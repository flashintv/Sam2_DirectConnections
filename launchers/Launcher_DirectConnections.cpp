#include <Windows.h>
#include <iostream>
#include "resource.h"
#include "md5.h"

#ifdef DEDICATEDSERVER_EXE
#define ExecutableName "DedicatedServer.exe"
#define ExecutableFlags CREATE_SUSPENDED
#else
#define ExecutableName "Sam2.exe"
#define ExecutableFlags CREATE_SUSPENDED | DETACHED_PROCESS
#endif

__declspec(noreturn) void exit_msg( const char* format, ... )
{
	va_list arg;
	va_start( arg, format );
	vprintf( format, arg );
	va_end( arg );

	printf( "Exiting in" );
	for ( int i = 3; i > 0; i-- )
	{
		printf( " %is...", i );
		Sleep( 1000 );
	}
	exit( 0 );
}

void load_dll( PROCESS_INFORMATION& pi, const char* pszString, int nStringLen )
{
	void* pBuffer = VirtualAllocEx( pi.hProcess, NULL, nStringLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	if ( !pBuffer )
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Failed to allocate memory to inject '%s'.\n", pszString );
	}

	if ( !WriteProcessMemory( pi.hProcess, pBuffer, pszString, nStringLen, NULL ) )
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Failed to write memory to inject '%s'.\n", pszString );
	}

	HANDLE hThread = CreateRemoteThread( pi.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, pBuffer, NULL, NULL );
	if ( hThread )
	{
		ResumeThread( hThread ); // we are in a suspended state so we need to resume the thread manually
		WaitForSingleObject( hThread, INFINITE );

		DWORD dwResult = 0;
		GetExitCodeThread( hThread, &dwResult );
		if ( dwResult == 0 )
		{
			TerminateProcess( pi.hProcess, 0 );
			exit_msg( "LoadLibrary failed to load file '%s'.\n", pszString );
		}

		CloseHandle( hThread );
	}
	else
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Failed to run LoadLibrary to inject '%s', error code: %i.\n", pszString, GetLastError() );
	}
}

int main( int argc, char* argv[] )
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof( si ) );
	ZeroMemory( &pi, sizeof( pi ) );
	si.cb = sizeof( si );

	static char szCmdLine[32767] = ExecutableName; // limit on windows
	for ( int i = 1; i < argc; i++ )
	{
		strcat_s( szCmdLine, " " );
		strcat_s( szCmdLine, argv[i] );
	}

	if ( !CreateProcess( nullptr,
		szCmdLine, // command line
		nullptr, nullptr, FALSE, 
		ExecutableFlags, // flags
		nullptr, nullptr, &si, &pi ) )
	{
		exit_msg( "Failed to create process '%s' with %s%s\n", 
			ExecutableName,
			argc > 1 ? "arguments:\n" : "no arguments.",
			argc > 1 ? strchr( szCmdLine, ' ' ) + 1 : "" );
		return 1;
	}

    printf( "Created process '%s' PID( %i )\n", ExecutableName, pi.dwProcessId );

	load_dll( pi, "Core.dll", sizeof( "Core.dll" ) );
	load_dll( pi, "Engine.dll", sizeof( "Engine.dll" ) );

	// load current mod (because insamnity uses a different dll)
	//load_dll( pi, "Sam2Game.dll", sizeof( "Sam2Game.dll" ) );
	FILE* currentmod_file = NULL;
	if ( fopen_s( &currentmod_file, ".\\..\\Content\\CurrentMod.txt", "r" ) == 0 )
	{
		char modname[100];
		char line[256];
		while ( fgets( line, sizeof( line ), currentmod_file ) )
		{
			if ( line[0] == '#' || line[0] == '\n' || line[0] == '\r' ) continue;
			if ( sscanf_s( line, "CURRENTMOD = %[^.]mod", modname, sizeof( modname ) ) == 1 )
			{
				// this would dynamically load the dll if i knew where it stores the data about what dll it needs to load
				if ( _strnicmp( modname, "InSamnity2", sizeof( modname ) ) == 0 )
					load_dll( pi, "InSamnity2Game.dll", sizeof( "InSamnity2Game.dll" ) );
				else
					load_dll( pi, "Sam2Game.dll", sizeof( "Sam2Game.dll" ) );
				break;
			}
		}
		fclose( currentmod_file );
	}
	else
	{
#if 0
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Couldn't load '.\\..\\Content\\CurrentMod.txt' to load the dll prematurely. (%i)\n", errno );
#else
		// just load Sam2Game.dll because if we dont have a CurrentMod.txt we havent launched the game at all before
		load_dll( pi, "Sam2Game.dll", sizeof( "Sam2Game.dll" ) );
#endif
	}

	HMODULE hModule = NULL; // https://gist.github.com/davidruhmann/8008844
	GetModuleHandleEx( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)load_dll, &hModule );
	
	HRSRC hRes = FindResource( hModule, MAKEINTRESOURCE( IDR_DLL1 ), "DLL" );
	if ( !hRes )
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Failed to find direct connections resource.\n" );
	}

	HGLOBAL hResData = LoadResource( hModule, hRes );
	if ( !hResData )
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Failed to load direct connections resource.\n" );
	}

	DWORD size = SizeofResource( hModule, hRes );
	void* data = LockResource( hResData );
	if ( !data || !size )
	{
		TerminateProcess( pi.hProcess, 0 );
		exit_msg( "Direct connections resource unavailable.\n" );
	}

	struct stat filestat;
	int statval = stat( "DirectConnections.dll", &filestat );
	if ( statval == 0 && filestat.st_size != size )
		statval = 1;

	if ( statval == 0 )
	{
		FILE* file = NULL;
		if ( fopen_s( &file, "DirectConnections.dll", "rb" ) != 0 )
			statval = 1;

		if ( file && statval != 1 )
		{
			unsigned char* filedata = new unsigned char[filestat.st_size];
			if ( fread_s( filedata, filestat.st_size, 1, filestat.st_size, file ) != filestat.st_size )
				statval = 1;

			if ( statval != 1 )
			{
				unsigned char cur_digest[MD5_SIZE], emb_digest[MD5_SIZE];
				md5( cur_digest, filedata, filestat.st_size );
				md5( emb_digest, data, size );
				if ( memcmp( cur_digest, emb_digest, MD5_SIZE ) != 0 )
					statval = 1;
			}

			fclose( file );
			delete[] filedata;
		}
	}

	if ( statval != 0 )
	{
		FILE* file = NULL;
		fopen_s( &file, "DirectConnections.dll", "wb" );
		if ( !file )
		{
			TerminateProcess( pi.hProcess, 0 );
			exit_msg( "Direct connections file couldn't be created.\n" );
		}
		fwrite( data, 1, size, file );
		fclose( file );
	}

#ifdef _DEBUG
	printf( "Waiting for key press to continue..." );
	if ( getchar() != '\n' ) // delay until input so we can attach a debugger
		printf( "\n" );
#endif
	load_dll( pi, "DirectConnections.dll", sizeof( "DirectConnections.dll" ) );

	ResumeThread( pi.hThread );
}
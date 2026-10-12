#include <Windows.h>
#include <Psapi.h>
#include "safetyhook.hpp"
#include "steam_api.h"

#define FMT_INT32(x)	0xABCD0003u, (int32)(x)
#define FMT_UINT32(x)	0xABCD0004u, (uint32)(x)
#define FMT_INT64(x)	0xABCD0005u, (int64)(x)
#define FMT_UINT64(x)	0xABCD0006u, (uint64)(x)
#define FMT_FLOAT(x)	0xABCD0007u, (double)(x)
#define FMT_STRING(x)	0xABCD0009u, (const char*)(x)
#define FMT_WSTRING(x)	0xABCD000Au, (const wchar_t*)(x)
#define FMT_POINTER(x)	0xABCD000Bu, (void*)(x)

// NON-IMPORTS
namespace SeriousEngine
{
	template<typename T>
	class CDynamicContainer {};
	template<typename T>
	class CStaticStackArray {};
	template<typename T>
	class Handle {};

	class CIPAddress
	{
	public:
		DWORD nIPv4;
		WORD usPort;
		WORD word6 = 0;
		DWORD dword8 = 0;
		DWORD dwordC = 0;
	};

	class CNetworkMessage
	{
	public:
		unsigned __int8 unsigned___int80;
		DWORD m_eMessageType;
		BYTE gap8[8];
		DWORD dword10;
	};

	class Time
	{
	public:
		double m_dblTime;
	};
}

// IMPORTS
namespace SeriousEngine
{
	class CSteamSocket
	{
	public:
		__declspec(dllimport) void Connect( CIPAddress const& );
		__declspec(dllimport) void Connect( CSteamID const& );
		__declspec(dllimport) void Listen( int, unsigned long, long );
		__declspec(dllimport) void OnSocketSatus( SocketStatusCallback_t* );
		__declspec(dllimport) void OnRequest_Server( P2PSessionRequest_t* );
		__declspec(dllimport) void Close();

	public:
		CSteamID steamid;
		DWORD hListenSocket;
		BYTE gapC[4];
		int m_bIsGameServer;
	};

	__declspec(dllimport) class CSteamOnlineInterface
	{
	public:
		virtual void vf0();
		virtual void Initialize( int );
		virtual void Uninitialize( void );
		virtual int IsDeviceConnected( void );
		virtual void __cdecl netTestCompression( void const*, long );
		virtual void Shutdown( void );
		virtual void __cdecl netTestCompression_6( void const*, long );
		virtual void OnSimStart( void );
		virtual void OnSimStop( void );
		virtual void VoiceUnmutePlayer( long );
		virtual void OnClientDisconnect( long );
		virtual void SetPlayOnline( int );
		virtual int IsPlayingOnline( void );
		virtual int RecognizeAchievementName( char const* );
		virtual int RecognizeAchievementName_14( char const* );
		virtual class CDataType* mdGetDataType( void );
		virtual void __cdecl netTestCompression_16( void const*, long );
		virtual int UpdateWasCheckSuccessfull( void );
		virtual int UpdateWasCheckSuccessfull_18( void );
		virtual class CDataType* mdGetDataType_19( void );
		virtual class CDataType* mdGetDataType_20( void );
		virtual class CString mdGetName( void );
		virtual class CDataType* mdGetDataType_22( void );
		virtual class CDataType* mdGetDataType_23( void );
		virtual void VoiceUnmutePlayer_24( long );
		virtual class CString mdGetName_25( void );
		virtual class CDataType* mdGetDataType_26( void );
		virtual class CDataType* mdGetDataType_27( void );
		virtual void UploadProfile( char const*, char const* );
		virtual class CDataType* mdGetDataType_29( void );
		virtual void VoiceUnmutePlayer_30( long );
		virtual void __cdecl netTestCompression_31( void const*, long );
		virtual void __cdecl netTestCompression_32( void const*, long );
		virtual void __cdecl netTestCompression_33( void const*, long );
		virtual class CDataType* mdGetDataType_34( void );
		virtual void VoiceUnmutePlayer_35( long );
		virtual class CDataType* mdGetDataType_36( void );
		virtual class CDataType* mdGetDataType_37( void );
		virtual class CDataType* mdGetDataType_38( void );
		virtual void VoiceUnmutePlayer_39( long );
		virtual class CDataType* mdGetDataType_40( void );
		virtual class CString mdGetName_41( void );
		virtual void __cdecl netTestCompression_42( void const*, long );
		virtual void ChallengeGetRequest( long, unsigned char*&, long& );
		virtual void ChallengeCalculateResponse( unsigned char*, long, unsigned char*&, long& );
		virtual void ChallengeAuthenticate( long, class CSteamID&, unsigned char*, long );
		virtual int ChallengeIsAuthenticationFinished( long );
		virtual int ChallengeIsAuthenticated( long );
		virtual void __cdecl netTestCompression_48( void const*, long );
		virtual void VoiceUnmutePlayer_49( long );
		virtual int MessageUseAsCurrent( class CString const&, enum EMsgNotificationType );
		virtual int RecognizeAchievementName_51( char const* );
		virtual int MessageUseAsCurrent_52( class CString const&, enum EMsgNotificationType );
		virtual void __cdecl netTestCompression_53( void const*, long );
		virtual void VoiceUnmutePlayer_54( long );
		virtual void VoiceUnmutePlayer_55( long );
		virtual class CString PlayerGetNameByIndex( long );
		virtual void VoiceUnmutePlayer_57( long );
		virtual int RecognizeAchievementName_58( char const* );
		virtual void UploadProfile_59( char const*, char const* );
		virtual void VoiceUnmutePlayer_60( long );
		virtual void VoiceUnmutePlayer_61( long );
		virtual int RecognizeAchievementName_62( char const* );
		virtual void VoiceUnmutePlayer_63( long );
		virtual void VoiceUnmutePlayer_64( long );
		virtual void __cdecl netTestCompression_65( void const*, long );
		virtual void __cdecl netTestCompression_66( void const*, long );
		virtual class CDataType* mdGetDataType_67( void );
		virtual void __cdecl netTestCompression_68( void const*, long );
		virtual void __cdecl netTestCompression_69( void const*, long );
		virtual class CDataType* mdGetDataType_70( void );
		virtual class CDataType* mdGetDataType_71( void );
		virtual int RecognizeAchievementName_72( char const* );
		virtual int RecognizeAchievementName_73( char const* );
		virtual int UpdateWasCheckSuccessfull_74( void );
		virtual int RecognizeAchievementName_75( char const* );
		virtual int RecognizeAchievementName_76( char const* );
		virtual void VoiceUnmutePlayer_77( long );
		virtual void VoiceUnmutePlayer_78( long );
		virtual void VoiceUnmutePlayer_79( long );
		virtual void VoiceUnmutePlayer_80( long );
		virtual void VoiceUnmutePlayer_81( long );
		virtual void UploadProfile_82( char const*, char const* );
		virtual void VoiceUnmutePlayer_83( long );
		virtual void VoiceUnmutePlayer_84( long );
		virtual void __cdecl netTestCompression_85( void const*, long );
		virtual void __cdecl netTestCompression_86( void const*, long );
		virtual void __cdecl netTestCompression_87( void const*, long );
		virtual void __cdecl netTestCompression_88( void const*, long );
		virtual class CDataType* mdGetDataType_89( void );
		virtual void __cdecl netTestCompression_90( void const*, long );
		virtual class CDataType* mdGetDataType_91( void );
		virtual void __cdecl netTestCompression_92( void const*, long );
		virtual float MessageGetVoiceTime( void );
		virtual float MessageGetVoiceTime_94( void );
		virtual void __cdecl netTestCompression_95( void const*, long );
		virtual void __cdecl netTestCompression_96( void const*, long );
		virtual void VoiceUnmutePlayer_97( long );
		virtual void VoiceUnmutePlayer_98( long );
		virtual class CDataType* mdGetDataType_99( void );
		virtual class CDataType* mdGetDataType_100( void );
		virtual class CDataType* mdGetDataType_101( void );
		virtual class CDataType* mdGetDataType_102( void );
		virtual int MessageUseAsCurrent_103( class CString const&, enum EMsgNotificationType );
		virtual void VoiceUnmutePlayer_104( long );
		virtual int MessageUseAsCurrent_105( class CString const&, enum EMsgNotificationType );
		virtual void UploadProfile_106( char const*, char const* );
		virtual void MatchCreateSession( void );
		virtual void __cdecl netTestCompression_108( void const*, long );
		virtual void MatchDeleteSession( void );
		virtual void MatchSetSlotCounts( long, long, long, long );
		virtual void MatchSetSessionAttributes( char const*, long, class CString const&, char const*, int );
		virtual void MatchGetSessionInfo( class COnlineSession* );
		virtual enum EOnlineTaskStatus MatchGetSessionInfoStatus( void );
		virtual void MatchGetSessionInfoResults( class CSteamID&, unsigned long&, unsigned long& );
		virtual void __cdecl netTestCompression_115( void const*, long );
		virtual void __cdecl netTestCompression_116( void const*, long );
		virtual void MatchSearchSetParams( long, class CString const&, int, long, int );
		virtual void __cdecl netTestCompression_118( void const*, long );
		virtual void MatchStartOptiMatchSearch( void );
		virtual int UpdateWasCheckSuccessfull_120( void );
		virtual class CDataType* mdGetDataType_121( void );
		virtual int MatchGetSearchResults( class CDynamicContainer<class COnlineSession>& );
		virtual void __cdecl netTestCompression_123( void const*, long );
		virtual void AwardAchievement( char const* );
		virtual void SetAchievementProgress( char const*, long, long );
		virtual int RecognizeAchievementName_126( char const* );
		virtual void RegisterAchievement( char const* );
		virtual void GetAchievementInfos( class CStaticStackArray<class CAchievementInfo>* );
		virtual class CString GetAchievementProgress( char const* );
		virtual int GetSeriousRunLevelCompletionStatus( char const* );
		virtual long GetStatsCount( void );
		virtual class CSteamStat* GetStatByID( char const* );
		virtual void AddToStat( char const*, float );
		virtual void SetStat( char const*, float );
		virtual void StoreStats( void );
		virtual float GetStatFloatValue( char const* );
		virtual float GetStatIntValue( char const* );
		virtual void UploadProfile_138( char const*, char const* );
		virtual unsigned __int64 GetUserID( long );
		virtual void __cdecl netTestCompression_140( void const*, long );
		virtual void Step( void );
		virtual void UpdateSteamLobbyData( void );
		virtual class CString GetSeriousRunAchievementProgress( void );
		virtual class CString GetAnyGameAchievementProgress( void );
		virtual class CString GetSeriousGameAchievementProgress( void );
		virtual class CString GetAny2xGameAchievementProgress( void );

	public:
		BYTE gap0[80];
		CSteamID m_steamIDGameServer;
		DWORD m_unIPServer;
		uint16 m_usPortServer;
	};

	__declspec(dllimport) class CClientInterface
	{
	public:
		virtual void vf0();
		virtual void AddDebugInfo( class Handle<class CEntity> );
		virtual void RenderDebugInfo( void );
		virtual void DelayMessage( class CNetworkMessage*, class Handle<class CEntity>, class CStaticStackArray<long>& );
		virtual int CanApplyMessage( long );
		virtual void RemoveDelayedMessage( long );
		virtual void OnWorldStop( void );
		virtual void VoiceUnmutePlayer( long );
		virtual void VoiceUnmutePlayer_8( long );
		virtual long GetModuleIndex( class CString& );
		virtual class CString GetModuleName( long );
		virtual void VoiceUnmutePlayer_11( long );
		virtual void VoiceUnmutePlayer_12( long );
		virtual long GetOutgoingStringIndex( class CString const& );
		virtual char const* GetOutgoingString( long );
		virtual char const* GetIncommingString( long );
		virtual int DoesIncommingStringExist( long );
		virtual void Initialize( void );
		virtual void Close( void );
		virtual void Disconnect( void );
		virtual class CDataType* mdGetDataType( void );
		virtual class CDataType* mdGetDataType_21( void );
		virtual int UpdateWasCheckSuccessfull( void );
		virtual class CDataType* mdGetDataType_23( void );
		virtual class CDataType* mdGetDataType_24( void );
		virtual int UpdateWasCheckSuccessfull_25( void );
		virtual int IsConnected( void );
		virtual int IsDisconnecting( void );
		virtual int IsCreated( void );
		virtual int HasActiveConnections( void );
		virtual void SetAvatar( class Handle<class CEntity>, long );
		virtual void SetAvatarPosition( class Vector3f );
		virtual unsigned long GetOutgoingBandwidthUsage( void );
		virtual unsigned long GetOutgoingBandwidthUsage_33( void );
		virtual unsigned long GetOutgoingBandwidthUsage_34( void );
		virtual void AddEntityTemplate( class CEntity* );
		virtual class CEntity* GetEntityTemplate( unsigned long );
		virtual void InitializeEntities( void );
		virtual void SendMessage( class CNetworkMessage& );
		virtual void UploadProfile( char const*, char const* );
		virtual void SendVoice( class CNetworkMessage& );
		virtual void UploadProfile_41( char const*, char const* );
		virtual void StartDemoRecording( void );
		virtual void StopDemoRecording( void );
		virtual class Time GetServerTime( void );
		virtual void UpadateServerTime( class Time );
		virtual void Step( void );
		virtual void HandleConnectResponse( class CNMConnectResponse const* );
		virtual void SendRemapList( void );
		virtual void ProcessRemapList( class CNMRemapList* );
		virtual long GetRemapEntry( class Handle<class CEntity>, class CRemapTableEntry& );
		virtual void SendModuleList( void );
		virtual void SendStringList( void );
		virtual void AddModule( class CNMModuleIndex* );
		virtual void AddIncommingString( class CNMStringIndex const* );
		virtual void UpdateEntity( class CNMUpdateEntity* );
		virtual void InitialUpdate( class CNMInitialUpdate* );
		virtual void CreateEntity( class CNMCreateEntity* );
		virtual void DeleteEntity( class CNMDeleteEntity* );
		virtual void ExecuteRPC( int, class Handle<class CEntity>, long, long, unsigned char* );
		virtual void ExecuteRRPC( class CNMReliableRPC* );
		virtual void ExecuteURPC( class CNMUnreliableRPC* );
		virtual void SetSessionParams( class CNMSessionParams* );
		virtual void ProcessPreWorldChange( class CNMPreWorldChange* );
		virtual void ProcessPostWorldChange( class CNMPostWorldChange* );
		virtual int ProcessMessage( class CNetworkMessage* );
		virtual void SyncSessionParameters( void );
		virtual void DeleteEntityBaselines( void );
		virtual long GetClientIndex( void );
		virtual int Connect( int, int );
		virtual int HasTimedOut( void );

	public:
		DWORD gap4;
		int m_nConnectionStatus;
		DWORD gapC;
		DWORD m_CommunicationInterface;
		BYTE gap14[5244];
		Time m_timConnect;
		BYTE gap1498[2344];
		DWORD dword1DC0;
		BYTE gap1DC4[84];
		DWORD dword1E18;
		BYTE gap1E1C[12];
		DWORD dword1E28;
		BYTE gap1E2C[12];
		DWORD dword1E38;
		DWORD dword1E3C;
		char char1E40;
		BYTE gap1E41[43];
		char char1E6C;
		BYTE gap1E6D[91];
		int m_bJoinAsPrivate;
		int m_bJoinAsObserver;
	};

	// we need this for netGetCurrent
	class CNetworkInterface : public CClientInterface {};

	class CCommunicationInterface
	{
	public:
		__declspec(dllimport) void InitiateConnectToServer_t( CSteamID const& );

	public:
		DWORD dword0;
		DWORD dword4;
		BYTE gap8[4];
		CSteamID m_steamId;
		BYTE gap14[4];
		int m_PacketBuffer;
		BYTE gap1C[2284];
		DWORD m_pInterface;
		BYTE gap90C[60];
		SeriousEngine::CSteamSocket m_SteamSocket;
		BYTE gap960[192];
		DWORD dwordA20;
		DWORD dwordA24;
	};

	class CMSLoading
	{
	public:
		void** __vtbl;
		BYTE gap0[100];
		int m_bGottenLevelData;
	};

	__declspec(dllimport) void onlFriendsStartup();
	__declspec(dllimport) void onlInitialize();
	__declspec(dllimport) void conInfoF( char const*, ... );
	__declspec(dllimport) void conPrintF( enum ConsoleMessageType, char const*, ... );
	__declspec(dllimport) class CNetworkInterface* netGetCurrent();
	__declspec(dllimport) class Time timUptimeNow();
	__declspec(dllimport) long sysStartProcess( char const*, CStaticStackArray<class CString> const& );

	__declspec(dllimport) class CDataType* md_pdtUBYTE;
	__declspec(dllimport) unsigned long net_ulServerAddress;
	__declspec(dllimport) long net_iServerPort;
	__declspec(dllimport) int net_bSteamGameserver;
	__declspec(dllimport) long net_iPort;
	__declspec(dllimport) CSteamID net_idSteamServerLobby;
}

#if 0
bool bConnectingViaIP = false;
SeriousEngine::CCommunicationInterface* pCommunicationInterface;
HServerQuery hServerPingResponse = HSERVERQUERY_INVALID;
SafetyHookInline CCommunicationInterfaceInitiateConnectToServer_tHook;
#else
SafetyHookInline CClientInterfaceConnectHook;
#endif
class CSteamMatchmakingPingResponse : public ISteamMatchmakingPingResponse
{
public:
	virtual void ServerResponded( gameserveritem_t& server ) 
	{
#if 0
		bConnectingViaIP = false;
		SeriousEngine::conInfoF( "Server responded to ping with %1\n", FMT_UINT64( server.m_steamID.ConvertToUint64() ) );
		
		SeriousEngine::net_idSteamServerLobby = server.m_steamID;
		SeriousEngine::net_ulServerAddress = 0;
		SeriousEngine::net_iServerPort = 0;

		if ( SeriousEngine::netGetCurrent() )
			CCommunicationInterfaceInitiateConnectToServer_tHook.thiscall< void, SeriousEngine::CCommunicationInterface*, CSteamID const& >( pCommunicationInterface, server.m_steamID);
		if ( pLoading )
			pLoading->m_bGottenLevelData = FALSE;
#else
		steamid = server.m_steamID;
		ip = server.m_NetAdr.GetIP();
		port = server.m_NetAdr.GetConnectionPort();
		received = true;
#endif
	}
	virtual void ServerFailedToRespond() {}
public:
#if 0
	SeriousEngine::CMSLoading* pLoading;
	int bJoinAsPrivate;
	int bJoinAsObserver;
#else
	CSteamID steamid;
	uint32 ip;
	uint16 port;
	bool received;
#endif
} g_ServerResponse;

BOOL __fastcall CClientInterfaceConnectHookFn( SeriousEngine::CSteamOnlineInterface* thisptr, void*, 
	int bJoinAsPrivate, int bJoinAsObserver )
{
#if 0
	bConnectingViaIP = false;

	if ( SeriousEngine::net_bSteamGameserver && SeriousEngine::net_idSteamServerLobby.ConvertToUint64() == 0 )
	{
		bConnectingViaIP = true;
		SeriousEngine::conInfoF( "Deferring connection til lobby is found.\n" );

		unsigned long ulServerAddress = SeriousEngine::net_ulServerAddress;
		long iServerPort = SeriousEngine::net_iServerPort;

		thisptr->m_unIPServer = 0;
		thisptr->m_usPortServer = 0;

		SeriousEngine::net_idSteamServerLobby.SetFromUint64( -1 );
		SeriousEngine::net_ulServerAddress = 0;
		SeriousEngine::net_iServerPort = 0;
		SeriousEngine::net_bSteamGameserver = TRUE;

		g_ServerResponse.pLoading = NULL;
		g_ServerResponse.bJoinAsPrivate = bJoinAsPrivate;
		g_ServerResponse.bJoinAsObserver = bJoinAsObserver;
		hServerPingResponse = SteamMatchmakingServers()->PingServer( ulServerAddress, iServerPort + 1, &g_ServerResponse );
		
		// set connection status to pending
		//SeriousEngine::netGetCurrent()->m_nConnectionStatus = 1;
		//SeriousEngine::netGetCurrent()->m_bJoinAsPrivate = bJoinAsPrivate;
		//SeriousEngine::netGetCurrent()->m_bJoinAsObserver = bJoinAsObserver;
		//SeriousEngine::netGetCurrent()->m_timConnect = SeriousEngine::timUptimeNow();
		return CClientInterfaceConnectHook.thiscall<int>( thisptr, bJoinAsPrivate, bJoinAsObserver );
	}
#else
	if ( SeriousEngine::net_idSteamServerLobby.ConvertToUint64() == 0 )
	{
		g_ServerResponse.received = false;
		SeriousEngine::conInfoF( "Deferring connection til lobby is found.\n" );

		SteamMatchmakingServers()->PingServer( SeriousEngine::net_ulServerAddress, SeriousEngine::net_iServerPort + 1, &g_ServerResponse );
		SteamAPI_RunCallbacks();

		int ntime = 0;
		while ( !g_ServerResponse.received )
		{
			SteamAPI_RunCallbacks();
			Sleep( 50 );

			if ( ntime > 3000 )
				break;
			ntime += 50;
		}

		if ( g_ServerResponse.received )
		{
			SeriousEngine::net_bSteamGameserver = TRUE;
			SeriousEngine::net_idSteamServerLobby = g_ServerResponse.steamid;
			SeriousEngine::net_ulServerAddress = g_ServerResponse.ip;
			SeriousEngine::net_iServerPort = g_ServerResponse.port;

			thisptr->m_steamIDGameServer = g_ServerResponse.steamid;
			thisptr->m_unIPServer = g_ServerResponse.ip;
			thisptr->m_usPortServer = g_ServerResponse.port;
		}
	}
#endif

	SeriousEngine::conInfoF( "Proceeding with a %1 connection %2 to %3.\n",
		FMT_STRING( bJoinAsPrivate ? "private" : "public" ),
		FMT_STRING( bJoinAsObserver ? "as an observer" : "as a player" ),
		FMT_UINT64( SeriousEngine::net_idSteamServerLobby.ConvertToUint64() ) );

	return CClientInterfaceConnectHook.thiscall<int>( thisptr, bJoinAsPrivate, bJoinAsObserver );
}

#if 0
SafetyHookInline CMSLoadingStepHook;
void __fastcall CMSLoadingStepHookFn( SeriousEngine::CMSLoading* thisptr, void* )
{
	g_ServerResponse.pLoading = thisptr;
	CMSLoadingStepHook.thiscall( thisptr );
}
#endif

SafetyHookInline CSteamOnlineInterfaceChallengeCalculateResponseHook;
void __fastcall CSteamOnlineInterfaceChallengeCalculateResponseHookFn( SeriousEngine::CSteamOnlineInterface* thisptr, void*, unsigned char* a, long b, unsigned char*& c, long& d )
{
	if ( g_ServerResponse.received )
	{
		thisptr->m_steamIDGameServer = g_ServerResponse.steamid;
		thisptr->m_unIPServer = g_ServerResponse.ip;
		thisptr->m_usPortServer = g_ServerResponse.port;
	}
	CSteamOnlineInterfaceChallengeCalculateResponseHook.thiscall<void, SeriousEngine::CSteamOnlineInterface*, unsigned char*, long, unsigned char*&, long&>( thisptr, a, b, c, d );
}

void* NetricsaServerCrashReasonHookExit;
SafetyHookMid NetricsaServerCrashReasonHook;
void NetricsaServerCrashReasonHookFn( SafetyHookContext& ctx )
{
	/*
	ebx = get_profile_or_whatnot();
	// our mid hook is here
	v5 = *(SeriousEngine::CInputBindings **)(ebx + 112);
	*/
	if ( ctx.ebx != 0 )
		return;

	*reinterpret_cast<uintptr_t*>(ctx.esi) = NULL;
	*reinterpret_cast<uintptr_t*>(ctx.trampoline_esp) = reinterpret_cast<uintptr_t>(NetricsaServerCrashReasonHookExit);
}

#if 0
void __fastcall CCommunicationInterfaceInitiateConnectToServer_tHookFn( SeriousEngine::CCommunicationInterface* thisptr, void*, CSteamID const& steamid )
{
	pCommunicationInterface = thisptr;
	if ( !bConnectingViaIP )
		CCommunicationInterfaceInitiateConnectToServer_tHook.thiscall< void, SeriousEngine::CCommunicationInterface*, CSteamID const& >( thisptr, steamid );
}
#endif

SafetyHookInline sysStartProcessHook;
long sysStartProcessHookFn( char const* pszExePath, SeriousEngine::CStaticStackArray<class SeriousEngine::CString> const& args )
{
	static char szOurExePath[MAX_PATH];
	strncpy_s( szOurExePath, pszExePath, MAX_PATH );
	strrchr( szOurExePath, '\\' )[0] = '\0'; // this should in reality return NULL
	strcat_s( szOurExePath, "\\Sam2_DirectConnections.exe" );
	return sysStartProcessHook.call<long>( szOurExePath, &args );
}

SafetyHookInline CSimulationJoin_tHook;
void __fastcall CSimulationJoin_tHookFn( void* thisptr, void*, int bJoinAsPrivate, int bJoinAsObserver )
{
#if 0
#else
	if ( SeriousEngine::net_idSteamServerLobby.ConvertToUint64() == 0 )
	{
		g_ServerResponse.received = false;
		SeriousEngine::conInfoF( "Deferring connection til lobby is found.\n" );

		SteamMatchmakingServers()->PingServer( SeriousEngine::net_ulServerAddress, SeriousEngine::net_iServerPort + 1, &g_ServerResponse );
		SteamAPI_RunCallbacks();

		int ntime = 0;
		while ( !g_ServerResponse.received )
		{
			SteamAPI_RunCallbacks();
			Sleep( 50 );

			if ( ntime > 3000 )
				break;
			ntime += 50;
		}

		if ( g_ServerResponse.received )
		{
			SeriousEngine::net_bSteamGameserver = TRUE;
			SeriousEngine::net_idSteamServerLobby = g_ServerResponse.steamid;
			//SeriousEngine::net_ulServerAddress = 0;
			//SeriousEngine::net_iServerPort = 0;
		}
	}
#endif
	CSimulationJoin_tHook.thiscall( thisptr, bJoinAsPrivate, bJoinAsObserver );
}

template <class T>
void* ResolveThunk( T pmf )
{
	void* p = *reinterpret_cast<void**>(&pmf);
	for ( int i = 0; p && i < 4; ++i )
	{
		auto b = (uint8_t*)p;
		if ( b[0] == 0xE9 )
			p = b + 5 + *(int32_t*)(b + 1);
		else if ( b[0] == 0xFF && b[1] == 0x25 )
			return **(void***)(b + 2);
		else
			return p;
	}
	return p;
}

void* FindSignature( const char* szmodule, const char* szsignature )
{
	#define INRANGE(x, a, b) (x >= a && x <= b)
	#define getBits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
	#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

	MODULEINFO modInfo;
	GetModuleInformation( GetCurrentProcess(), GetModuleHandleA( szmodule ), &modInfo, sizeof( MODULEINFO ) );
	DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
	DWORD endAddress = startAddress + modInfo.SizeOfImage;
	const char* pat = szsignature;
	DWORD firstMatch = 0;
	for ( DWORD pCur = startAddress; pCur < endAddress; pCur++ ) {
		if ( !*pat )
			return (void*)firstMatch;
		if ( *(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte( pat ) ) {
			if ( !firstMatch )
				firstMatch = pCur;
			if ( !pat[2] )
				return (void*)firstMatch;
			if ( *(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?' )
				pat += 3;
			else
				pat += 2; // one ?
		}
		else {
			pat = szsignature;
			firstMatch = 0;
		}
	}
	return NULL;
}

BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD reason, LPVOID lpReserved )
{
	switch ( reason )
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls( hModule );

		sysStartProcessHook = safetyhook::create_inline(
			ResolveThunk( SeriousEngine::sysStartProcess ),
			sysStartProcessHookFn );
		/*CClientInterfaceConnectHook = safetyhook::create_inline(
			ResolveThunk( GetProcAddress( GetModuleHandle( "Engine.dll" ), "?Connect@CClientInterface@SeriousEngine@@UAEHHH@Z" ) ),
			CClientInterfaceConnectHookFn );*/
		CSimulationJoin_tHook = safetyhook::create_inline(
			ResolveThunk( GetProcAddress( GetModuleHandle( "Engine.dll" ), "?Join_t@CSimulation@SeriousEngine@@QAEXHH@Z" ) ),
			CSimulationJoin_tHookFn );
		CSteamOnlineInterfaceChallengeCalculateResponseHook = safetyhook::create_inline(
			ResolveThunk( GetProcAddress( GetModuleHandle( "Engine.dll" ), "?ChallengeCalculateResponse@CSteamOnlineInterface@SeriousEngine@@UAEXPAEJAAPAEAAJ@Z" ) ),
			CSteamOnlineInterfaceChallengeCalculateResponseHookFn );
#if 0
		CCommunicationInterfaceInitiateConnectToServer_tHook = safetyhook::create_inline(
			ResolveThunk( &static_cast<void (SeriousEngine::CCommunicationInterface::*)(CSteamID const&)>(&SeriousEngine::CCommunicationInterface::InitiateConnectToServer_t) ),
			CCommunicationInterfaceInitiateConnectToServer_tHookFn );
		CMSLoadingStepHook = safetyhook::create_inline(
			ResolveThunk( GetProcAddress( GetModuleHandle( "Sam2Game.dll" ), "?Step@CMSLoading@SeriousEngine@@UAEXXZ" ) ),
			CMSLoadingStepHookFn );
#endif

		// find signature because its a midhook and there are no symbols/exports for it
		if ( GetModuleHandle( "InSamnity2Game.dll" ) )
			NetricsaServerCrashReasonHook = safetyhook::create_mid(
				FindSignature( "InSamnity2Game.dll", "8B 8B F8 00 00 00 89 5D E8" ),
				NetricsaServerCrashReasonHookFn );
		else
			NetricsaServerCrashReasonHook = safetyhook::create_mid(
				FindSignature( "Sam2Game.dll", "8B 4B 70 89 5D E8" ),
				NetricsaServerCrashReasonHookFn );
		NetricsaServerCrashReasonHookExit = FindSignature( 
			GetModuleHandle( "InSamnity2Game.dll" ) ? "InSamnity2Game.dll" : "Sam2Game.dll", 
			"8D 4D F0 C7 45 EC 01 00 00 00 C6 45 FC 00 FF 15 ?? ?? ?? ?? 8B 4D F4 5F 8B C6 5E 5B 64 89 0D 00 00 00 00 8B E5 5D C3" );

		break;
	}
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
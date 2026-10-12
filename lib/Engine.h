#include "Core.h"

namespace SeriousEngine
{
	// static imports
	DLLIMPORT void vmExecuteBatchedCommands();
	DLLIMPORT class CString simGetLoadingWorldPath();
	DLLIMPORT int simIsLoading();
	DLLIMPORT void priSetCurrent( class CProjectInstance* );
	DLLIMPORT class CProject* wldGetProject();
	DLLIMPORT void vmSaveCvars();
	DLLIMPORT void comEndWinsock();
	DLLIMPORT void onlInitialize();
	DLLIMPORT void onlSetDedicated( int );
	DLLIMPORT long net_iPort;
	DLLIMPORT void comInitWinsock();
	DLLIMPORT void vmProcessCmdArgs();
	DLLIMPORT void vmLoadCvars( char const* );
	DLLIMPORT void vmProcessConfigFile( char const* );
	DLLIMPORT int engRun( void( __cdecl* )(void), int, char** const, char const* );

	// classes
	class CProjectInstance : public CResource
	{
	public:
		virtual void* mdGetDataType() OVERRIDE;
		virtual void DeleteSelf() OVERRIDE;
		virtual CSmartObject* AcquireReplacement() OVERRIDE;
		virtual void InitiateDelayedLoad() OVERRIDE;
		virtual int IsReplacementReady() OVERRIDE;
		virtual class CString GetSimpleInfo() OVERRIDE;
		virtual class CStockDumpInfo GetSimpleInfoCSV() OVERRIDE;
		virtual void GetShellOpenPaths( class CString&, class CString& ) OVERRIDE;
		virtual void PrecacheData() OVERRIDE;
		virtual void PostRegister() OVERRIDE;
		virtual void Finalize( enum EPlatform, char const* ) OVERRIDE;
		virtual int MayFileBeReferenced() OVERRIDE;
		virtual class CString GetThumbnailFileName() OVERRIDE;
	public:
		int a;
		int b;
	};
}
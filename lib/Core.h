#define DLLIMPORT __declspec(dllimport);
#define OVERRIDE override

namespace SeriousEngine
{
	// static imports
	DLLIMPORT void mdModuleDeclareBeg( char const* );
	DLLIMPORT void mdDeclare( unsigned long const* );
	DLLIMPORT void mdModuleDeclareEnd();

	// classes
	class CObject
	{
	public:
		virtual ~CObject();
		virtual void* mdGetDataType();
	};

	class CSmartObject : public CObject
	{
	public:
		virtual ~CSmartObject() OVERRIDE;
		virtual void* mdGetDataType() OVERRIDE;
		virtual void DeleteSelf();
		virtual CSmartObject* AcquireReplacement();
		virtual void InitiateDelayedLoad();
		virtual int IsReplacementReady();
	};

	class CResource : public CSmartObject
	{
	public:
		virtual ~CResource() OVERRIDE;
		virtual void* mdGetDataType() OVERRIDE;
		virtual void DeleteSelf() OVERRIDE;
		virtual CSmartObject* AcquireReplacement() OVERRIDE;
		virtual void InitiateDelayedLoad() OVERRIDE;
		virtual int IsReplacementReady() OVERRIDE;
		virtual class CString GetSimpleInfo();
		virtual class CStockDumpInfo GetSimpleInfoCSV();
		virtual void GetShellOpenPaths( class CString&, class CString& );
		virtual void PrecacheData();
		virtual void PostRegister();
		virtual void Finalize( enum EPlatform, char const* );
		virtual int MayFileBeReferenced();
		virtual class CString GetThumbnailFileName();
	};
}
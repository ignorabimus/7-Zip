// HandlerOut.h

#ifndef __HANDLER_OUT_H
#define __HANDLER_OUT_H

#include "../../../Windows/System.h"

#include "../../Common/MethodProps.h"

namespace NArchive {

bool ParseSizeString(const wchar_t *name, const PROPVARIANT &prop, UInt64 percentsBase, UInt64 &res);

class CCommonMethodProps
{
protected:
  void InitCommon()
  {
    #ifndef _7ZIP_ST
    _numProcessors = _numThreads = NWindows::NSystem::GetNumberOfProcessors();
    #endif

    UInt64 memAvail = (UInt64)(sizeof(size_t)) << 28;
    _memAvail = memAvail;
    _memUsage = memAvail;
    if (NWindows::NSystem::GetRamSize(memAvail))
    {
      _memAvail = memAvail;
      _memUsage = memAvail / 32 * 17;
    }

    _processPriority = 2; // NORMAL_PRIORITY_CLASS
    _threadPriority = 3; // THREAD_PRIORITY_NORMAL
  }

public:
  #ifndef _7ZIP_ST
  UInt32 _numThreads;
  UInt32 _numProcessors;
  #endif

  UInt64 _memUsage;
  UInt64 _memAvail;

  UInt32 _processPriority;
  int numProcessPriority() const
  {
    switch (_processPriority)
    {
      case 0: return IDLE_PRIORITY_CLASS;         // 0x00000040
      case 1: return BELOW_NORMAL_PRIORITY_CLASS; // 0x00004000
      case 2: return NORMAL_PRIORITY_CLASS;       // 0x00000020
      case 3: return ABOVE_NORMAL_PRIORITY_CLASS; // 0x00008000
      case 4: return HIGH_PRIORITY_CLASS;         // 0x00000080
      case 5: return REALTIME_PRIORITY_CLASS;     // 0x00000100
      default: return NORMAL_PRIORITY_CLASS;      // 0x00000020
    }
  }

  UInt32 _threadPriority;
  int numThreadPriority() const
  {
    switch (_threadPriority)
    {
      case 0: return THREAD_PRIORITY_IDLE;          // -15
      case 1: return THREAD_PRIORITY_LOWEST;        // -2
      case 2: return THREAD_PRIORITY_BELOW_NORMAL;  // -1
      case 3: return THREAD_PRIORITY_NORMAL;        // 0
      case 4: return THREAD_PRIORITY_ABOVE_NORMAL;  // 1
      case 5: return THREAD_PRIORITY_HIGHEST;       // 2
      case 6: return THREAD_PRIORITY_TIME_CRITICAL; // 15
      default: return THREAD_PRIORITY_NORMAL;       // 0
    }
  }

  bool SetCommonProperty(const UString &name, const PROPVARIANT &value, HRESULT &hres);

  CCommonMethodProps() { InitCommon(); }
};


#ifndef EXTRACT_ONLY

class CMultiMethodProps: public CCommonMethodProps
{
  UInt32 _level;
  int _analysisLevel;

  void InitMulti();
public:
  UInt32 _crcSize;
  CObjectVector<COneMethodInfo> _methods;
  COneMethodInfo _filterMethod;
  bool _autoFilter;

  
  void SetGlobalLevelTo(COneMethodInfo &oneMethodInfo) const;

  #ifndef _7ZIP_ST
  static void SetMethodThreadsTo(COneMethodInfo &oneMethodInfo, UInt32 numThreads);
  #endif


  unsigned GetNumEmptyMethods() const
  {
    unsigned i;
    for (i = 0; i < _methods.Size(); i++)
      if (!_methods[i].IsEmpty())
        break;
    return i;
  }

  int GetLevel() const { return _level == (UInt32)(Int32)-1 ? 5 : (int)_level; }
  int GetAnalysisLevel() const { return _analysisLevel; }

  void Init();
  CMultiMethodProps() { InitMulti(); }

  HRESULT SetProperty(const wchar_t *name, const PROPVARIANT &value);
};


class CSingleMethodProps: public COneMethodInfo, public CCommonMethodProps
{
  UInt32 _level;

  void InitSingle()
  {
    _level = (UInt32)(Int32)-1;
  }

public:
  void Init();
  CSingleMethodProps() { InitSingle(); }
  
  int GetLevel() const { return _level == (UInt32)(Int32)-1 ? 5 : (int)_level; }
  HRESULT SetProperties(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
};

#endif

}

#endif

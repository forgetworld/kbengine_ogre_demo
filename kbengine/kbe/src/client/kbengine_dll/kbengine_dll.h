#ifndef __KBENGINE_DLL__
#define __KBENGINE_DLL__
#pragma warning(disable : 4217)
#pragma warning(disable : 4049)
#include "stdio.h"
#include "stdlib.h"
#include "common/common.h"
#include "Python.h"

#ifdef KBE_DLL_API
#else
#define KBE_DLL_API  extern "C" _declspec(dllimport)
#endif

namespace KBEngine{
	class EventHandle;
}

inline char* wchar2char(const wchar_t* ts)
{
	int len = (wcslen(ts) + 1) * 4;
	char* ccattr =(char *)malloc(len);
	memset(ccattr, 0, len);
	wcstombs(ccattr, ts, len);
	return ccattr;
};

inline wchar_t* char2wchar(const char* cs)
{
	int len = (strlen(cs) + 1) * 4;
	wchar_t* ccattr =(wchar_t *)malloc(len);
	memset(ccattr, 0, len);
	mbstowcs(ccattr, cs, len);
	return ccattr;
};

/**
	初始化与销毁引擎模块
*/
KBE_DLL_API bool kbe_init();
KBE_DLL_API bool kbe_destroy();

/**
	产生一个uint64位的唯一值(注意：仅当前app中产生是唯一的)
*/
KBE_DLL_API KBEngine::uint64 kbe_genUUID64(); 

/**
	休眠
*/
KBE_DLL_API void kbe_sleep(KBEngine::uint32 ms); 

/**
	获得当前系统时间， 毫秒
*/
KBE_DLL_API KBEngine::uint32 kbe_getSystemTime();

/**
	登录服务器
*/
KBE_DLL_API bool kbe_login(const char* accountName, const char* passwd, const KBEngine::uint8* datas = NULL, KBEngine::uint32 datasize = 0,
						   const char* ip = NULL, KBEngine::uint32 port = 0);

/**
	更新引擎状态
*/
KBE_DLL_API void kbe_update();

/**
	引擎锁， 防止多线程下访问脚本等出错。
	主要针对python
*/
KBE_DLL_API void kbe_lock();
KBE_DLL_API void kbe_unlock();

/**
	告诉引擎渲染层在处理中
*/
KBE_DLL_API void kbe_inProcess(bool v);

/**
	获取最后一次使用的账号
*/
KBE_DLL_API const char* kbe_getLastAccountName();

/**
	得到player的当前ID
*/
KBE_DLL_API KBEngine::ENTITY_ID kbe_playerID();

/**
	得到player的当前dbid
*/
KBE_DLL_API KBEngine::DBID kbe_playerDBID();

/**
	更新player的坐标与朝向
*/
KBE_DLL_API void kbe_updateVolatile(KBEngine::ENTITY_ID eid, float x, float y, float z, float yaw, float pitch, float roll);

/**
	注册一个事件handle来监听引擎产生的事件
	然后根据事件可以做相应的表现
*/
KBE_DLL_API bool kbe_registerEventHandle(KBEngine::EventHandle* pHandle);
KBE_DLL_API bool kbe_deregisterEventHandle(KBEngine::EventHandle* pHandle);

/**
	调用脚本entity的方法 
*/
KBE_DLL_API void kbe_callEntityMethod(KBEngine::ENTITY_ID entityID, const char *method, 
										   const char* strargs); 


/**
	触发事件到脚本
	可以触发键盘事件
	鼠标点击和移动事件等
*/
KBE_DLL_API void kbe_fireEvent(const char *eventID, PyObject *args); 


/**
	获得用户脚本资源根目录
*/
KBE_DLL_API const char* kbe_getPyUserResPath();

#endif // __KBENGINE_DLL__
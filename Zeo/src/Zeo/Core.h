#pragma once

#include<memory>

#ifdef ZO_PLATFORM_WINDOWS
#if ZO_DYNAMIC_LINK
	#ifdef ZO_BUILD_DLL
		#define ZEO_API __declspec(dllexport)
	#else		
		#define ZEO_API __declspec(dllimport)
	#endif // ZO_BULID_DLL 
#else
	#define ZEO_API
#endif
#else	
	#error Zeo only supports Windows!
#endif // ZO_PLATFORM_WINDOWS

#ifdef ZO_DEBUG
	#define ZO_ENABLE_ASSERSTS
#endif

#ifdef ZO_ENABLE_ASSERSTS
	#define ZO_ASSERT(x, ...) { if(!(x)) { ZO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ZO_CORE_ASSERT(x, ...) { if(!(x)) { ZO_CORE_ERROR("Assertion Faild: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define ZO_ASSERT(x, ...)
	#define ZO_CORE_ASSERT(x, ...)
#endif // ZO_ENABLE_ASSERSTS


#define BIT(x) (1 << x)//��������һ�������ض�λ��bit������Ϊ1������ֵ����λ��λ���ɲ��� x ָ��������һ��λ�����ĳ����÷���ͨ���������á�����������ض�λ��״̬��

#define ZO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Zeo {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
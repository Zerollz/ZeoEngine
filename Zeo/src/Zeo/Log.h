#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Zeo {

	class ZEO_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define ZO_CORE_TRACE(...)		::Zeo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZO_CORE_INFO(...)		::Zeo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZO_CORE_WARN(...)		::Zeo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZO_CORE_ERROR(...)		::Zeo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZO_CORE_FATAl(...)		::Zeo::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//�����Ļ����԰�����װ����һ�����У�ֻ���ض�������²����������������ڷ��а汾��ȥ�����е���־��Ϣ��

//Client log macros
#define ZO_TRACE(...)			::Zeo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZO_INFO(...)			::Zeo::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZO_WARN(...)			::Zeo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZO_ERROR(...)			::Zeo::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZO_FATAl(...)			::Zeo::Log::GetClientLogger()->fatal(__VA_ARGS__)
//���þ�̬������ȡloggerָ���еĸ��ֺ�����
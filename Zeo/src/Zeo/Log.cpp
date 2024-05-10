#include "zopch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zeo {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		//����ģʽ����ʹ����ȷ����ɫ������ʱ�������־����ʵ�ʵ���־��Ϣ������ֻ����ʱ�������־����ʵ�ʵ���Ϣ
		s_CoreLogger = spdlog::stdout_color_mt("ZEO");
		s_CoreLogger->set_level(spdlog::level::trace);//������ɫ����

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
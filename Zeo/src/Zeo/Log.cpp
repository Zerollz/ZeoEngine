#include "zopch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zeo {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		//设置模式，会使用正确的颜色，还有时间戳、日志名、实际的日志信息。这里只用了时间戳、日志名和实际的信息
		s_CoreLogger = spdlog::stdout_color_mt("ZEO");
		s_CoreLogger->set_level(spdlog::level::trace);//设置颜色级别

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
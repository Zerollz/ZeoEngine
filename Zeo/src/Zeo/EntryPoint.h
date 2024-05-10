#pragma once

#ifdef ZO_PLATFORM_WINDOWS

extern Zeo::Application* Zeo::CreateApplication();

int main(int argc, char** argv)
{
	Zeo::Log::Init();
	ZO_CORE_WARN("Initialized Log!");

	auto app = Zeo::CreateApplication();
	app->Run();
	delete app;
}

#endif // ZO_PLATFORM_WINDOWS

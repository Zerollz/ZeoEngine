#pragma once

#include "Core.h"

#include "Window.h"
#include "Zeo/LayerStack.h"
#include "Zeo/Events/Event.h"
#include "Zeo/Events/ApplicationEvent.h"

#include "Zeo/Core/TimeStep.h"

#include "Zeo/ImGui/ImGuiLayer.h"

#include "Zeo/Renderer/Shader.h"
#include "Zeo/Renderer/Buffer.h"
#include "Zeo/Renderer/VertexArray.h"
#include "Zeo/Renderer/OrthographicCamera.h"

namespace Zeo {

	class ZEO_API Application
	{
	public:
		Application();
		virtual ~Application();//设置为虚函数，因为会被Sandbox继承

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		float m_LastFrameTime = 0.0f;
	private:	 
		static Application* s_Instance;
	};

	//To be define in CLIENT
	Application* CreateApplication();

}



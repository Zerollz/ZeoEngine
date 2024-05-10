#pragma once

#include "Zeo/Layer.h"

#include "Zeo/Events/ApplicationEvent.h"
#include "Zeo/Events/KeyEvent.h"
#include "Zeo/Events/MouseEvent.h"

namespace Zeo {

	class ZEO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
#pragma once

#include "RenderCommand.h"

#include "Zeo/Renderer/OrthographicCamera.h"
#include "Zeo/Renderer/Shader.h"

namespace Zeo {

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void Endscene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_Scenedata;
	};
}
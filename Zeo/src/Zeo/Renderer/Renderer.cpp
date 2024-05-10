#include "zopch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Zeo {
	Renderer::SceneData* Renderer::m_Scenedata = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_Scenedata->ViewProjectionMatrix = camera.GetViewProjectMatrix();
	}

	void Renderer::Endscene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_Scenedata->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
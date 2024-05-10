#include <Zeo.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Zeo::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Zeo::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Zeo::Ref<Zeo::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Zeo::VertexBuffer::Create(vertices, sizeof(vertices)));

		Zeo::BufferLayout layout = {
			{ Zeo::ShaderDataType::Float3, "a_Position" },
			{ Zeo::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Zeo::Ref<Zeo::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Zeo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(Zeo::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};//顶点坐标加上纹理坐标

		Zeo::Ref<Zeo::VertexBuffer> squareVB;
		squareVB.reset(Zeo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Zeo::ShaderDataType::Float3, "a_Position" },
			{ Zeo::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Zeo::Ref<Zeo::IndexBuffer> squareIB;
		squareIB.reset(Zeo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Zeo::Shader::Create(vertexSrc, fragmentSrc));

		Shader::Create("assest/shaders/Texture.glsl");

		std::string vertexSrcSq = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcSq = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = u_Color;
			}
		)";

		m_ShaderSq.reset(Zeo::Shader::Create(vertexSrcSq, fragmentSrcSq));


		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Zeo::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Zeo::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Zeo::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Zeo::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Zeo::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Zeo::TimeStep ts) override
	{
		ZO_TRACE("time {0}s, {1}ms", ts.GetSeconds(), ts.GetMilliseconds());
		if (Zeo::Input::IsKeyPressed(ZO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Zeo::Input::IsKeyPressed(ZO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Zeo::Input::IsKeyPressed(ZO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Zeo::Input::IsKeyPressed(ZO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Zeo::Input::IsKeyPressed(ZO_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Zeo::Input::IsKeyPressed(ZO_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		Zeo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Zeo::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Zeo::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Zeo::OpenGLShader>(m_ShaderSq)->Bind();
		std::dynamic_pointer_cast<Zeo::OpenGLShader>(m_ShaderSq)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y*0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Zeo::Renderer::Submit(m_ShaderSq, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Zeo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Zeo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		//三角形
		//Zeo::Renderer::Submit(m_Shader, m_VertexArray);

		Zeo::Renderer::Endscene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Zeo::Event& event) override
	{

	}

private:
	Zeo::Ref<Zeo::Shader> m_Shader;
	Zeo::Ref<Zeo::VertexArray> m_VertexArray;

	Zeo::Ref<Zeo::Shader> m_ShaderSq, m_TextureShader;
	Zeo::Ref<Zeo::VertexArray> m_SquareVA;

	Zeo::Ref<Zeo::Texture2D> m_Texture, m_ChernoLogoTexture;

	Zeo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.7f , 1.0f };

};

class Sandbox : public Zeo::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Zeo::Application* Zeo::CreateApplication()
{
	return new Sandbox();
}
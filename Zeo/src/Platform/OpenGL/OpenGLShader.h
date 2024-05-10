#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Zeo/Renderer/Shader.h>

namespace Zeo {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformMat3(const char* name, const glm::mat3& matrix);
		void UploadUniformMat4(const char* name, const glm::mat4& matrix);

		void UploadUniformInt(const char* name, int values);

		void UploadUniformFloat(const char* name, float values);
		void UploadUniformFloat2(const char* name, const glm::vec2& values);
		void UploadUniformFloat3(const char* name, const glm::vec3& values);
		void UploadUniformFloat4(const char* name, const glm::vec4& values);
	private:
		void Compile();
	private:
		uint32_t m_RendererID;
	};
}
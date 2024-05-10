#include "zopch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Zeo {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
#pragma once

#include <GL/glew.h>

#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/Shader.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"


namespace Engine {
	class Renderer {

	public:
		Renderer();

		void Clear();
		//void ClearColor(Color rgba);
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}
#include "Renderer.h"

#include <iostream>

#include "../debug/GLCall.h"

namespace Engine {
	Renderer::Renderer() {

	}

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		//bind all
		va.Bind();
		ib.Bind();
		shader.Bind();

		//draw elements
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}
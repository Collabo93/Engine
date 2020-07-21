#include "VertexBuffer.h"

#include "../debug/GLCall.h"
#include "VertexBufferLayout.h"

namespace Engine {

	VertexBuffer::VertexBuffer(unsigned int size) {
		GLCall(glGenBuffers(1, &n_RenderID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, n_RenderID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		GLCall(glGenBuffers(1, &n_RenderID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, n_RenderID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &n_RenderID));
	}

	void VertexBuffer::PopData(const void* positions, unsigned int size) {
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, positions));
	}

	void VertexBuffer::Bind()const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, n_RenderID));
	}

	void VertexBuffer::Unbind()const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
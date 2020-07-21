#include "IndexBuffer.h"

#include "../debug/GLCall.h"

namespace Engine {

	IndexBuffer::IndexBuffer(unsigned int count) :n_count(count) {
		ASSERT(sizeof(unsigned int) == sizeof(GLuint)); //Plattform check - unsigned int 4 bytes?

		GLCall(glGenBuffers(1, &n_RenderID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n_RenderID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW));
	}

	IndexBuffer::IndexBuffer(const void* data, unsigned int count) :n_count(count) {
		ASSERT(sizeof(unsigned int) == sizeof(GLuint)); //Plattform check - unsigned int 4 bytes?

		GLCall(glGenBuffers(1, &n_RenderID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n_RenderID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &n_RenderID));
	}

	void IndexBuffer::PopData(const void* positions, unsigned int size) {
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, positions));
	}

	void IndexBuffer::Bind()const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n_RenderID));
	}

	void IndexBuffer::Unbind()const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}
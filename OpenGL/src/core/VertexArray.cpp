#include "VertexArray.h"

#include "../debug/GLCall.h"
#include "VertexBufferLayout.h"


namespace Engine {

	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &n_RenderID));
	}

	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &n_RenderID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int n_offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.n_count, element.n_type, element.c_normalized, layout.GetStride(), (const void*)n_offset));

			n_offset += element.n_count * VertexBufferElement::n_GetSizeOfType(element.n_type);
		}
	}

	void VertexArray::Bind()const {
		GLCall(glBindVertexArray(n_RenderID));
	}
	void VertexArray::Unbind()const {
		GLCall(glBindVertexArray(0));
	}
}
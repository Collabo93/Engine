#pragma once
#include <vector>
#include <GL\glew.h>

#include "../debug/GLCall.h"

namespace Engine {

	struct VertexBufferElement {
		unsigned int n_type;
		unsigned int n_count;
		unsigned char c_normalized;

		static unsigned int n_GetSizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT:return 4;
			case GL_UNSIGNED_INT:return 4;
			case GL_UNSIGNED_BYTE:return 1;
			}
			ASSERT(false);
			return 0;
		}
	};

	class VertexBufferLayout {
	private:

		std::vector<VertexBufferElement> vElements;
		unsigned int n_Stride;

	public:
		VertexBufferLayout()
			:n_Stride(0) {}

		template <typename T> void Push(unsigned int count) {
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count) {
			vElements.push_back({ GL_FLOAT,count,GL_FALSE });
			n_Stride += VertexBufferElement::n_GetSizeOfType(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned int>(unsigned int count) {
			vElements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
			n_Stride += VertexBufferElement::n_GetSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count) {
			vElements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
			n_Stride += VertexBufferElement::n_GetSizeOfType(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexBufferElement> GetElements() const {
			return vElements;
		}
		inline unsigned int GetStride() const {
			return n_Stride;
		}
	};
}

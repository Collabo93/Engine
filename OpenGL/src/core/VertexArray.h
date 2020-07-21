#pragma once

#include "VertexBuffer.h"

namespace Engine {

	class VertexBufferLayout; // to avoid loop with renderer

	class VertexArray {
	private:
		unsigned int n_RenderID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind()const;
		void Unbind()const;
	};
}
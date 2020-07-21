#pragma once

namespace Engine {

	class VertexBuffer {
	private:
		unsigned int n_RenderID;

	public:
		VertexBuffer(unsigned int size);
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void PopData(const void* positions, unsigned int size);

		void Bind()const;
		void Unbind()const;
	};
}
#pragma once

namespace Engine {

	class IndexBuffer {
	private:
		unsigned int n_RenderID;
		unsigned int n_count;

	public:
		IndexBuffer(unsigned int count);
		IndexBuffer(const void* data, unsigned int count);
		~IndexBuffer();

		void PopData(const void* positions, unsigned int size);

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const { return n_count; }
	};
}
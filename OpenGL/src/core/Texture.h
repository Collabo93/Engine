#pragma once

#include <iostream>

namespace Engine {

	class Texture {
	private:
		unsigned int n_RenderID;
		std::string s_FilePath;
		unsigned char* c_LocalBuffer;
		int nWidth, nHeight, nBPP; //bits per pixel

	public:
		Texture(const std::string& path, unsigned int slot = 0);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind();

		inline int GetWidth() const { return nWidth; }
		inline int GetHeigth() const { return nHeight; }

		unsigned int GetRenderID() { return n_RenderID; }
	};
}
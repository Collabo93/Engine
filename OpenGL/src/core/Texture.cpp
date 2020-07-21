#include "Texture.h"
#include "../debug/GLCall.h"

#include "../vendor/stb_image/stb_image.h"

namespace Engine {

	Texture::Texture(const std::string& path, unsigned int slot) :n_RenderID(0), s_FilePath(path), c_LocalBuffer(nullptr), nWidth(0), nHeight(0), nBPP(0) {

		//stbi_set_flip_vertically_on_load(1); //flip top left
		c_LocalBuffer = stbi_load(path.c_str(), &nWidth, &nHeight, &nBPP, 4);

		GLCall(glGenTextures(1, &n_RenderID));
		//GLCall(glBindTexture(GL_TEXTURE_2D, n_RenderID));

		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, n_RenderID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, c_LocalBuffer));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (c_LocalBuffer)
			stbi_image_free(c_LocalBuffer);
	}

	Texture::~Texture() {
		GLCall(glDeleteTextures(1, &n_RenderID));
	}

	void Texture::Bind(unsigned int slot) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, n_RenderID));
	}

	void Texture::Unbind() {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
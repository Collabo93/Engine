#pragma once

#include <memory>

#include "../core/VertexArray.h"
#include "../core/VertexBuffer.h"
#include "../core/IndexBuffer.h"
#include "../core/Shader.h"
#include "../core/VertexBufferLayout.h"
#include "../core/Texture.h"
		  
#include "Renderer.h"

namespace Engine {

	struct Color {
		float r, g, b, a;
	};

	class Renderer2D {

		struct Vec2 {
			float x, y;
		};
		struct Vec3 {
			float x, y, z;
		};
		struct Vec4 {
			float x, y, z, w;

		};

		struct  Vertex {
			Vec3 Position;
			Vec4 Color;
			Vec2 TexCoords;
			float TexID;
		};

	private:
		std::unique_ptr<VertexArray> va;
		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr<VertexBufferLayout> vbl;
		std::unique_ptr<IndexBuffer> ib;
		std::unique_ptr<Shader> shader;
		std::vector<std::unique_ptr<Texture>> texture;
		//Texture texture [std::unique_ptr<Texture>];
		std::unique_ptr<Renderer> renderer;

		const uint32_t nMaxQuads = 524288;
		const uint32_t nMaxPositions = nMaxQuads * 4;
		const uint32_t nMaxIndicies = nMaxQuads * 6;
		static const uint32_t nMaxTextureSlots = 32;

		std::string TextureSlots[nMaxTextureSlots];
		uint32_t TextureSlotIndex = 1; //0 = Color

		glm::mat4 projection, view;

		uint32_t nScreenWidth = 256;
		uint32_t nScreenHeight = 240;

		std::vector<std::vector<Vertex>> vQuads;
		std::vector<int> vIndicies;
		std::vector<Vertex> vVerticies; //helper for vQuads

	public:
		Renderer2D(unsigned int ScreenWidth, unsigned int ScreenHeight);
		~Renderer2D();

		void CreateColorQuad(float x, float y, float width, float heigth, Color color = { 0.18f, 0.6f, 0.96f, 1.0f });
		void CreateTextureQuad(float x, float y, float width, float heigth, std::string texturePath);
		void DrawAll();
	};
}
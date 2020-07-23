#include "Renderer2D.h"

#include <iostream>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include <array>
#include <fstream>

namespace Engine {

	Renderer2D::Renderer2D(unsigned int ScreenWidth, unsigned int ScreenHeight)
		: projection(glm::ortho(0.0f, (float)ScreenWidth, (float)ScreenHeight, 0.0f, -1.0f, 1.0f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {

		renderer = std::make_unique<Renderer>();
		va = std::make_unique<VertexArray>();
		vb = std::make_unique<VertexBuffer>(sizeof(Vertex) * nMaxPositions);

		vbl = std::make_unique<VertexBufferLayout>();
		vbl->Push<float>(3); //positions
		vbl->Push<float>(4); //color
		vbl->Push<float>(2); //texture
		vbl->Push<float>(1); //texture ID

		va->AddBuffer(*vb, *vbl);

		ib = std::make_unique<IndexBuffer>(sizeof(Vertex) * nMaxIndicies);

		shader = std::make_unique<Shader>("res/shaders/Texture.shader");
		shader->Bind();

		for (uint32_t i = 0; i < nMaxTextureSlots; i++) {
			TextureSlots[i] = "";
		}
		int sampler[nMaxTextureSlots];
		for (uint32_t i = 0; i < nMaxTextureSlots; i++) {
			sampler[i] = i;
		}
		shader->SetUniform1iv("u_Texture", nMaxTextureSlots, sampler);

		texture.push_back(nullptr);
	}
	Renderer2D::~Renderer2D() {

	}

	void Renderer2D::CreateColorQuad(float x, float y, float width, float heigth, Color color) {
		Vertex v0;
		v0.Position = { x,y,0.0f };
		v0.Color = { color.r,color.g, color.b,color.a };
		v0.TexCoords = { 0.0f,0.0f };
		v0.TexID = 0.0f;

		Vertex v1;
		v1.Position = { x + width,y,0.0f };
		v1.Color = { color.r,color.g, color.b,color.a };
		v1.TexCoords = { 1.0f,0.0f };
		v1.TexID = 0.0f;

		Vertex v2;
		v2.Position = { x + width,y + heigth,0.0f };
		v2.Color = { color.r,color.g, color.b,color.a };
		v2.TexCoords = { 1.0f,1.0f };
		v2.TexID = 0.0f;

		Vertex v3;
		v3.Position = { x,y + heigth,0.0f };
		v3.Color = { color.r,color.g, color.b,color.a };
		v3.TexCoords = { 0.0f,1.0f };
		v3.TexID = 0.0f;

		vQuads.push_back({ v0,v1,v2,v3 });

		uint32_t QuadsCount = vQuads.size() - 1;
		vIndicies.push_back(QuadsCount * 4 + 0);
		vIndicies.push_back(QuadsCount * 4 + 1);
		vIndicies.push_back(QuadsCount * 4 + 3);
		vIndicies.push_back(QuadsCount * 4 + 1);
		vIndicies.push_back(QuadsCount * 4 + 2);
		vIndicies.push_back(QuadsCount * 4 + 3);
	}

	void Renderer2D::CreateTextureQuad(float x, float y, float width, float heigth, std::string texturePath) {
		float textureIndex = 0.0f;

		std::ifstream ifile;
		ifile.open(texturePath);
		if (!ifile)
			texturePath = noTexturePath;

		for (uint32_t i = 1; i < TextureSlotIndex; i++) {
			if (TextureSlots[i] == texturePath) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)TextureSlotIndex;
			TextureSlots[TextureSlotIndex] = texturePath;
			auto generateTexture = std::make_unique<Engine::Texture>(texturePath, TextureSlotIndex);
			texture.push_back(std::move(generateTexture));
			texture[textureIndex]->Bind(TextureSlotIndex);
			TextureSlotIndex++;
		}

		Vertex v0;
		v0.Position = { x,y,0.0f };
		v0.Color = { 0.0f,0.0f, 0.0f,0.0f };
		v0.TexCoords = { 0.0f,0.0f };
		v0.TexID = textureIndex;

		Vertex v1;
		v1.Position = { x + width,y,0.0f };
		v1.Color = { 0.0f,0.0f, 0.0f,0.0f };
		v1.TexCoords = { 1.0f,0.0f };
		v1.TexID = textureIndex;

		Vertex v2;
		v2.Position = { x + width,y + heigth,0.0f };
		v2.Color = { 0.0f,0.0f, 0.0f,0.0f };
		v2.TexCoords = { 1.0f,1.0f };
		v2.TexID = textureIndex;

		Vertex v3;
		v3.Position = { x,y + heigth,0.0f };
		v3.Color = { 0.0f,0.0f, 0.0f,0.0f };
		v3.TexCoords = { 0.0f,1.0f };
		v3.TexID = textureIndex;

		vQuads.push_back({ v0,v1,v2,v3 });

		uint32_t QuadsCount = vQuads.size() - 1;
		vIndicies.push_back(QuadsCount * 4 + 0);
		vIndicies.push_back(QuadsCount * 4 + 1);
		vIndicies.push_back(QuadsCount * 4 + 3);
		vIndicies.push_back(QuadsCount * 4 + 1);
		vIndicies.push_back(QuadsCount * 4 + 2);
		vIndicies.push_back(QuadsCount * 4 + 3);
	}

	bool Renderer2D::DrawAll() {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 mvp = projection * view * model;

		for (uint32_t i = 0; i < vQuads.size(); i++)
		{
			for (uint32_t z = 0; z < vQuads[i].size(); z++)
			{
				vVerticies.push_back(vQuads[i][z]);
			}
		}

		if (vVerticies.size() <= nMaxPositions){
			vb->PopData(&vVerticies[0], vVerticies.size() * sizeof(Vertex));
		}
		else{
			std::cout << "Warning: maximum Verticies reached" << std::endl;
			return false;
		}

		if (vIndicies.size() <= nMaxIndicies){
			ib->PopData(&vIndicies[0], vIndicies.size() * sizeof(int));
		}
		else{
			std::cout << "Warning: maximum Indicies reached" << std::endl;
			return false;
		}

		shader->SetUniformMat4f("u_MVP", mvp);

		renderer->Draw(*va, *ib, *shader);

		vQuads.clear();
		vIndicies.clear();
		vVerticies.clear();

		return true;
	}
}
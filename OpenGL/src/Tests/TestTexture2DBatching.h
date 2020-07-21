#pragma once

#include "Test.h"

#include "../renderer/Renderer2D.h"

#include <memory>

namespace test {
	class TestTexture2DBatching : public Test {
	private:
		void BatchRectangle();
	public:
		TestTexture2DBatching();
		~TestTexture2DBatching();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Engine::Renderer2D> Renderer2D;

		glm::mat4 projection,view;
		glm::vec3 translationA, translationB;
		float x = 1, y = 1, width = 20, height = 20;
		float screenWidth, screenHeight;

		std::vector<float> vPositions;
		std::vector<unsigned int> vIndecies;
	};
}
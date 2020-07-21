#pragma once

#include "Test.h"

#include "../renderer/Renderer2D.h"

#include <memory>

namespace test {
	class TestRectangle : public Test {
	public:
		TestRectangle();
		~TestRectangle();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Engine::Renderer2D> Renderer2D;

		glm::mat4 projection,view;
		glm::vec3 translationA;
		float x = 20, y = 20, width = 200, height = 200;

		int iWidth, iHeigth;
	};
}
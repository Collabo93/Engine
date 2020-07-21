#include "TestTexture2DBatching.h"

#include "../vendor/imgui/imgui.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../renderer/Renderer.h"

namespace test {


	TestTexture2DBatching::TestTexture2DBatching()
		:translationA(0, 0, 0),
		projection(glm::ortho(0.0f, 1024.0f, 512.0f, 0.0f, -1.0f, 1.0f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {

		screenWidth = 1024;
		screenHeight = 512;

		Renderer2D = std::make_unique<Engine::Renderer2D>(screenWidth, screenHeight);
	}
	TestTexture2DBatching::~TestTexture2DBatching() {

	}

	void TestTexture2DBatching::OnUpdate(float deltaTime) {

	}
	void TestTexture2DBatching::OnRender() {
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Engine::Renderer renderer;
		{
			BatchRectangle();
			Renderer2D->DrawAll();

		}
	}
	void TestTexture2DBatching::OnImGuiRender() {
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1024);
	}

	void TestTexture2DBatching::BatchRectangle() {
		int currentWidth = x, currentHeigth = y;




		while (currentHeigth + y + height < screenHeight) {
			while (currentWidth + x + width < screenWidth) {
				Renderer2D->CreateTextureQuad(currentWidth, currentHeigth, width, height, "res/textures/ground1.png");

				currentWidth += width + x;
			}
			currentWidth = x;
			currentHeigth += height + y;
		}
	}
}
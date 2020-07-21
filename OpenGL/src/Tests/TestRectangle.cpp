#include "TestRectangle.h"

#include "../vendor/imgui/imgui.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../renderer/Renderer.h"

namespace test {


	TestRectangle::TestRectangle()
		:translationA(0, 0, 0),
		projection(glm::ortho(0.0f, 1024.0f, 512.0f, 0.0f, -1.0f, 1.0f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {

		Renderer2D = std::make_unique<Engine::Renderer2D>(1024,512);
	}

	TestRectangle::~TestRectangle() {
	}

	void TestRectangle::OnUpdate(float deltaTime) {

	}
	void TestRectangle::OnRender() {
		Renderer2D->CreateColorQuad(translationA.x, translationA.y, 100, 100, { 0.2f,0.8f,0.8f,1.0f });
		Renderer2D->DrawAll();
	}
	void TestRectangle::OnImGuiRender() {
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1024);
	}
}
#include "TestClearColor.h"

#include "../vendor/imgui/imgui.h"
#include "../debug/GLCall.h"

namespace test {


	TestClearColor::TestClearColor() :fClearColor{ 0.1f,0.1f,0.1f,1.0f } {

	}
	TestClearColor::~TestClearColor() {

	}

	void TestClearColor::OnUpdate(float deltaTime) {

	}
	void TestClearColor::OnRender() {
		GLCall(glClearColor(fClearColor[0], fClearColor[1], fClearColor[2], fClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", fClearColor);
	}
}
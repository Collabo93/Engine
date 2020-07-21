#include "Test.h"
#include "../vendor/imgui/imgui.h"

namespace test {
	TestMenu::TestMenu(Test*& currenTestPointer) :m_CurrentTest(currenTestPointer) {

	}

	void TestMenu::OnImGuiRender() {
		for (auto& test : v_Test) {
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}
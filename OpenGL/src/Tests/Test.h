#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu :public Test {
	public:
		TestMenu(Test*& currenTestPointer);

		virtual void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test: " << name << std::endl;
			v_Test.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> v_Test;

		float fWidth, fHeight;
	};
}
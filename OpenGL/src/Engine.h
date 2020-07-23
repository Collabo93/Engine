#pragma once

#ifndef ENGINE_PGE_DEF
#define ENGINE_PGE_DEF

//includes
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <atomic>
#include <vector>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "Tests/TestClearColor.h"
#include "Tests/TestRectangle.h"
#include "Tests/TestTexture2DBatching.h"

#include "renderer/Renderer.h"
#include "renderer/Renderer2D.h"

namespace Engine {

	//Engine state 
	enum rcode
	{
		FAIL = 0,
		OK = 1
	};

	class GameEngine {

	private:
		//Window variables
		GLFWwindow* window;
		uint32_t nScreenWidth = 256;
		uint32_t nScreenHeight = 240;
		const char* sTitle = "Undefinded";
		bool bVsync = false;

		// false = end programm
		bool bOnUpdateActive = true;

		//Test Menu
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);

		//Renderer
		Renderer* renderer;
		Renderer2D* renderer2D;

		//Color
		Color defaultColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		Color turquoise = { 26 / 255.0, 188 / 255.0, 156 / 255.0,1.0 };
		Color emerald = { 46 / 255.0, 204 / 255.0, 156 / 113,1.0 };
		Color river = { 52 / 255.0, 152 / 255.0, 219 / 255.0,1.0 };
		Color amethyst = { 155 / 255.0, 89 / 255.0, 182 / 255.0,1.0 };
		Color asphalt = { 52 / 255.0, 73 / 255.0, 94 / 255.0,1.0 };

		Color sun = { 241 / 255.0, 196 / 255.0, 15 / 255.0,1.0 };
		Color carrot = { 230 / 255.0, 126 / 255.0, 34 / 255.0,1.0 };
		Color alizarin = { 26 / 255.0, 188 / 255.0, 156 / 255.0,1.0 };
		Color clouds = { 236 / 255.0, 240 / 255.0, 241 / 255.0,1.0 };
		Color concret = { 149 / 255.0, 165 / 255.0, 166 / 255.0,1.0 };

		Color white = { 1.0,1.0,1.0,1.0 };
		Color sunAlpha = { 236 / 255.0, 240 / 255.0, 241 / 255.0,0.6 };

	public:
		Engine::rcode Create(uint32_t screen_w, uint32_t screen_h, const char* title, bool vsync);
		Engine::rcode Start();

		GameEngine();
		~GameEngine();

		//User methods
		virtual bool OnCreate();
		virtual bool OnUpdate(float fElapsedTime);

		//Init a frame
		void StartTests();
		void Start2DRenderer();

		//events
		double GetMouseX();
		double GetMouseY();
		uint32_t GetWindowWidth() { return nScreenWidth; }
		uint32_t GetWindowHeight() { return nScreenHeight; }

		//Create 2D Quad
		void CreateColorQuad(float x, float y, float width, float heigth, Color color);
		void CreateColorQuad(float x, float y, float width, float heigth, std::string colorName = "default");
		void CreateTextureQuad(float x, float y, float width, float heigth, std::string texturePath);

		//Draw everything in the buffer
		Engine::rcode DrawAll();

	private:
		//After creation
		void InitDependencies();
		void EngineThread();
	};
}
#endif

#ifdef ENGINE_PGE_APPLICATION
#undef ENGINE_PGE_APPLICATION
namespace Engine {

	GameEngine::GameEngine() {
		currentTest = testMenu;


	}
	GameEngine::~GameEngine() {
		delete renderer;
	}

	Engine::rcode GameEngine::Create(uint32_t screen_w, uint32_t screen_h, const char* title, bool vsync) {
		nScreenWidth = screen_w;
		nScreenHeight = screen_h;
		sTitle = title;
		bVsync = vsync;

		if (nScreenWidth == 0 || nScreenHeight == 0)
			return Engine::FAIL;

		return Engine::OK;
	}



	/*
	##########################################
	############## OpenGL init ###############
	##########################################
	*/
	Engine::rcode GameEngine::Start() {
		//GL library check
		if (!glfwInit())
			return Engine::FAIL;

		// Min + Max version to 3.3
		//Vertex Array implementation
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//window creation and check
		window = glfwCreateWindow(nScreenWidth, nScreenHeight, sTitle, NULL, NULL);
		if (!window) {
			glfwTerminate();
			return Engine::FAIL;
		}

		glfwMakeContextCurrent(window); //GLCall cant be applied here

		if (bVsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		//glew library check
		if (glewInit() != GLEW_OK)
			return Engine::FAIL;
		std::cout << glGetString(GL_VERSION) << std::endl;

		InitDependencies();
		bOnUpdateActive = true;
		EngineThread();

		return Engine::OK;
	}



	/*
	##########################################
	############## Dependecies ###############
	##########################################
	*/
	void GameEngine::InitDependencies() {
		const char* glsl_version = "#version 130";

		//ImGui init
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		//blending init
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}



	/*
	##########################################
	############## Engine Loop ###############
	##########################################
	*/
	void GameEngine::EngineThread() {
		{
			std::cout << "id" << std::this_thread::get_id() << std::endl;

			if (!OnCreate())
				bOnUpdateActive = false;

			auto tp1 = std::chrono::system_clock::now();
			auto tp2 = std::chrono::system_clock::now();

			while (bOnUpdateActive && !glfwWindowShouldClose(window)) {

				tp2 = std::chrono::system_clock::now();
				std::chrono::duration<float> elapsedTime = tp2 - tp1;
				tp1 = tp2;
				float fElapsedTime = elapsedTime.count();

				GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
				renderer->Clear();

				if (!OnUpdate(fElapsedTime))
					bOnUpdateActive = false;

				/* Swap front and back buffers */
				GLCall(glfwSwapBuffers(window));

				/* Poll for and process events */
				GLCall(glfwPollEvents());
			}
			delete currentTest;
			if (currentTest != testMenu)
				delete testMenu;
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();

		return;
	}



	/*
	##########################################
	########### User entry point #############
	##########################################
	*/
	bool GameEngine::OnCreate() {
		return false;
	}
	bool GameEngine::OnUpdate(float fElapsedTime) {
		UNUSED(fElapsedTime);  return false;
	}



	/*
	##########################################
	############## TestFrame #################
	##########################################
	*/
	void GameEngine::StartTests() {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest) {
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (currentTest != testMenu && ImGui::Button("<-")) {
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}



	/*
	##########################################
	############## 2DRenderer ################
	##########################################
	*/
	void GameEngine::Start2DRenderer() {
		renderer2D = new Renderer2D(nScreenWidth, nScreenHeight);
	}
	void GameEngine::CreateColorQuad(float x, float y, float width, float heigth, Color color) {
		renderer2D->CreateColorQuad(x, y, width, heigth, color);
	}

	//TODO: find another way to implement colors
	void GameEngine::CreateColorQuad(float x, float y, float width, float heigth, std::string colorName) {
		if (colorName == "turquoise")
			renderer2D->CreateColorQuad(x, y, width, heigth, turquoise);
		else if (colorName == "emerald")
			renderer2D->CreateColorQuad(x, y, width, heigth, emerald);
		else if (colorName == "river")
			renderer2D->CreateColorQuad(x, y, width, heigth, river);
		else if (colorName == "amethyst")
			renderer2D->CreateColorQuad(x, y, width, heigth, amethyst);
		else if (colorName == "asphalt")
			renderer2D->CreateColorQuad(x, y, width, heigth, asphalt);
		else if (colorName == "sun")
			renderer2D->CreateColorQuad(x, y, width, heigth, sun);
		else if (colorName == "carrot")
			renderer2D->CreateColorQuad(x, y, width, heigth, carrot);
		else if (colorName == "alizarin")
			renderer2D->CreateColorQuad(x, y, width, heigth, alizarin);
		else if (colorName == "clouds")
			renderer2D->CreateColorQuad(x, y, width, heigth, clouds);
		else if (colorName == "concret")
			renderer2D->CreateColorQuad(x, y, width, heigth, concret);
		else if (colorName == "white")
			renderer2D->CreateColorQuad(x, y, width, heigth, white);
		else if (colorName == "sunAlpha")
			renderer2D->CreateColorQuad(x, y, width, heigth, sunAlpha);
		else
			renderer2D->CreateColorQuad(x, y, width, heigth, defaultColor);
	}
	void GameEngine::CreateTextureQuad(float x, float y, float width, float heigth, std::string texturePath) {
		renderer2D->CreateTextureQuad(x, y, width, heigth, texturePath);
	}
	Engine::rcode GameEngine::DrawAll() {
		if (renderer2D->DrawAll()){
			return Engine::OK;
		}
		else{
			bOnUpdateActive = false;
			return Engine::FAIL;
		}
	}


	/*
	##########################################
	################# Events #################
	##########################################
	*/
	double GameEngine::GetMouseX() {
		double x;
		glfwGetCursorPos(window, &x, nullptr);
		return x;
	}
	double GameEngine::GetMouseY() {
		double y;
		glfwGetCursorPos(window, nullptr, &y);
		return y;
	}
}
#endif
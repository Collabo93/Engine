#define ENGINE_PGE_APPLICATION
#include "src/Engine.h";

class Quelle : public Engine::GameEngine {
public:
	Quelle() {

	}

	bool OnCreate() override {
		Start2DRenderer();
		return true;
	}

	bool OnUpdate(float fElapsedTime) override {


		CreateColorQuad(20, 20, 60, 60, "turquoise");
		CreateColorQuad(120, 20, 60, 60, "sun");
		CreateColorQuad(220, 20, 60, 60, "emerald");
		CreateColorQuad(320, 20, 60, 60, "river");
		CreateColorQuad(420, 20, 60, 60, "amethyst");
		CreateColorQuad(520, 20, 60, 60, "asphalt");
		CreateColorQuad(620, 20, 60, 60, "carrot");
		CreateColorQuad(720, 20, 60, 60, "alizarin");
		CreateColorQuad(820, 20, 60, 60, "clouds");
		CreateColorQuad(820, 20, 60, 60, "concret");

		CreateTextureQuad(20, 140, 240, 135, "res/textures/wall.jpg");
		CreateTextureQuad(300, 140, 240, 135, "res/textures/wall2.jpg");


		DrawAll();


		std::cout << "X: " << GetMouseX() << std::endl;
		std::cout << "Y: " << GetMouseY() << std::endl;


		//StartTests();
		return true;
	}
};

int main()
{
	Quelle game;
	if (game.Create(1024, 512, "Test", true))
		game.Start();
	return 0;
}
// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL_image.h>

#include "pch.h"
#include "Engine.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"

nc::Engine engine;
nc::GameObject player;
nc::Factory<nc::Object, std::string> objectFactory;


/*
void ExampleCode()
{
	SDL_Surface* surface = SDL_LoadBMP("sf2.bmp");
	if (surface == nullptr)
	{
		return 1;
	}
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect2;
	rect2.x = 20;
	rect2.y = 20;
	SDL_QueryTexture(texture2, NULL, NULL, &rect2.w, &rect2.h);
	SDL_RenderCopy(renderer, texture2, NULL, &rect2);


	//Create Textures
	int width = 128;
	int height = 128;

	SDL_Texture* texture1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];
	memset(pixels, 255, width * height * sizeof(Uint32));
	SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));

	//Draw
		for (size_t i = 0; i < width * height; i++)
		{
			Uint8 c = rand() % 256;
			pixels[i] = (c << 24 | c << 16 | c << 8);
		}

		SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));

		SDL_Rect rect;
		rect.x = 200;
		rect.y = 100;
		rect.w = width * 0.5f;
		rect.h = height * 0.5f;
		SDL_RenderCopy(renderer, texture1, NULL, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);


	nc::Timer timer;
	//Profile
	for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	std::cout << timer.ElapsedSeconds() << std::endl;

	angle += 180 * timer.DeltaTime();


		rapidjson::Document document;
	nc::json::Load("json.txt", document);

	std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "bool", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;
}
*/


int main(int, char**)
{


	engine.Startup();

	objectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	objectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
	objectFactory.Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);
	objectFactory.Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);

	nc::GameObject* player = objectFactory.Create<nc::GameObject>("GameObject");

	player->Create(&engine);

	rapidjson::Document document;

	nc::json::Load("player.txt", document);
	player->Read(document);


	nc::Component* component = objectFactory.Create<nc::Component>("PhysicsComponent");
	player->AddComponent(component);
	component->Create();

	component = objectFactory.Create<nc::Component>("SpriteComponent");
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	component = objectFactory.Create<nc::Component>("PlayerComponent");
	player->AddComponent(component);
	component->Create();

	//Texture
	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		//Pressing quit
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}

		//Update
		engine.Update();
		player->Update();

		/*if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESC) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}*/

		//Draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);

		//Render Sprite
		player->Draw();


		engine.GetSystem<nc::Renderer>()->EndFrame();

	}

	engine.Shutdown();

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

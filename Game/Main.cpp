// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL_image.h>

#include "pch.h"
#include "Engine.h"
#include "Core/Json.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "Components/PlayerComponent.h"
#include "TileMap.h"

nc::Engine engine;
nc::GameObject player;

nc::Scene scene;

/*
void ExampleCode()
{
			public:
			using function_t = std::function<TBase*()>;

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

	nc::ObjectFactory::Instance().Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	nc::ObjectFactory::Instance().Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
	nc::ObjectFactory::Instance().Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);


	if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESC) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

	nc::GameObject* player = nc::ObjectFactory::Instance().Create<nc::GameObject>("GameObject");

	player->Create(&engine);

	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
	component->Create(player);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
	component->Create(player);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
	component->Create(player);
	player->AddComponent(component);


	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
	{
		force = nc::Vector2::forward * 1000.0f;

	}

	force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));
}
*/


int main(int, char**)
{

	engine.Startup();


	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);

	
	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
	//	gameObject->m_transform.position = { nc::random(0, 800), nc::random(200, 400) };
	//	//gameObject->m_transform.angle = nc::random(0, 360);

	//	scene.AddGameObject(gameObject);
	//}


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
		scene.Update();
		
		//Draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
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

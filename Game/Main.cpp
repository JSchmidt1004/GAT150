// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"

nc::ResourceManager resourceManager;
nc::Renderer renderer;

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

}
*/

int main(int, char**)
{
	renderer.Startup();
	renderer.Create("Idk, I'm not good at names", 800, 600);

	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
	float angle = 0;


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

		renderer.BeginFrame();

		angle += 0.2f;
		texture1->Draw({ 500, 100 }, { 0.3f, 0.3f }, angle);
		texture2->Draw({ 200, 300 }, { 0.3f, 0.3f }, angle + 90);

		renderer.EndFrame();

	}

	renderer.Shutdown();
	SDL_Quit();

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

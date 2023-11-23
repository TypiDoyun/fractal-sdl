#include "mandelbrot.h"

using namespace std;

inline Uint32 makeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
    return (a << 24) + (r << 16) + (g << 8) + b;
}

Mandelbrot::Mandelbrot(SDL_Renderer* renderer)
	: renderer(renderer)
{
	window = SDL_RenderGetWindow(renderer);
	
	SDL_GetWindowSize(window, &width, &height);
	aspectRatio = (double)width / height;

	surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	posX = 0;
	posY = 0;
	scale = 1;
	iter  = 10;

	updated = false;
}

Mandelbrot::~Mandelbrot()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Mandelbrot::draw()
{
	if (!updated) {
		drawSurface();
		SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
		updated = true;
	}

	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Mandelbrot::drawSurface()
{
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			uint32_t& pixel = *((uint32_t*)surface->pixels + h * surface->w + w);

			// for test
			pixel = makeColor(h % 255, w % 255, h % 255);
		}
	}
}
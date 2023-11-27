#include "mandelbrot.h"
#include <complex>

using namespace std;

inline Uint32 makeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
{
	return (a << 24) + (r << 16) + (g << 8) + b;
}

template <class T>
inline Uint32 mandelbrot(complex<T> comp, Uint32 iteration)
{
	complex<T> z;
	for (int i = 0; i < iteration; ++i)
	{
		z = z * z + comp;
		if (norm(z) > 4.)
			return i;
	}
	return iteration;
}

Mandelbrot::Mandelbrot(SDL_Renderer *renderer)
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
	iteration = 32;

	updated = false;
}

Mandelbrot::~Mandelbrot()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Mandelbrot::draw()
{
	if (!updated)
	{
		drawSurface();
		SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
		updated = true;
	}

	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Mandelbrot::drawSurface()
{
	double minX = posX - 2. * scale * aspectRatio;
	double maxY = posY + 2. * scale;
	double dx = 4. * scale * aspectRatio / width;
	double dy = 4. * scale / height;

	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			Uint32 &pixel = *((Uint32 *)surface->pixels + h * surface->w + w);

			double cx = minX + dx * (w + 0.5f);
			double cy = maxY - dy * (h + 0.5f);

			auto iterated = mandelbrot<double>({cx, cy}, iteration);

			if (iterated == iteration)
				pixel = 0xffffffff;
			else
				pixel = 0xff000000;
		}
	}
}
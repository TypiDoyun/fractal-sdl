#include <SDL.h>

class Mandelbrot
{
public:
	using real_t = double;

	Mandelbrot(SDL_Renderer *renderer);
	~Mandelbrot();

	void draw();

private:
	void drawSurface();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Surface *surface;
	SDL_Texture *texture;

	int width;
	int height;
	double aspectRatio;

	double posX;
	double posY;
	double scale;
	Uint32 iteration;

	bool updated;
};
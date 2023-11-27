#include <iostream>
#include <memory>
#include "mandelbrot.h"
#include <SDL.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define FPS 60

using namespace std;

bool initialize();

int main(void) {

    bool isInitialized = initialize();
    bool isRunning = true;
    Uint32 startTime = 0;
    Uint32 frameTime = 0;

    if (!isInitialized) {
        cout << "initialize failed with error: " << SDL_GetError() << endl;
        return EXIT_FAILURE; 
    }

    SDL_Window* window = SDL_CreateWindow(
        "Learn SDL", // title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, // window width
        WINDOW_HEIGHT, // window height
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        cout << "SDL_CreateWindow failed with error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        cout << "SDL_CreateWindow failed with error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    auto mandelbrot = make_unique<Mandelbrot>(renderer);

    while (isRunning) {
        startTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) isRunning = false;
        }


        frameTime = SDL_GetTicks() - startTime;
        if (frameTime < (1000 / FPS)) {
            SDL_Delay((1000 / FPS) - frameTime);
        }

        mandelbrot->draw();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS; 
}

bool initialize() {
    return SDL_Init(SDL_INIT_EVERYTHING) <= 0;
}
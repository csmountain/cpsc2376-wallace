// Same code used as in Project 1 modified to use game.h and game.cpp, meaning little bugfixing was needed after plugging in the old values to the template.
// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#define SDL_MAIN_HANDLED
#include "game.h"
#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Game game;
    bool running = true;
    SDL_Event event;

    while (running)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int col = event.button.x / 100;
                if (game.status() == ONGOING && !game.isColumnFull(col))
                {
                    game.play(col);
                }
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        game.draw(renderer);

        if (game.status() != ONGOING)
        {
            // Display win/draw message
            // (You can add SDL2 text rendering here)
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

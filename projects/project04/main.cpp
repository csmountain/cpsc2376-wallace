// Same code used as in Project 1 modified to use game.h and game.cpp, meaning little bugfixing was needed after plugging in the old values to the template.
// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#define SDL_MAIN_HANDLED
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

// Helper function to render text
void renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, SDL_Color color, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main()
{
    // Initialize SDL and TTF
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
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

    // Specify the absolute or relative path to the font file
    const std::string fontPath = "C:/Windows/fonts/arial.ttf"; // Update this path to the actual location of your font file
    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Game game;
    bool running = true;
    SDL_Event event;

    enum Screen
    {
        INTRO,
        GAME,
        END
    };
    Screen currentScreen = INTRO;
    std::string endMessage;

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
                if (currentScreen == INTRO)
                {
                    currentScreen = GAME; // Start the game
                }
                else if (currentScreen == GAME)
                {
                    int col = event.button.x / 100;
                    if (game.status() == ONGOING && !game.isColumnFull(col))
                    {
                        game.play(col);
                    }
                }
                else if (currentScreen == END)
                {
                    // Check if "Play Again" button is clicked
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (mouseX >= 250 && mouseX <= 450 && mouseY >= 500 && mouseY <= 550)
                    {
                        game = Game(); // Reset the game
                        currentScreen = GAME;
                    }
                }
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        if (currentScreen == INTRO)
        {
            // Intro screen
            SDL_Color white = {255, 255, 255, 255};
            renderText(renderer, font, "Welcome to Connect Four!", white, 200, 100);
            renderText(renderer, font, "Rules:", white, 200, 150);
            renderText(renderer, font, "1. Players take turns dropping tokens.", white, 200, 200);
            renderText(renderer, font, "2. First to connect 4 tokens wins.", white, 200, 250);
            renderText(renderer, font, "3. If the grid is full, it's a draw.", white, 200, 300);
            renderText(renderer, font, "Click anywhere to start!", white, 200, 400);
        }
        else if (currentScreen == GAME)
        {
            // Game screen
            game.draw(renderer);

            if (game.status() != ONGOING)
            {
                if (game.status() == PLAYER_1_WINS)
                {
                    endMessage = "Player 1 Wins!";
                }
                else if (game.status() == PLAYER_2_WINS)
                {
                    endMessage = "Player 2 Wins!";
                }
                else
                {
                    endMessage = "It's a Draw!";
                }
                currentScreen = END;
            }
        }
        else if (currentScreen == END)
        {
            // End screen
            SDL_Color white = {255, 255, 255, 255};
            renderText(renderer, font, endMessage, white, 250, 200);
            renderText(renderer, font, "Click the button below to play again.", white, 150, 300);

            // Draw "Play Again" button
            SDL_Rect buttonRect = {250, 500, 200, 50};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue button
            SDL_RenderFillRect(renderer, &buttonRect);
            renderText(renderer, font, "Play Again", white, 290, 510);
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

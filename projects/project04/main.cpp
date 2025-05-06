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

// Function to render a semi-transparent preview token
void renderPreviewToken(SDL_Renderer *renderer, int mouseX, SDL_Color color)
{
    // Enable blending for transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Calculate the column based on mouseX
    const int cellSize = 100;    // Same as in the draw function
    const int holeRadius = 40;   // Same as in the draw function
    const int boardOffsetY = 50; // Vertical offset for the board
    int col = mouseX / cellSize;

    // Define the circle's center and radius
    int centerX = col * cellSize + cellSize / 2; // Center of the column
    int centerY = boardOffsetY + cellSize / 2;   // Center of the first row, including board offset
    int radius = holeRadius;                     // Match the token radius

    // Set the color with transparency
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 128); // 128 for 50% transparency

    // Draw the filled circle using a simple algorithm
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // Horizontal distance from center
            int dy = radius - h; // Vertical distance from center
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }

    // Reset the blend mode
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
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

    // Increase window height to include display area
    SDL_Window *window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 650, SDL_WINDOW_SHOWN);
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
                    // Check if "Exit" button is clicked
                    else if (mouseX >= 250 && mouseX <= 450 && mouseY >= 570 && mouseY <= 620)
                    {
                        running = false; // Exit the program
                    }
                }
            }
        }

        // Get the current mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

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
            // Draw the black section above the board
            SDL_Rect infoSection = {0, 0, 700, 50};         // Adjust width and height as needed
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
            SDL_RenderFillRect(renderer, &infoSection);

            // Display current player's turn
            SDL_Color textColor = {255, 255, 255, 255}; // White text
            std::string currentPlayerText = (game.getCurrentPlayer() == PLAYER_1)
                                                ? "Player 1's Turn (Red)"
                                                : "Player 2's Turn (Yellow)";
            renderText(renderer, font, currentPlayerText, textColor, 10, 10); // Position text inside the black section

            // Draw the game board (shifted down by 50 pixels)
            SDL_Rect boardOffset = {0, 50, 700, 600};
            SDL_RenderSetViewport(renderer, &boardOffset);
            game.draw(renderer);
            SDL_RenderSetViewport(renderer, nullptr); // Reset viewport

            // Render the semi-transparent preview token
            SDL_Color previewColor = (game.getCurrentPlayer() == PLAYER_1)
                                         ? SDL_Color{255, 0, 0, 128}    // Red for Player 1
                                         : SDL_Color{255, 255, 0, 128}; // Yellow for Player 2
            renderPreviewToken(renderer, mouseX, previewColor);

            // Check game status
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
            SDL_Rect playAgainButton = {250, 500, 200, 50};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue button
            SDL_RenderFillRect(renderer, &playAgainButton);
            renderText(renderer, font, "Play Again", white, 290, 510);

            // Draw "Exit" button
            SDL_Rect exitButton = {250, 570, 200, 50};        // Positioned below "Play Again"
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red button
            SDL_RenderFillRect(renderer, &exitButton);
            renderText(renderer, font, "Exit", white, 320, 580);
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

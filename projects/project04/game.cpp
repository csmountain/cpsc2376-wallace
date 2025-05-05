// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include "game.h"
#include <SDL2/SDL_ttf.h>

Game::Game() : board(ROWS, std::vector<Token>(COLS, EMPTY)), currentPlayer(PLAYER_1) {}

void Game::play(int col) {
    if (col < 0 || col >= COLS)
        return;

    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == EMPTY) {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
            return;
        }
    }
}

bool Game::checkWin(Token token) const {  
   // Horizontal check  
   for (int row = 0; row < ROWS; ++row) {  
       for (int col = 0; col <= COLS - 4; ++col) {  
           if (board[row][col] == token && board[row][col + 1] == token &&  
               board[row][col + 2] == token && board[row][col + 3] == token) {  
               return true;  
           }  
       }  
   }  

   // Vertical check  
   for (int col = 0; col < COLS; ++col) {  
       for (int row = 0; row <= ROWS - 4; ++row) {  
           if (board[row][col] == token && board[row + 1][col] == token &&  
               board[row + 2][col] == token && board[row + 3][col] == token) {  
               return true;  
           }  
       }  
   }  

   // Diagonal (top-left to bottom-right) check  
   for (int row = 0; row <= ROWS - 4; ++row) {  
       for (int col = 0; col <= COLS - 4; ++col) {  
           if (board[row][col] == token && board[row + 1][col + 1] == token &&  
               board[row + 2][col + 2] == token && board[row + 3][col + 3] == token) {  
               return true;  
           }  
       }  
   }  

   // Diagonal (bottom-left to top-right) check  
   for (int row = 3; row < ROWS; ++row) {  
       for (int col = 0; col <= COLS - 4; ++col) {  
           if (board[row][col] == token && board[row - 1][col + 1] == token &&  
               board[row - 2][col + 2] == token && board[row - 3][col + 3] == token) {  
               return true;  
           }  
       }  
   }  

   // If no win condition is met, return false  
   return false;  
}

bool Game::isColumnFull(int col) const {
    return board[0][col] != EMPTY;
}

Status Game::status() const {
    if (checkWin(PLAYER_1))
        return PLAYER_1_WINS;
    if (checkWin(PLAYER_2))
        return PLAYER_2_WINS;

    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == EMPTY)
                return ONGOING;
        }
    }

    return DRAW;
}

Token Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::draw(SDL_Renderer* renderer) const {
    // Colors
    SDL_Color gridColor = { 0, 68, 127, 255 }; // Blue
    SDL_Color player1Color = { 255, 0, 0, 255 }; // Red
    SDL_Color player2Color = { 255, 255, 0, 255 }; // Yellow
    SDL_Color backgroundColor = { 0, 0, 0, 255 }; // Black (for holes)
    SDL_Color textColor = { 255, 255, 255, 255 }; // White for text

    // Grid cell dimensions
    const int cellSize = 100;
    const int holeRadius = 40;
    const int holeOffset = (cellSize - 2 * holeRadius) / 2;

    // Draw grid with circular holes
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            // Draw grid cell
            SDL_Rect cell = { col * cellSize, row * cellSize, cellSize, cellSize };
            SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
            SDL_RenderFillRect(renderer, &cell);

            // Draw circular hole
            int centerX = col * cellSize + cellSize / 2;
            int centerY = row * cellSize + cellSize / 2;
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
            for (int w = 0; w < holeRadius * 2; ++w) {
                for (int h = 0; h < holeRadius * 2; ++h) {
                    int dx = holeRadius - w; // Horizontal distance from center
                    int dy = holeRadius - h; // Vertical distance from center
                    if ((dx * dx + dy * dy) <= (holeRadius * holeRadius)) {
                        SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                    }
                }
            }

            // Draw tokens if present
            if (board[row][col] != EMPTY) {
                SDL_Color tokenColor = (board[row][col] == PLAYER_1) ? player1Color : player2Color;
                SDL_SetRenderDrawColor(renderer, tokenColor.r, tokenColor.g, tokenColor.b, tokenColor.a);
                for (int w = 0; w < holeRadius * 2; ++w) {
                    for (int h = 0; h < holeRadius * 2; ++h) {
                        int dx = holeRadius - w;
                        int dy = holeRadius - h;
                        if ((dx * dx + dy * dy) <= (holeRadius * holeRadius)) {
                            SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                        }
                    }
                }
            }
        }
    }

    // Display current player's turn
    const char* currentPlayerText = (currentPlayer == PLAYER_1) ? "Player 1 (Red)" : "Player 2 (Yellow)";
    SDL_Color currentPlayerColor = (currentPlayer == PLAYER_1) ? player1Color : player2Color;

    // Assuming you have an SDL_ttf font loaded as `font`
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24); // Adjust path and size as needed
    if (font) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, currentPlayerText, textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                SDL_Rect textRect = { 10, ROWS * cellSize + 10, textSurface->w, textSurface->h }; // Position below the board
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
            }
            SDL_FreeSurface(textSurface);
        }
        TTF_CloseFont(font);
    }
}


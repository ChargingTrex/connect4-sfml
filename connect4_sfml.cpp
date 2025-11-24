#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "animation.h"
#include "popup.h"

// --- Game Constants ---
constexpr int ROWS = 6;
constexpr int COLS = 7;
constexpr float CELL_SIZE = 100.0f; // Size of each cell in pixels
constexpr float PIECE_RADIUS = 40.0f; // Radius of the game pieces
constexpr int WINDOW_WIDTH = static_cast<int>(COLS * CELL_SIZE);
constexpr int WINDOW_HEIGHT = static_cast<int>(ROWS * CELL_SIZE + 50.0f); // Extra height for status bar

// --- Game State Variables ---
// Board: 0=Empty, 1=Red, 2=Yellow
std::vector<std::vector<int>> board(ROWS, std::vector<int>(COLS, 0));
int currentPlayer = 1; // 1 for Red, 2 for Yellow
bool gameOver = false;
std::string statusText = "Player 1 (Red)'s Turn";

// --- Function Declarations ---
bool checkWin(int lastRow, int lastCol);
int dropPiece(int col, int player);
void resetGame();
void drawBoard(sf::RenderWindow& window);
void drawStatus(sf::RenderWindow& window, const sf::Font& font);

/**
 * @brief Resets the game board and state variables for a new game.
 */
void resetGame() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            board[r][c] = 0;
        }
    }
    currentPlayer = 1;
    gameOver = false;
    statusText = "Player 1 (Red)'s Turn";
    resetAnimation();
    resetPopup();
}

/**
 * @brief Checks all directions (horizontal, vertical, diagonals) for 4 in a row.
 * @param lastRow The row of the last piece placed.
 * @param lastCol The column of the last piece placed.
 * @return true if the last move resulted in a win, false otherwise.
 */
bool checkWin(int lastRow, int lastCol) {
    if (lastRow == -1) return false;

    int player = board[lastRow][lastCol];

    // Helper lambda to count consecutive pieces in a direction
    auto countDir = [&](int dr, int dc) {
        int count = 0;
        // Check both directions from the center piece
        for (int i = -3; i <= 3; ++i) {
            int r = lastRow + i * dr;
            int c = lastCol + i * dc;

            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                if (board[r][c] == player) {
                    count++;
                    if (count >= 4) return true;
                } else {
                    count = 0;
                }
            }
        }
        return false;
    };

    // 1. Check Horizontal (dr=0, dc=1)
    if (countDir(0, 1)) return true;
    
    // 2. Check Vertical (dr=1, dc=0) 
    if (countDir(1, 0)) return true;

    // 3. Check Diagonal (top-left to bottom-right) (dr=1, dc=1)
    if (countDir(1, 1)) return true;

    // 4. Check Diagonal (top-right to bottom-left) (dr=1, dc=-1)
    if (countDir(1, -1)) return true;

    return false;
}

/**
 * @brief Finds the lowest available row in a column and places the piece.
 */
int dropPiece(int col, int player) {
    if (col < 0 || col >= COLS) return -1;

    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == 0) {
            board[r][col] = player;
            return r; // Return the row where the piece landed
        }
    }
    return -1; // Column is full
}

/**
 * @brief Checks for a draw condition (board is full).
 */
bool checkDraw() {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Draws the 6x7 Connect Four board, including the grid and the pieces.
 */
void drawBoard(sf::RenderWindow& window) {
    // 1. Draw the Blue Board Background
    sf::RectangleShape boardBg(sf::Vector2f(WINDOW_WIDTH, ROWS * CELL_SIZE));
    boardBg.setFillColor(sf::Color(0, 0, 150)); // Dark Blue
    // SFML 3.x Fix: use sf::Vector2f
    boardBg.setPosition(sf::Vector2f(0.0f, 0.0f)); 
    window.draw(boardBg);

    // 2. Draw the Pieces and Empty Slots
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            float centerX = c * CELL_SIZE + CELL_SIZE / 2.0f;
            float centerY = r * CELL_SIZE + CELL_SIZE / 2.0f;

            sf::CircleShape piece(PIECE_RADIUS);
            // SFML 3.x Fix: use sf::Vector2f
            piece.setOrigin(sf::Vector2f(PIECE_RADIUS, PIECE_RADIUS)); 
            // SFML 3.x Fix: use sf::Vector2f
            piece.setPosition(sf::Vector2f(centerX, centerY)); 
            
            if (board[r][c] == 1) {
                piece.setFillColor(sf::Color::Red);
            } else if (board[r][c] == 2) {
                piece.setFillColor(sf::Color::Yellow);
            } else {
                piece.setFillColor(sf::Color(20, 20, 20)); 
                piece.setOutlineThickness(2);
                piece.setOutlineColor(sf::Color(0, 0, 100)); 
            }

            window.draw(piece);
        }
    }
}

/**
 * @brief Draws the game status text at the bottom of the window.
 */
void drawStatus(sf::RenderWindow& window, const sf::Font& font) {
    // SFML 3.x Fix: Text constructor now requires font as first parameter
    sf::Text status(font, statusText);
    status.setCharacterSize(24);
    status.setFillColor(sf::Color::White);
    
    // Center the text horizontally in the status bar area
    sf::FloatRect textRect = status.getLocalBounds();
    // SFML 3.x Fix: Accessing FloatRect members using new position and size members
    status.setOrigin(sf::Vector2f(
        textRect.position.x + textRect.size.x / 2.0f, 
        textRect.position.y + textRect.size.y / 2.0f
    ));
    // SFML 3.x Fix: use sf::Vector2f
    status.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, ROWS * CELL_SIZE + 25.0f)); 

    window.draw(status);

    if (gameOver) {
        // Draw a "New Game" button prompt if the game is over
        // SFML 3.x Fix: Text constructor now requires font as first parameter
        sf::Text restartPrompt(font, "Press R to Restart");
        restartPrompt.setCharacterSize(18);
        restartPrompt.setFillColor(sf::Color::Green);
        // SFML 3.x Fix: use sf::Vector2f
        restartPrompt.setPosition(sf::Vector2f(WINDOW_WIDTH - 200.0f, ROWS * CELL_SIZE + 10.0f));
        window.draw(restartPrompt);
    }
}

/**
 * @brief Main function where the SFML game loop resides.
 */
int main() {
    // SFML 3.x Fix: VideoMode constructor now takes sf::Vector2u for size
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Connect Four (C++/SFML)", sf::Style::Close);
    window.setFramerateLimit(60);

    // Load a font for displaying status text
    sf::Font font;
    // SFML 3.x Fix: Renamed from loadFromFile to openFromFile
    // Using macOS system font (Helvetica)
    if (!font.openFromFile("/System/Library/Fonts/Helvetica.ttc")) {
        std::cerr << "--- FONT ERROR ---" << std::endl;
        std::cerr << "Failed to load font. Trying alternative..." << std::endl;
        // Fallback to another common macOS font
        if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
            std::cerr << "Failed to load any font. Text will not display." << std::endl;
        }
    }

    // Main game loop
    sf::Clock clock; // For tracking deltaTime
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Time since last frame
        
        // SFML 3.x Event handling loop: pollEvent now returns an optional event object
        // NOTE: std::optional is required, which is why we need the C++17 flag.
        for (std::optional<sf::Event> eventOpt = window.pollEvent(); eventOpt.has_value(); eventOpt = window.pollEvent()) {
            const auto& event = eventOpt.value(); // Access the event structure

            if (event.is<sf::Event::Closed>()) {
                window.close();
            }

            // Handle mouse clicks for placing pieces (only if not animating)
            if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    if (!gameOver && !isAnimationActive()) {
                        // Calculate which column was clicked using the mouse position
                        int clickedCol = static_cast<int>(mouseEvent->position.x / CELL_SIZE);

                        // Find the target row for animation
                        int targetRow = -1;
                        for (int r = ROWS - 1; r >= 0; --r) {
                            if (board[r][clickedCol] == 0) {
                                targetRow = r;
                                break;
                            }
                        }
                        
                        if (targetRow != -1) {
                            // Start the fall animation
                            initAnimation(clickedCol, targetRow, currentPlayer);
                        } else {
                            std::cout << "Column " << clickedCol + 1 << " is full!" << std::endl;
                        }
                    }
                }
            }
            
            // Handle keyboard input for restarting the game
            if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::R) {
                    resetGame();
                }
            }
        }
        
        // Update animation if active
        if (isAnimationActive()) {
            updateAnimation(deltaTime);
            
            // Check if animation just finished
            if (!isAnimationActive()) {
                // Animation complete - place the piece on board
                int col = g_animation.column;
                int row = g_animation.targetRow;
                int player = g_animation.player;
                
                board[row][col] = player;
                
                // Check win condition
                if (checkWin(row, col)) {
                    gameOver = true;
                    statusText = (player == 1 ? "Player 1 (Red) WINS!" : "Player 2 (Yellow) WINS!");
                    initPopup(player, false);
                } else if (checkDraw()) {
                    gameOver = true;
                    statusText = "Game Over - It's a DRAW!";
                    initPopup(0, true);
                } else {
                    // Switch player and update status
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    statusText = (currentPlayer == 1 ? "Player 1 (Red)'s Turn" : "Player 2 (Yellow)'s Turn");
                }
            }
        }
        
        // Update popup fade-in animation
        updatePopup(deltaTime);

        // --- Drawing ---
        window.clear(sf::Color(50, 50, 50));

        drawBoard(window);
        drawStatus(window, font);
        
        // Draw falling piece on top of board
        drawFallingPiece(window);
        
        // Draw winner popup if game is over
        if (gameOver) {
            drawWinnerPopup(window, font);
        }

        window.display();
    }

    return 0;
}
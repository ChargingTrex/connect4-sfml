#include "animation.h"
#include <cmath>

// Define the global animation state
AnimationState g_animation = {false, 0, 0, 0, 0.0f, 0.0f};

/**
 * @brief Initialize and start a fall animation for a piece
 * @param col Column where piece is dropping
 * @param targetRow Final row position for the piece
 * @param player Player number (1=Red, 2=Yellow)
 */
void initAnimation(int col, int targetRow, int player) {
    g_animation.isActive = true;
    g_animation.column = col;
    g_animation.targetRow = targetRow;
    g_animation.player = player;
    g_animation.currentY = 0.0f; // Start at top of board
    g_animation.velocity = 0.0f;  // Start with zero velocity
}

/**
 * @brief Update animation state based on elapsed time
 * @param deltaTime Time elapsed since last frame (in seconds)
 */
void updateAnimation(float deltaTime) {
    if (!g_animation.isActive) return;

    // Calculate target Y position
    float targetY = g_animation.targetRow * CELL_SIZE_ANIM + CELL_SIZE_ANIM / 2.0f;
    
    // Apply gravity to velocity
    g_animation.velocity += GRAVITY * deltaTime;
    
    // Update position
    g_animation.currentY += g_animation.velocity * deltaTime;
    
    // Check if we've reached or passed the target
    if (g_animation.currentY >= targetY) {
        g_animation.currentY = targetY;
        g_animation.isActive = false; // Animation complete
    }
}

/**
 * @brief Draw the falling piece at its current animated position
 * @param window SFML render window to draw on
 */
void drawFallingPiece(sf::RenderWindow& window) {
    if (!g_animation.isActive) return;

    float centerX = g_animation.column * CELL_SIZE_ANIM + CELL_SIZE_ANIM / 2.0f;
    
    sf::CircleShape piece(PIECE_RADIUS_ANIM);
    piece.setOrigin(sf::Vector2f(PIECE_RADIUS_ANIM, PIECE_RADIUS_ANIM));
    piece.setPosition(sf::Vector2f(centerX, g_animation.currentY));
    
    // Set color based on player
    if (g_animation.player == 1) {
        piece.setFillColor(sf::Color::Red);
    } else {
        piece.setFillColor(sf::Color::Yellow);
    }
    
    window.draw(piece);
}

/**
 * @brief Check if animation is currently active
 * @return true if animation is running, false otherwise
 */
bool isAnimationActive() {
    return g_animation.isActive;
}

/**
 * @brief Reset animation state to inactive
 */
void resetAnimation() {
    g_animation.isActive = false;
    g_animation.column = 0;
    g_animation.targetRow = 0;
    g_animation.player = 0;
    g_animation.currentY = 0.0f;
    g_animation.velocity = 0.0f;
}

/**
 * @brief Get the target row for the current animation
 * @return Target row index, or -1 if no animation active
 */
int getAnimationTargetRow() {
    if (g_animation.isActive) {
        return g_animation.targetRow;
    }
    return -1;
}

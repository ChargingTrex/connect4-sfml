#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

// Animation constants
constexpr float GRAVITY = 1600.0f;       // Pixels per second squared (doubled for faster animation)
constexpr float CELL_SIZE_ANIM = 100.0f; // Match main game cell size
constexpr float PIECE_RADIUS_ANIM = 40.0f;

// Animation state structure
struct AnimationState {
    bool isActive;
    int column;
    int targetRow;
    int player;          // 1 for Red, 2 for Yellow
    float currentY;      // Current Y position
    float velocity;      // Current velocity (pixels/second)
};

// Global animation state
extern AnimationState g_animation;

// Animation functions
void initAnimation(int col, int targetRow, int player);
void updateAnimation(float deltaTime);
void drawFallingPiece(sf::RenderWindow& window);
bool isAnimationActive();
void resetAnimation();
int getAnimationTargetRow();

#endif // ANIMATION_H

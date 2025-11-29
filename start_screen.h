#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <SFML/Graphics.hpp>

/**
 * @brief Draw the start screen with title and menu buttons
 * @param window SFML render window to draw on
 * @param startTexture Texture containing the start screen sprite
 */
void drawStartScreen(sf::RenderWindow& window, const sf::Texture* startTexture);

/**
 * @brief Check if a mouse click is on the START button
 * @param x Mouse X position
 * @param y Mouse Y position
 * @return true if click is on start button, false otherwise
 */
bool isClickOnStartButton(float x, float y);

/**
 * @brief Check if a mouse click is on the EXIT button
 * @param x Mouse X position
 * @param y Mouse Y position
 * @return true if click is on exit button, false otherwise
 */
bool isClickOnExitButton(float x, float y);

#endif // START_SCREEN_H

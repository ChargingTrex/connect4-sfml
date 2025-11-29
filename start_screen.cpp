#include "start_screen.h"

// Constants for window size (matching main game)
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 650;

// Sprite regions from start_screen.png
// Based on the sprite sheet layout, approximate coordinates:
const sf::IntRect TITLE_RECT(sf::Vector2i(220, 15), sf::Vector2i(580, 110));      // "CONNECT 4" title
const sf::IntRect START_BTN_RECT(sf::Vector2i(300, 320), sf::Vector2i(420, 90));  // "START GAME" button
const sf::IntRect EXIT_BTN_RECT(sf::Vector2i(420, 415), sf::Vector2i(180, 70));   // "EXIT" button

// Button screen positions (where they'll be drawn)
constexpr float TITLE_Y = 150.0f;
constexpr float START_BUTTON_Y = 350.0f;
constexpr float EXIT_BUTTON_Y = 470.0f;

// Store button bounds for click detection
static sf::FloatRect g_startButtonBounds;
static sf::FloatRect g_exitButtonBounds;

/**
 * @brief Draw the start screen with title and menu buttons as separate sprites
 */
void drawStartScreen(sf::RenderWindow& window, const sf::Texture* startTexture) {
    // Draw checkered background pattern
    constexpr int CHECKER_SIZE = 20; // Size of each checker square
    const sf::Color GRAY1(100, 100, 100);      // Light gray
    const sf::Color GRAY2(70, 70, 70);         // Dark gray
    
    for (int y = 0; y < WINDOW_HEIGHT; y += CHECKER_SIZE) {
        for (int x = 0; x < WINDOW_WIDTH; x += CHECKER_SIZE) {
            sf::RectangleShape checker(sf::Vector2f(CHECKER_SIZE, CHECKER_SIZE));
            checker.setPosition(sf::Vector2f(x, y));
            
            // Alternate colors in checkerboard pattern
            if ((x / CHECKER_SIZE + y / CHECKER_SIZE) % 2 == 0) {
                checker.setFillColor(GRAY1);
            } else {
                checker.setFillColor(GRAY2);
            }
            
            window.draw(checker);
        }
    }
    
    if (!startTexture) {
        // Fallback if texture not loaded - just show checkered background
        return;
    }
    
    // --- Draw Title Sprite ---
    sf::Sprite titleSprite(*startTexture);
    titleSprite.setTextureRect(TITLE_RECT);
    
    float titleScale = 0.8f;
    titleSprite.setScale(sf::Vector2f(titleScale, titleScale));
    
    sf::FloatRect titleBounds = titleSprite.getLocalBounds();
    titleSprite.setOrigin(sf::Vector2f(
        titleBounds.position.x + titleBounds.size.x / 2.0f,
        titleBounds.position.y + titleBounds.size.y / 2.0f
    ));
    titleSprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, TITLE_Y));
    
    window.draw(titleSprite);
    
    // --- Draw Start Button Sprite ---
    sf::Sprite startBtnSprite(*startTexture);
    startBtnSprite.setTextureRect(START_BTN_RECT);
    
    float startScale = 0.75f;
    startBtnSprite.setScale(sf::Vector2f(startScale, startScale));
    
    sf::FloatRect startBounds = startBtnSprite.getLocalBounds();
    startBtnSprite.setOrigin(sf::Vector2f(
        startBounds.position.x + startBounds.size.x / 2.0f,
        startBounds.position.y + startBounds.size.y / 2.0f
    ));
    startBtnSprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, START_BUTTON_Y));
    
    // Store bounds for click detection
    g_startButtonBounds = startBtnSprite.getGlobalBounds();
    
    window.draw(startBtnSprite);
    
    // --- Draw Exit Button Sprite ---
    sf::Sprite exitBtnSprite(*startTexture);
    exitBtnSprite.setTextureRect(EXIT_BTN_RECT);
    
    float exitScale = 0.6f;
    exitBtnSprite.setScale(sf::Vector2f(exitScale, exitScale));
    
    sf::FloatRect exitBounds = exitBtnSprite.getLocalBounds();
    exitBtnSprite.setOrigin(sf::Vector2f(
        exitBounds.position.x + exitBounds.size.x / 2.0f,
        exitBounds.position.y + exitBounds.size.y / 2.0f
    ));
    exitBtnSprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, EXIT_BUTTON_Y));
    
    // Store bounds for click detection
    g_exitButtonBounds = exitBtnSprite.getGlobalBounds();
    
    window.draw(exitBtnSprite);
}

/**
 * @brief Check if a mouse click is on the START button
 */
bool isClickOnStartButton(float x, float y) {
    return (x >= g_startButtonBounds.position.x && 
            x <= g_startButtonBounds.position.x + g_startButtonBounds.size.x &&
            y >= g_startButtonBounds.position.y && 
            y <= g_startButtonBounds.position.y + g_startButtonBounds.size.y);
}

/**
 * @brief Check if a mouse click is on the EXIT button
 */
bool isClickOnExitButton(float x, float y) {
    return (x >= g_exitButtonBounds.position.x && 
            x <= g_exitButtonBounds.position.x + g_exitButtonBounds.size.x &&
            y >= g_exitButtonBounds.position.y && 
            y <= g_exitButtonBounds.position.y + g_exitButtonBounds.size.y);
}

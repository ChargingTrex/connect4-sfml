#include "popup.h"
#include <algorithm>
#include <cmath>

// Define the global popup state
PopupState g_popup = {false, 0, 0.0f, ""};

// Constants for popup appearance
constexpr float FADE_SPEED = 600.0f;    // Alpha units per second
constexpr float POPUP_WIDTH = 500.0f;
constexpr float POPUP_HEIGHT = 250.0f;
constexpr int WINDOW_WIDTH_POPUP = 700;  // Match main game window
constexpr int WINDOW_HEIGHT_POPUP = 650;

/**
 * @brief Initialize and display winner popup
 * @param winningPlayer Player who won (1=Red, 2=Yellow)
 * @param isDraw True if game is a draw
 */
void initPopup(int winningPlayer, bool isDraw) {
    g_popup.isActive = true;
    g_popup.winningPlayer = winningPlayer;
    g_popup.alpha = 0.0f; // Start transparent, will fade in
    
    if (isDraw) {
        g_popup.message = "It's a DRAW!";
    } else if (winningPlayer == 1) {
        g_popup.message = "Player 1 (Red) WINS!";
    } else {
        g_popup.message = "Player 2 (Yellow) WINS!";
    }
}

/**
 * @brief Update popup fade-in animation
 * @param deltaTime Time elapsed since last frame (in seconds)
 */
void updatePopup(float deltaTime) {
    if (!g_popup.isActive) return;
    
    // Fade in the popup
    if (g_popup.alpha < 255.0f) {
        g_popup.alpha += FADE_SPEED * deltaTime;
        g_popup.alpha = std::min(g_popup.alpha, 255.0f);
    }
}

/**
 * @brief Draw the arcade-style winner popup overlay
 * @param window SFML render window to draw on
 * @param font Font to use for text rendering
 */
void drawWinnerPopup(sf::RenderWindow& window, const sf::Font& font) {
    if (!g_popup.isActive) return;
    
    std::uint8_t alpha = static_cast<std::uint8_t>(g_popup.alpha);
    
    // 1. Draw semi-transparent dark overlay over entire window (darker for drama)
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH_POPUP, WINDOW_HEIGHT_POPUP));
    overlay.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha * 0.85f)));
    window.draw(overlay);
    
    // 2. Draw larger popup box in center
    float popupX = (WINDOW_WIDTH_POPUP - POPUP_WIDTH) / 2.0f;
    float popupY = (WINDOW_HEIGHT_POPUP - POPUP_HEIGHT) / 2.0f - 20.0f;
    
    // Arcade-style background with double border
    sf::RectangleShape popupBg(sf::Vector2f(POPUP_WIDTH, POPUP_HEIGHT));
    popupBg.setPosition(sf::Vector2f(popupX, popupY));
    popupBg.setFillColor(sf::Color(20, 20, 40, alpha)); // Dark blue-black
    
    // Outer neon glow border
    popupBg.setOutlineThickness(8.0f);
    if (g_popup.winningPlayer == 1) {
        popupBg.setOutlineColor(sf::Color(255, 0, 100, alpha)); // Hot pink/red
    } else if (g_popup.winningPlayer == 2) {
        popupBg.setOutlineColor(sf::Color(255, 220, 0, alpha)); // Bright yellow
    } else {
        popupBg.setOutlineColor(sf::Color(100, 200, 255, alpha)); // Cyan for draw
    }
    window.draw(popupBg);
    
    // Inner bright border for layered effect
    sf::RectangleShape innerBorder(sf::Vector2f(POPUP_WIDTH - 20, POPUP_HEIGHT - 20));
    innerBorder.setPosition(sf::Vector2f(popupX + 10, popupY + 10));
    innerBorder.setFillColor(sf::Color::Transparent);
    innerBorder.setOutlineThickness(3.0f);
    innerBorder.setOutlineColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(alpha * 0.6f)));
    window.draw(innerBorder);
    
    // 3. Draw "GAME OVER" text with shadow effect
    sf::Text gameOverText(font, "GAME OVER");
    gameOverText.setCharacterSize(56);
    gameOverText.setFillColor(sf::Color(255, 255, 255, alpha));
    gameOverText.setStyle(sf::Text::Bold);
    
    // Shadow layer for depth
    sf::Text gameOverShadow(font, "GAME OVER");
    gameOverShadow.setCharacterSize(56);
    gameOverShadow.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha * 0.7f)));
    gameOverShadow.setStyle(sf::Text::Bold);
    
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(sf::Vector2f(
        gameOverBounds.position.x + gameOverBounds.size.x / 2.0f,
        gameOverBounds.position.y + gameOverBounds.size.y / 2.0f
    ));
    gameOverShadow.setOrigin(gameOverText.getOrigin());
    
    float gameOverY = popupY + 70.0f;
    gameOverText.setPosition(sf::Vector2f(popupX + POPUP_WIDTH / 2.0f, gameOverY));
    gameOverShadow.setPosition(sf::Vector2f(popupX + POPUP_WIDTH / 2.0f + 4.0f, gameOverY + 4.0f));
    
    // Draw shadow first, then text
    window.draw(gameOverShadow);
    
    // Add neon outline to GAME OVER text
    gameOverText.setOutlineThickness(2.0f);
    if (g_popup.winningPlayer == 1) {
        gameOverText.setOutlineColor(sf::Color(255, 0, 100, alpha));
    } else if (g_popup.winningPlayer == 2) {
        gameOverText.setOutlineColor(sf::Color(255, 220, 0, alpha));
    } else {
        gameOverText.setOutlineColor(sf::Color(100, 200, 255, alpha));
    }
    window.draw(gameOverText);
    
    // 4. Draw decorative line separator
    sf::RectangleShape separator(sf::Vector2f(POPUP_WIDTH - 100, 4.0f));
    separator.setPosition(sf::Vector2f(popupX + 50, popupY + 130.0f));
    if (g_popup.winningPlayer == 1) {
        separator.setFillColor(sf::Color(255, 0, 100, alpha));
    } else if (g_popup.winningPlayer == 2) {
        separator.setFillColor(sf::Color(255, 220, 0, alpha));
    } else {
        separator.setFillColor(sf::Color(100, 200, 255, alpha));
    }
    window.draw(separator);
    
    // 5. Draw winner announcement with neon effect
    sf::Text winnerText(font, g_popup.message);
    winnerText.setCharacterSize(40);
    winnerText.setStyle(sf::Text::Bold);
    
    // Shadow for winner text
    sf::Text winnerShadow(font, g_popup.message);
    winnerShadow.setCharacterSize(40);
    winnerShadow.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha * 0.7f)));
    winnerShadow.setStyle(sf::Text::Bold);
    
    // Set winner text color based on player
    if (g_popup.winningPlayer == 1) {
        winnerText.setFillColor(sf::Color(255, 100, 100, alpha)); // Light red
        winnerText.setOutlineColor(sf::Color(255, 0, 0, alpha));
    } else if (g_popup.winningPlayer == 2) {
        winnerText.setFillColor(sf::Color(255, 255, 100, alpha)); // Light yellow
        winnerText.setOutlineColor(sf::Color(255, 200, 0, alpha));
    } else {
        winnerText.setFillColor(sf::Color(150, 220, 255, alpha)); // Light cyan
        winnerText.setOutlineColor(sf::Color(100, 200, 255, alpha));
    }
    winnerText.setOutlineThickness(2.0f);
    
    sf::FloatRect winnerBounds = winnerText.getLocalBounds();
    winnerText.setOrigin(sf::Vector2f(
        winnerBounds.position.x + winnerBounds.size.x / 2.0f,
        winnerBounds.position.y + winnerBounds.size.y / 2.0f
    ));
    winnerShadow.setOrigin(winnerText.getOrigin());
    
    float winnerY = popupY + POPUP_HEIGHT / 2.0f + 20.0f;
    winnerText.setPosition(sf::Vector2f(popupX + POPUP_WIDTH / 2.0f, winnerY));
    winnerShadow.setPosition(sf::Vector2f(popupX + POPUP_WIDTH / 2.0f + 3.0f, winnerY + 3.0f));
    
    window.draw(winnerShadow);
    window.draw(winnerText);
    
    // 6. Draw restart instruction with pulsing effect
    float pulseAlpha = alpha * (0.7f + 0.3f * std::sin(g_popup.alpha / 40.0f));
    sf::Text restartText(font, ">> PRESS R TO RESTART <<");
    restartText.setCharacterSize(22);
    restartText.setFillColor(sf::Color(0, 255, 150, static_cast<std::uint8_t>(pulseAlpha)));
    restartText.setStyle(sf::Text::Bold);
    restartText.setOutlineThickness(1.5f);
    restartText.setOutlineColor(sf::Color(0, 200, 100, static_cast<std::uint8_t>(pulseAlpha)));
    
    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setOrigin(sf::Vector2f(
        restartBounds.position.x + restartBounds.size.x / 2.0f,
        restartBounds.position.y + restartBounds.size.y / 2.0f
    ));
    restartText.setPosition(sf::Vector2f(
        popupX + POPUP_WIDTH / 2.0f,
        popupY + POPUP_HEIGHT - 50.0f
    ));
    window.draw(restartText);
}

/**
 * @brief Reset popup state to inactive
 */
void resetPopup() {
    g_popup.isActive = false;
    g_popup.winningPlayer = 0;
    g_popup.alpha = 0.0f;
    g_popup.message = "";
}

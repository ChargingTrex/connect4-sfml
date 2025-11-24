#ifndef POPUP_H
#define POPUP_H

#include <SFML/Graphics.hpp>
#include <string>

// Popup state structure
struct PopupState {
    bool isActive;
    int winningPlayer;    // 1 for Red, 2 for Yellow, 0 for draw
    float alpha;          // Current opacity (0-255)
    std::string message;
};

// Global popup state
extern PopupState g_popup;

// Popup functions
void initPopup(int winningPlayer, bool isDraw = false);
void updatePopup(float deltaTime);
void drawWinnerPopup(sf::RenderWindow& window, const sf::Font& font);
void resetPopup();

#endif // POPUP_H

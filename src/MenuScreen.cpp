#include "../include/MenuScreen.h"

MenuScreen::MenuScreen() : defaultColor(sf::Color::White), hoverColor(sf::Color::Green) {
    // Load background texture
    if (!backgroundTexture.loadFromFile("assets/images/menu.jpg")) {
        throw std::runtime_error("Failed to load background image");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Load font
    if (!font.loadFromFile("assets/fonts/font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Initialize title
    initializeText(title, "ICE Smash", 640, 100);

    // Initialize buttons
    initializeText(playButton, "Play", 640, 300);
    initializeText(highScoresButton, "High Scores", 640, 400);
    initializeText(exitButton, "Exit", 640, 500);
}

void MenuScreen::initializeText(sf::Text &text, const std::string &str, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(50);
    text.setFillColor(defaultColor);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x, y);
}

void MenuScreen::update(sf::RenderWindow &window) {
    // No need for continuous updates for static menu
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Change button color on hover
    if (playButton.getGlobalBounds().contains(mousePosF)) {
        playButton.setFillColor(hoverColor);
    } else {
        playButton.setFillColor(defaultColor);
    }

    if (highScoresButton.getGlobalBounds().contains(mousePosF)) {
        highScoresButton.setFillColor(hoverColor);
    } else {
        highScoresButton.setFillColor(defaultColor);
    }

    if (exitButton.getGlobalBounds().contains(mousePosF)) {
        exitButton.setFillColor(hoverColor);
    } else {
        exitButton.setFillColor(defaultColor);
    }
}

void MenuScreen::render(sf::RenderTarget& target) const {
    target.draw(backgroundSprite);
    target.draw(title);
    target.draw(playButton);
    target.draw(highScoresButton);
    target.draw(exitButton);
}

// Check if the mouse is over the buttons
bool MenuScreen::isPlayButtonClicked(sf::Vector2i mousePos) const {
    return playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

// Check if the mouse is over the buttons
bool MenuScreen::isHighScoresButtonClicked(sf::Vector2i mousePos) const {
    return highScoresButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

// Check if the mouse is over the buttons
bool MenuScreen::isExitButtonClicked(sf::Vector2i mousePos) const {
    return exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

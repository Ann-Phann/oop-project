#include "../include/GameWinScreen.h"

GameWinScreen::GameWinScreen() {
    // Load font
    if (!font.loadFromFile("assets/fonts/scoreFont.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Set up "You Win" text
    winText.setFont(font);
    winText.setString("Congratulations! You Win!");
    winText.setCharacterSize(70);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(640.f - winText.getGlobalBounds().width / 2, 200.f);

    // Set up total points text
    totalPointsText.setFont(font);
    totalPointsText.setCharacterSize(50);
    totalPointsText.setFillColor(sf::Color::White);
    totalPointsText.setPosition(640.f - totalPointsText.getGlobalBounds().width / 2, 300.f);

    // Set up Back to Menu button
    backToMenuButton.setSize(sf::Vector2f(200.f, 50.f));
    backToMenuButton.setFillColor(sf::Color::Blue);
    backToMenuButton.setPosition(540.f, 450.f);

    backToMenuButtonText.setFont(font);
    backToMenuButtonText.setString("Back to Menu");
    backToMenuButtonText.setCharacterSize(25);
    backToMenuButtonText.setFillColor(sf::Color::White);
    backToMenuButtonText.setPosition(
        backToMenuButton.getPosition().x + backToMenuButton.getSize().x / 2 - backToMenuButtonText.getGlobalBounds().width / 2,
        backToMenuButton.getPosition().y + backToMenuButton.getSize().y / 2 - backToMenuButtonText.getGlobalBounds().height / 2
    );

    // Set up Exit button
    exitButton.setSize(sf::Vector2f(200.f, 50.f));
    exitButton.setFillColor(sf::Color::Blue);
    exitButton.setPosition(540.f, 550.f);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(25);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(
        exitButton.getPosition().x + exitButton.getSize().x / 2 - exitButtonText.getGlobalBounds().width / 2,
        exitButton.getPosition().y + exitButton.getSize().y / 2 - exitButtonText.getGlobalBounds().height / 2
    );

    // Load background
    if (!backgroundTexture.loadFromFile("assets/images/win.jpg")) {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void GameWinScreen::update(sf::RenderWindow& window) {
    // Handle events for buttons if needed
}

void GameWinScreen::render(sf::RenderWindow& window) const {
    window.draw(backgroundSprite);
    window.draw(winText);
    window.draw(totalPointsText);
    window.draw(backToMenuButton);
    window.draw(backToMenuButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

bool GameWinScreen::isBackToMenuButtonClicked(const sf::Vector2i& mousePos) const {
    return backToMenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool GameWinScreen::isExitButtonClicked(const sf::Vector2i& mousePos) const {
    return exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void GameWinScreen::setTotalPoints(int points) {
    totalPointsText.setString("Total Points: " + std::to_string(points));
    totalPointsText.setPosition(640.f - totalPointsText.getGlobalBounds().width / 2, 300.f);
}

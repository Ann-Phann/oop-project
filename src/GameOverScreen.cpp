#include "../include/GameOverScreen.h"

GameOverScreen::GameOverScreen() {
    // Load font
    if (!font.loadFromFile("assets/fonts/scoreFont.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Set up "Game Over" text
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(640.f - gameOverText.getGlobalBounds().width / 2, 300.f);

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
}

void GameOverScreen::update(sf::RenderWindow& window) {
    // Handle events for buttons if needed
}

void GameOverScreen::render(sf::RenderWindow& window) const {
    window.draw(gameOverText);
    window.draw(backToMenuButton);
    window.draw(backToMenuButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

bool GameOverScreen::isBackToMenuButtonClicked(const sf::Vector2i& mousePos) const {
    return backToMenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool GameOverScreen::isExitButtonClicked(const sf::Vector2i& mousePos) const {
    return exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

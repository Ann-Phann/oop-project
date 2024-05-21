#include "../include/Menu.h"

Menu::Menu() {
    initializeMenu();
}

void Menu::initializeMenu() {
    // Load font
    if (!font.loadFromFile("assets/fonts/font.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Initialize title
    title.setFont(font);
    title.setString("ICE Smash");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 20);

    // Initialize start button
    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition(540.f, 400.f);

    // Initialize start button text
    startButtonText.setFont(font);
    startButtonText.setString("Start");
    startButtonText.setCharacterSize(30);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(
        startButton.getPosition().x + (startButton.getSize().x - startButtonText.getLocalBounds().width) / 2,
        startButton.getPosition().y + (startButton.getSize().y - startButtonText.getLocalBounds().height) / 2
    );
}

void Menu::render(sf::RenderTarget& target) const {
    target.draw(title);
    target.draw(startButton);
    target.draw(startButtonText);
}

bool Menu::handleInput(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true; // Start button clicked
        }
    }

    return false;
}

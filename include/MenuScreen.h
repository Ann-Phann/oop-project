#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>

class MenuScreen {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text title;
    sf::Text playButton;
    sf::Text highScoresButton;
    sf::Text exitButton;

    sf::Color defaultColor;
    sf::Color hoverColor;

    void initializeText(sf::Text &text, const std::string &str, float x, float y);

public:
    MenuScreen();
    void update(sf::RenderWindow &window);
    void render(sf::RenderTarget& target) const;
    bool isPlayButtonClicked(sf::Vector2i mousePos) const;
    bool isHighScoresButtonClicked(sf::Vector2i mousePos) const;
    bool isExitButtonClicked(sf::Vector2i mousePos) const;
};

#endif // MENUSCREEN_H

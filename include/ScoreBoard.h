#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include<iostream>
#include <SFML/Graphics.hpp>

class Scoreboard {
private:
    int totalPoints;
    //display points as text
    sf::Font font;
    sf::Text pointText;

public:
    Scoreboard();

    void addScores();
    void updatePoints();
    void render(sf::RenderTarget& target) const;

    //functions to initialize the font and text for score
    void initializePointText();
};

#endif // SCOREBOARD_H

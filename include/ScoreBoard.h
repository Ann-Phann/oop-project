#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @brief The Scoreboard class manages the display and updating of the game's score.
 *
 * This class handles adding scores, updating the displayed score, and rendering the score on the screen.
 */
class Scoreboard {
private:
    int totalPoints;              // Total points scored
    sf::Font font;                // Font for displaying the score
    sf::Text pointText;           // Text displaying the current score

public:
    Scoreboard();

    // Other methods
    void addScores(int scoreIncrement);       // Adds a score increment to the total points
    void updatePoints();                      // Updates the displayed score text
    void render(sf::RenderTarget& target) const; // Renders the score text
    int getScores();                    // Gets the total points
};

#endif // SCOREBOARD_H

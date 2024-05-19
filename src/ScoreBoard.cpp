#include "../include/Scoreboard.h"

void Scoreboard:: initializePointText()
{
    // Load font
    if (!font.loadFromFile("assets/fonts/scoreFont.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    } else {
    // Set font to text
    pointText.setFont(font);
    pointText.setCharacterSize(25);

    // Set text color
    pointText.setFillColor(sf::Color::White);
    // Set text position
    pointText.setPosition(50.f, 961.f);
    }
}
Scoreboard::Scoreboard() : totalPoints(0) {
    this-> initializePointText();
}

void Scoreboard::addScores() {
    totalPoints += 70;

}

void Scoreboard::updatePoints() {
    pointText.setString("Scores: " + std::to_string(totalPoints));

}

void Scoreboard::render(sf::RenderTarget& target) const {
    target.draw(pointText);
}





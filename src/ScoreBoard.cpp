 #include "../include/Scoreboard.h"


Scoreboard::Scoreboard() : totalPoints(0) {
      // Load font
    if (!font.loadFromFile("assets/fonts/scoreFont.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    } else {
    //Set properties for pointText
        pointText.setFont(font);
        pointText.setCharacterSize(25);
        pointText.setFillColor(sf::Color::White);
        pointText.setPosition(1000.f, 961.f);
    }
}

// Add scores to the total points
void Scoreboard::addScores(int scoreIncrement) {
    totalPoints += (100 * scoreIncrement)  ;
}

void Scoreboard::updatePoints() {
    pointText.setString("Scores : " + std::to_string(totalPoints));
}

int Scoreboard::getScores() {
    return totalPoints;
}

// Render the score text
void Scoreboard::render(sf::RenderTarget& target) const {
    std::cout << "Rendering point text" << std::endl;
    target.draw(pointText);    
}





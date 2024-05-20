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

void Scoreboard::addScores() {
    totalPoints += 70 ;
}

void Scoreboard::updatePoints() {
    pointText.setString("Scores : " + std::to_string(totalPoints));
}

int Scoreboard::getScores() {
    return totalPoints;
}

void Scoreboard::render(sf::RenderTarget& target) const {
    std::cout << "Rendering point text" << std::endl;
    target.draw(pointText);    
}





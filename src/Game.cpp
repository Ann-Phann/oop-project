#include "../include/Game.h"

//constructor and destructor
Game::Game()
{
    this->initializeVariables();
    this->initializeWindow();
    this->initializeBackground();
    this->initializeText();
    this->initializeLimitLine();
}

Game::~Game()
{
    delete this->window;
}

//privarte functions
void Game:: initializeVariables()
{
    this->window = nullptr;
    this->endGame = false;
    
}

void Game:: initializeWindow()
{
    this->videoMode.height = 1024;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(videoMode, "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game:: initializeBackground()
{
    // Load a sprite to display
    if(!backgroundTexture.loadFromFile("assets/images/blue.jpg"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void Game:: initializeText()
{
    //Create Heading to display
    if (!font.loadFromFile("assets/fonts/font.ttf"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else 
    {
        text.setFont(font);
        text.setString("ICE Smash");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);  
        text.setPosition(100, 50);
    }  
}

void Game::initializeLimitLine()
{
    // initialize Limit Line
    this->limitLine.setSize(sf::Vector2f(1280.f, 10.f));
    this->limitLine.setFillColor(sf::Color::Red);
    this->limitLine.setPosition(0.f, 911.f); // Position gun on top of the base

}

// void Game:: initializeBlocks(){
//     int top = 0;
//     int left = 0;
//     for (int i = 0; i < 5; i++){
//         blocks.push_back(new NormalBlock(top, left));
//         left += 210;
//     }
// }


//functions
void Game::updateEvent()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
        }
    }
}

void Game::update(sf::Time dt)
{
    if(!window->isOpen()) return;
    
    this->updateEvent();
    this->cannon.update(dt, *this->window);
    this->cannon.ballsHitBlock(this->normalBlock);
}
void Game:: render()
{
    //clear window (clear old frame)
    this->window->clear();

    //draw background
    this->window->draw(this->backgroundSprite);
    this->window->draw(this->text);
    this->window->draw(this->limitLine);

    //draw game objects
    this->window->draw(this->cannon);

    //draw block objects
    this->window->draw(this->normalBlock);
    
    
    //display frame in window
    this->window->display();
}

//accessor
const bool Game:: running() const
{
    return this-> window->isOpen();
}

// void Game::removeBock(Block* block){
//     auto it = std::find(blocks.begin(), blocks.end(), block);
//     if (it != blocks.end()) {
//         delete *it; // Free the memory
//         blocks.erase(it); // Remove from the vector
//     }
// }
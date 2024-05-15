#include "../include/NormalBlock.h"
#include <typeinfo>

NormalBlock::NormalBlock() : Block()
{
    this->strength = 1;
    this->initializeBlock();
    this->initializeBlockFont();
}



NormalBlock::~NormalBlock() {
    // Destructor
}


void NormalBlock::initializeBlock() {
    // Set specific properties for NormalBlock
    size = sf::Vector2f(210.f, 105.f);
    block.setSize(size); // Use the same size as defined in Block
    block.setFillColor(sf::Color::Green); // Different color for NormalBlock
    block.setOutlineThickness(5.f);
    block.setOutlineColor(sf::Color::White);
}

void NormalBlock:: initializeBlockFont()
{
    if (!blockFont.loadFromFile("assets/fonts/Roboto-Black.ttf"))
    {
        std::cout << "Failed to load background image!" << std::endl;
    } else {
    blockStrength.setFont(blockFont);
    blockStrength.setCharacterSize(20.f);
    blockStrength.setFillColor(sf::Color::Red);
    blockStrength.setPosition(block.getPosition().x/2, block.getPosition().y/2);
    std::cout << "Block Strength: " << std::to_string(this->getStrength()) << std::endl;
    blockStrength.setString(std::to_string(this->getStrength()));

    }  
    sf::FloatRect textRect = blockStrength.getLocalBounds();
    blockStrength.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    blockStrength.setPosition(block.getPosition().x + block.getSize().x/2.0f, block.getPosition().y + block.getSize().y/2.0f);
    
}

void NormalBlock::update(Ball& ball) {
    // Implement how the NormalBlock should update its state
    // If the block involves animation or any state change, handle it here
    this->hitBall(ball);
}

void NormalBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        target.draw(block, states); // Draw the block with the current states
        target.draw(blockStrength, states);
}

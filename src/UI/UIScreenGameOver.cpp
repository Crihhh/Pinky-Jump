#include "UI/UIScreenGameOver.h"

UIScreenGameOver::UIScreenGameOver()
{
    m_font.loadFromFile("../Data/Fonts/GOUDYSTO.TTF");

    m_text.setFont(m_font);
    m_text.setString("GAME OVER");
    m_text.setCharacterSize(64);
    m_text.setFillColor(sf::Color::Red);
}

void UIScreenGameOver::update(float)
{
    //
}

void UIScreenGameOver::render(sf::RenderWindow& window)
{
    //to center text in the middle of the widow
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.left + bounds.width / 2.f,bounds.top + bounds.height / 2.f);
    sf::Vector2u size = window.getSize();
    m_text.setPosition(size.x / 2.f, size.y / 2.f);
    window.draw(m_text);
    
}
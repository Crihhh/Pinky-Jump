#include "UI/UIScreenVictory.h"

UIScreenVictory::UIScreenVictory()
{
    m_font.loadFromFile("../Data/Fonts/GOUDYSTO.TTF");
    m_text.setFont(m_font);
    m_text.setString("VICTORY");
    m_text.setCharacterSize(64);
    m_text.setFillColor(sf::Color::Yellow);
}

void UIScreenVictory::update(float)
{
   //
}

void UIScreenVictory::render(sf::RenderWindow& window)
{
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    sf::Vector2u size = window.getSize();
    m_text.setPosition(size.x / 2.f, size.y / 2.f);
    window.draw(m_text);
}
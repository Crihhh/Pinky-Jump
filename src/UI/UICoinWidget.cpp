#include <UI/UICoinWidget.h>
#include <Core/AssetManager.h>
#include "SFML/Graphics.hpp"

UICoinWidget::UICoinWidget()
{
    auto tex = AssetManager::getInstance()->loadTexture("../Data/Images/UI/hud_coin.png");

    m_icon.setTexture(*tex);
    m_icon.setPosition(20.f, 100.f);

    m_font.loadFromFile("../Data/Fonts/GOUDYSTO.TTF");

    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setPosition(90.f, 120.f);
}

void UICoinWidget::setCoins(int coins)
{
    m_text.setString(std::to_string(coins));
}

void UICoinWidget::render(sf::RenderWindow& window)
{
    window.draw(m_icon);
    window.draw(m_text);
}

void UICoinWidget::update(float deltaMiliseconds)
{
    //
}
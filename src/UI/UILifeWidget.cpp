#include <UI/UILifeWidget.h>
#include <Core/AssetManager.h>

UILifeWidget::UILifeWidget()
{
    auto tex = AssetManager::getInstance()->loadTexture("../Data/Images/UI/hud_heart.png");

    for (int i = 0; i < 3; ++i)
    {
        m_hearts[i].setTexture(*tex);
        m_hearts[i].setPosition(20.f + i * 70.f, 20.f);
    }
}

void UILifeWidget::setLives(int lives)
{
    for (int i = 0; i < 3; ++i)
    {
        if (i < lives)
            m_hearts[i].setColor(sf::Color::White);
        else
            m_hearts[i].setColor(sf::Color(80, 80, 80));
    }
}

void UILifeWidget::render(sf::RenderWindow& window)
{
    for (auto& h : m_hearts)
        window.draw(h);
}
void UILifeWidget::update(float deltaMiliseconds)
{
    //
}
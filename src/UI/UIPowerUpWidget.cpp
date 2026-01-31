#include <UI/UIPowerUpWidget.h>
#include <Core/AssetManager.h>

UIPowerUpWidget::UIPowerUpWidget()
{
    auto tex = AssetManager::getInstance()->loadTexture("../Data/Images/UI/hud_powerUp_Jump.png");

    m_icon.setTexture(*tex);
    m_icon.setPosition(20.f, 180.f);
}

void UIPowerUpWidget::setActive(bool active)
{
    m_active = active;
}

void UIPowerUpWidget::render(sf::RenderWindow& window)
{
    if (m_active)
        window.draw(m_icon);
}

void UIPowerUpWidget::update(float deltaMiliseconds)
{
    
}
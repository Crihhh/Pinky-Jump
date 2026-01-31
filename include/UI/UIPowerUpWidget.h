#pragma once
#include <vector>
#include <functional>
#include "UI/UIWidget.h"
#include "SFML/Graphics.hpp"

class UIPowerUpWidget : public UIWidget
{
public:
    UIPowerUpWidget();
    void setActive(bool active);

    void update(float deltaMiliseconds) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_icon;
    bool m_active{ false };
};
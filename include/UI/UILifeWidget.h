#pragma once
#include <vector>
#include <functional>
#include "UI/UIWidget.h"
#include "SFML/Graphics.hpp"

class UILifeWidget : public UIWidget
{
public:
    UILifeWidget();
    void setLives(int lives);

    void update(float deltaMiliseconds) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_hearts[3];
};
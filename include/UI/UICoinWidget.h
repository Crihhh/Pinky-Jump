#pragma once
#include <vector>
#include <functional>
#include "UI/UIWidget.h"
#include "SFML/Graphics.hpp"

class UICoinWidget : public UIWidget
{
public:
    UICoinWidget();
    void setCoins(int coins);

    void update(float deltaMiliseconds) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_icon;
    sf::Text m_text;
    sf::Font m_font;
};
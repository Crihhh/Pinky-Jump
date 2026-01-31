#pragma once
#include "UI/UIScreen.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class UIScreenVictory : public UIScreen
{
public:
    UIScreenVictory();
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font m_font;
    sf::Text m_text;
};
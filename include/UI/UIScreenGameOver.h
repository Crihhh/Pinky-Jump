#pragma once
#include "UI/UIScreen.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class UIScreenGameOver : public UIScreen
{
public:
    UIScreenGameOver();
    void update(float delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font m_font;
    sf::Text m_text;
};
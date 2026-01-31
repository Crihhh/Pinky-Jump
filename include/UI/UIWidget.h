#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace sf
{
	class RenderWindow;
};

class UIWidget
{
public:
	virtual void update(float deltaMiliseconds) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
protected:
	sf::Vector2f m_position;
};
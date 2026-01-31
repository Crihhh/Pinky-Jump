#pragma once
#include <vector>
#include <functional>
#include "SFML/Graphics/RectangleShape.hpp"
#include <UI/UIWidget.h>

class UIScreen
{
public:
	virtual ~UIScreen();

	virtual void update(float delta);
	virtual void render(sf::RenderWindow& window);
protected:
	std::vector<UIWidget*> m_widgets;
};
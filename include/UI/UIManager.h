#pragma once
#include <vector>
#include <functional>
#include "SFML/Graphics/RectangleShape.hpp"
#include <UI/UIScreen.h>

class Player;

class UIManager
{
public:

	enum UIState
	{
		State_MainMenu,
		State_HUD,
		State_Pause,
		State_Victory,
		State_GameOver,

		State_Count
	};

	UIManager(Player* player);
	~UIManager();

	void setState(UIState state);
	void update(float delta);
	void render(sf::RenderWindow& window);

	UIScreen* getCurrentScreen();

private:
	UIScreen* m_states[State_Count]{};
	UIState m_currentState;

};

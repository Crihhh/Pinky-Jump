#pragma once

#include <cstdint>
#include <string>
#include <Render/Camera.h>
#include "UI/UIManager.h"

namespace sf
{
	class RenderWindow;
}

class World;

class Game
{
	public:

		struct GameCreateInfo
		{
			std::string gameTitle{};
			uint32_t screenWidth{0};
			uint32_t screenHeight{0};
			uint32_t frameRateLimit{0};
		};

		~Game();

		bool init(GameCreateInfo& createInfo);

		bool isRunning() const;

		void update(uint32_t deltaMilliseconds);
		void render();

	private:

		sf::RenderWindow* m_window{ nullptr };
		World* m_world{ nullptr };
		UIManager* m_uiManager{ nullptr };
		Camera m_camera;
};
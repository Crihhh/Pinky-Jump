#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <vector> 
#include <Gameplay/ElementsManager.h>

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;
class Player;
class ElementsManager;

class World
{
	public:

		
		~World();

		// TO-DO: Ideally the scene should be read from file.
		bool load();

		// To-Do: Implement a unload()

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);
		
		//CAMERA
		sf::Vector2f getWorldSize() const;
		sf::Vector2f getPlayerPosition() const;

		
		bool isGameOver() const;
		bool isVictory() const;

		void checkGoalTrigger();

		//UI
		Player* getPlayer() const;
		

	private:

		void spawn();
		void loadCollisions();
		void loadPlayer();
		void loadEnemies();
		void loadItems();

		//Items
		void checkItemCollisions();

		//Hit
		void collisionsEnemyPlayer();
		void playerIsFalling();


		// To-Do: This should be in its own class, something like "Level" should work
		tmx::Map* m_map{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };

		//Spawns
		sf::Vector2f playerSpawn{ 0.f, 0.f };
		std::vector<sf::Vector2f> m_enemySpawns;
		std::vector<sf::Vector2f> m_coinSpawns;
		std::vector<sf::Vector2f> m_powerUpSpawns;
		
		std::vector<sf::FloatRect> m_colliders;

		//Goal
		sf::FloatRect m_goalTrigger;
		bool m_victory = false;

		//Elements
		ElementsManager m_elementsManager;
};
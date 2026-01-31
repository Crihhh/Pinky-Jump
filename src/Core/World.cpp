#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Gameplay/Zombie.h>
#include <Gameplay/Player.h>
#include <Gameplay/Coin.h>
#include <Gameplay/PowerUp.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>
#include <Gameplay/PowerUpType.h>

#include <Gameplay/Item.h>
#include <iostream>

World::~World()
{
	delete m_layerZero;
	delete m_layerOne;
	delete m_layerTwo;
	delete m_map;
	m_colliders.clear();
}

//DIVIDIR FUNCIONALIDADES
bool World::load()
{
	Coin::reset();
	m_victory = false;
	m_enemySpawns.clear();
	m_coinSpawns.clear();
	m_powerUpSpawns.clear();
	m_colliders.clear();
	// To-Do, Load level: this should have its own class

	m_map = new tmx::Map();

	if (!m_map->load("../Data/map.tmx"))
		return false;

	
	loadCollisions();
	spawn();
	loadPlayer();
	loadEnemies();
	loadItems();
	
	

	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);
	m_layerTwo = new MapLayer(*m_map, 2);

	constexpr float millisecondsToSeconds = 1 / 1000.f;

	// To-Do, read ALL from file, this is just a quick example to understand that here is where entities are created but consider grouping/managing actors in a smarter way

	return true;
}

void World::spawn()
{
	if (!m_map)
		return;
	m_enemySpawns.clear();
	m_coinSpawns.clear();


	for (const auto& layer : m_map->getLayers())
	{

		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();

			if (objectLayer.getName() == "Spawns")
			{

				for (const auto& obj : objectLayer.getObjects())
				{
					if (obj.getName() == "PlayerSpawn")
					{
						auto pos = obj.getPosition();
						playerSpawn = { (float)pos.x, (float)pos.y };
						
					}
					else if (obj.getName() == "Enemy")
					{
						auto pos = obj.getPosition();
						m_enemySpawns.emplace_back(static_cast<float>(pos.x),static_cast<float>(pos.y));
					}
				}
			}
			else if (objectLayer.getName() == "Objects")
			{
				for (const auto& obj : objectLayer.getObjects())
				{
					if (obj.getName() == "Coin")
					{
						auto pos = obj.getPosition();
						m_coinSpawns.emplace_back(static_cast<float>(pos.x), static_cast<float>(pos.y));

					}
					else if (obj.getName() == "PowerUp")
					{
						auto pos = obj.getPosition();
						m_powerUpSpawns.emplace_back(static_cast<float>(pos.x), static_cast<float>(pos.y));
					}
				}
			}
		}
		
	}
}
void World::loadPlayer()
{
	//Player
	Player* player = new Player();
	Character::CharacterDescriptor playerDescriptor;
	playerDescriptor.texture = AssetManager::getInstance()->loadTexture("../Data/Images/Character/character.png");
	playerDescriptor.textureRect = { 0, 0, 64, 64 };
	playerDescriptor.position = playerSpawn;
	playerDescriptor.moveSpeed = 400.f;

	if (!player->init(playerDescriptor))
	{
		delete player;
		return;
	}
	
	player->setColliders(&m_colliders);
	m_elementsManager.setPlayer(player);
}

Player* World::getPlayer() const
{
	return m_elementsManager.getPlayer();
}
void World::loadEnemies()
{
	//Enemies

	for (const auto& spawnPosEnemy : m_enemySpawns)
	{
		Zombie* zombie = new Zombie();
		Character::CharacterDescriptor zombieDescriptor;
		zombieDescriptor.texture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/saw_a.png");
		zombieDescriptor.textureRect = { 0, 0, 64, 64 };
		zombieDescriptor.position = spawnPosEnemy;
		zombieDescriptor.moveSpeed = 200.f;

		if (!zombie->init(zombieDescriptor))
		{
			delete zombie;
			continue;
		}

		zombie->setColliders(&m_colliders);

		m_elementsManager.addEnemy(zombie);
	}

}
void World::loadItems()
{
	//Coins
	for (const auto& spawnPosCoin : m_coinSpawns)
	{
		Coin* coin = new Coin();
		Item::ItemDescriptor itemeDescriptor;
		itemeDescriptor.texture = AssetManager::getInstance()->loadTexture("../Data/Images/Items/coin_gold.png");
		itemeDescriptor.textureRect = { 0, 0, 64, 64 };
		itemeDescriptor.position = spawnPosCoin;


		if (!coin->init(itemeDescriptor))
		{
			delete coin;
			continue;
		}

		m_elementsManager.addCoin(coin);
	}

	//PowerUp
	for (const auto& spawnPosCoin : m_powerUpSpawns)
	{
		PowerUp* powerUp = new PowerUp();
		Item::ItemDescriptor itemeDescriptor;
		itemeDescriptor.texture = AssetManager::getInstance()->loadTexture("../Data/Images/Items/powerUp_Jump.png");
		itemeDescriptor.textureRect = { 0, 0, 64, 64 };
		itemeDescriptor.position = spawnPosCoin;

		if (!powerUp->init(itemeDescriptor, PowerUpType::Jump))
		{
			delete powerUp;
			continue;
		}

		m_elementsManager.addPowerUp(powerUp);
	}
}

void World::loadCollisions() 
{
	if (!m_map)
		return;
	for (const auto& layer : m_map->getLayers())
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objLayer = layer->getLayerAs<tmx::ObjectGroup>();

			if (objLayer.getName() == "Collision")
			{
				for (const auto& obj : objLayer.getObjects())
				{
					const auto& aabb = obj.getAABB();
					m_colliders.emplace_back(
						aabb.left,
						aabb.top,
						aabb.width,
						aabb.height
					);
				}
			}
			else if (objLayer.getName() == "Objects")
			{
				for (const auto& obj : objLayer.getObjects())
				{
					if (obj.getName() == "Goal")
					{
						const auto& aabb = obj.getAABB();
						sf::FloatRect goal;
						goal.left = aabb.left;
						goal.top = aabb.top;
						goal.width = aabb.width;
						goal.height = aabb.height;

						m_goalTrigger = goal;
						
					}
				}
			}
		}
	}

}

void World::checkItemCollisions()
{
	const sf::FloatRect playerBounds = m_elementsManager.getPlayer()->getBounds();
	for (Coin* coin : m_elementsManager.getCoins())
	{ 
		if (!coin || !coin->isActive())
			continue;

		if (playerBounds.intersects(coin->getBounds()))
		{
			coin->onPickup();
		}
	}

	for (PowerUp* powerUp : m_elementsManager.getPowerUps())
	{
		if (!powerUp || !powerUp->isActive())
			continue;

		if (playerBounds.intersects(powerUp->getBounds()))
		{
			powerUp->onPickup();
			m_elementsManager.getPlayer()->applyPowerUp(powerUp->getType());
		}
	}

}

void World::checkGoalTrigger()
{
	if (m_victory)
		return;

	if (m_elementsManager.getPlayer()->getBounds().intersects(m_goalTrigger))
	{
		m_victory = true;
	}
}

void World::collisionsEnemyPlayer() 
{
	for (Enemy* enemy : m_elementsManager.getEnemies())
	{
		if (!enemy || enemy->isDead())
			continue;

		if (m_elementsManager.getPlayer()->getBounds().intersects(enemy->getBounds()))
		{
			bool playerAbove = m_elementsManager.getPlayer()->getBounds().top + m_elementsManager.getPlayer()->getBounds().height<= enemy->getBounds().top + 10.f;

			bool playerFalling = m_elementsManager.getPlayer()->getVelocity().y > 0.f;

			if (playerAbove && playerFalling)
			{
				enemy->takeDamage(1);

				// Jump again after kill an enemy
				m_elementsManager.getPlayer()->bounce();
			}
			else
			{
				m_elementsManager.getPlayer()->takeDamage(1);
			}
		}
		
	}
}

void World::playerIsFalling()
{
	if (m_elementsManager.getPlayer()->getPosition().y > getWorldSize().y + 200.f)
	{
		m_elementsManager.getPlayer()->kill();
	}
}

sf::Vector2f World::getWorldSize() const
{
	return
	{
		 static_cast<float>(m_map->getTileCount().x * m_map->getTileSize().x),
		 static_cast<float>(m_map->getTileCount().y * m_map->getTileSize().y)
	};
}

sf::Vector2f World::getPlayerPosition() const
{
	return m_elementsManager.getPlayer() ? m_elementsManager.getPlayer()->getPosition() : sf::Vector2f{};
}


void World::update(uint32_t deltaMilliseconds)
{
	if (isGameOver() || isVictory())
		return;
	if (!m_layerZero)
		return;
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));
	m_elementsManager.update(deltaMilliseconds);

	checkItemCollisions();
	collisionsEnemyPlayer();
	playerIsFalling();
	checkGoalTrigger();
}

bool World::isGameOver() const
{
	return m_elementsManager.getPlayer()->isDead();
}

bool World::isVictory() const
{
	return m_victory;
}

void World::render(sf::RenderWindow& window)
{
	if (m_layerZero) window.draw(*m_layerZero);
	if (m_layerOne)  window.draw(*m_layerOne);
	if (m_layerTwo)  window.draw(*m_layerTwo);
	
	m_elementsManager.render(window);

}

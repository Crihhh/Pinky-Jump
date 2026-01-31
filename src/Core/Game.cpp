#include <cassert>
#include <Core/Game.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>



bool Game::init(GameCreateInfo& createInfo)
{
	std::cout << "GAME INIT\n";
	
	assert(m_window == nullptr && m_world == nullptr && "Game is already initialized, we are about to leak memory");

	m_window = new sf::RenderWindow({ createInfo.screenWidth, createInfo.screenHeight }, createInfo.gameTitle);
	m_window->setFramerateLimit(createInfo.frameRateLimit);
	m_world = new World();
	const bool loadOk = m_world->load();

	//Camera
	m_camera.init({static_cast<float>(createInfo.screenWidth),static_cast<float>(createInfo.screenHeight)});
	m_camera.setWorldBounds(m_world->getWorldSize());

	//UI
	m_uiManager = new UIManager(m_world->getPlayer());


	return loadOk;
}

Game::~Game()
{
	// To-Do: make sure m_world is unloaded()

	delete m_world;
	delete m_window;
	delete m_uiManager;
}

bool Game::isRunning() const 
{ 
	return m_window->isOpen(); 
}

void Game::update(uint32_t deltaMilliseconds)
{
	// Check if user closed the window
	for (auto event = sf::Event(); m_window->pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}

	// Update scene here
	if (!m_world->isVictory() && !m_world->isGameOver())
	{
		m_world->update(deltaMilliseconds);
		m_uiManager->setState(UIManager::State_HUD);
		m_uiManager->update(static_cast<float>(deltaMilliseconds)); 
	}
	else
	{
		m_uiManager->setState(m_world->isVictory() ? UIManager::State_Victory : UIManager::State_GameOver);
	}

	
	

	//Camera
	const sf::Vector2f playerPos = m_world->getPlayerPosition();
	m_camera.follow(playerPos);
	m_camera.update();

	
}

void Game::render()
{
	m_window->clear();

	m_window->setView(m_camera.getView());
	m_world->render(*m_window);
	m_window->setView(m_window->getDefaultView());

	//UI
	m_uiManager->render(*m_window);

	m_window->display();
}
#include "Gameplay/ElementsManager.h"
#include <Gameplay/Player.h>
#include <Gameplay/Enemy.h>
#include <Gameplay/Coin.h>
#include <Gameplay/PowerUp.h>

ElementsManager::~ElementsManager()
{
    delete m_player;

    for (Enemy* e : m_enemies) 
        delete e;
    for (Coin* c : m_coins) 
        delete c;
    for (PowerUp* p : m_powerUps) 
        delete p;

    m_enemies.clear();
    m_coins.clear();
    m_powerUps.clear();
}

void ElementsManager::setPlayer(Player* player)
{
    m_player = player;
}

Player* ElementsManager::getPlayer() const
{
    return m_player;
}

void ElementsManager::addEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
}

void ElementsManager::addCoin(Coin* coin)
{
    m_coins.push_back(coin);
}

void ElementsManager::addPowerUp(PowerUp* powerUp)
{
    m_powerUps.push_back(powerUp);
}

//List of enemies
std::vector<Enemy*>& ElementsManager::getEnemies()
{
    return m_enemies;
}
//List of coins
std::vector<Coin*>& ElementsManager::getCoins()
{
    return m_coins;
}
//List os PowerUps
std::vector<PowerUp*>& ElementsManager::getPowerUps()
{
    return m_powerUps;
}

void ElementsManager::update(uint32_t deltaMilliseconds)
{
    if (m_player)
        m_player->update(static_cast<float>(deltaMilliseconds));

    for (Enemy* e : m_enemies)
        if (e) e->update(static_cast<float>(deltaMilliseconds));
}

void ElementsManager::render(sf::RenderWindow& window)
{
    if (m_player)
        m_player->render(window);

    for (Enemy* e : m_enemies)
        if (e) e->render(window);

    for (Coin* c : m_coins)
        if (c && c->isActive()) c->render(window);

    for (PowerUp* p : m_powerUps)
        if (p && p->isActive()) p->render(window);
}
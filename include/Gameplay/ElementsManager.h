#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class Player;
class Enemy;
class Coin;
class PowerUp;

class ElementsManager
{
public:
    ElementsManager() = default;
    ~ElementsManager();

    //Player
    void setPlayer(Player* player);
    Player* getPlayer() const;

    // Elements
    void addEnemy(Enemy* enemy);
    void addCoin(Coin* coin);
    void addPowerUp(PowerUp* powerUp);

   
    std::vector<Enemy*>& getEnemies();
    std::vector<Coin*>& getCoins();
    std::vector<PowerUp*>& getPowerUps();

 
    void update(uint32_t deltaMilliseconds);
    void render(sf::RenderWindow& window);

private:
    Player* m_player{ nullptr };
    std::vector<Enemy*> m_enemies;
    std::vector<Coin*> m_coins;
    std::vector<PowerUp*> m_powerUps;
};
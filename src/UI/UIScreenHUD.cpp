#include <UI/UIScreenHUD.h>
#include <UI/UILifeWidget.h>
#include <UI/UICoinWidget.h>
#include <UI/UIPowerUpWidget.h>
#include <Gameplay/Player.h>
#include <Gameplay/Coin.h>

UIScreenHUD::UIScreenHUD(Player* player)
    : m_player(player)
{
    m_hearts = new UILifeWidget();
    m_coins = new UICoinWidget();
    m_powerUp = new UIPowerUpWidget();

    m_widgets.push_back(m_hearts);
    m_widgets.push_back(m_coins);
    m_widgets.push_back(m_powerUp);
}

void UIScreenHUD::update(float delta)
{
    m_hearts->setLives(m_player->getLives());
    m_coins->setCoins(Coin::getTotalCoins());
    m_powerUp->setActive(m_player->hasPowerUp());

    UIScreen::update(delta);
}
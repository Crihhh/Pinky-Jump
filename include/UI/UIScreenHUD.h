#include "SFML/Graphics/RectangleShape.hpp"
#include <UI/UIScreen.h>
#include <Gameplay/Player.h>

class Player;
class UILifeWidget;
class UICoinWidget;
class UIPowerUpWidget;

class UIScreenHUD : public UIScreen
{
public:
    UIScreenHUD(Player* player);

    void update(float deltaMiliseconds) override;

private:
    Player* m_player{ nullptr };
    UILifeWidget* m_hearts{ nullptr };
    UICoinWidget* m_coins{ nullptr };
    UIPowerUpWidget* m_powerUp{ nullptr };
};
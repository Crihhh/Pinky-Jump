#include <Gameplay/PowerUp.h>

bool PowerUp::init(const ItemDescriptor& ItemDescriptor, PowerUpType type)
{
    m_type = type;
    return Item::init(ItemDescriptor);
}

void PowerUp::onPickup()
{
    if (!m_active)
        return;

    m_active = false;
}
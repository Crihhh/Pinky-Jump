#pragma once
#include <Gameplay/Item.h>
#include <Gameplay/PowerUpType.h>


class PowerUp : public Item
{
public:
    bool init(const ItemDescriptor& desc, PowerUpType type);

    void onPickup() override;

    PowerUpType getType() const { return m_type; }

private:
    PowerUpType m_type = PowerUpType::None;
};
#include <Gameplay/Coin.h>

int Coin::s_totalCoins = 0;

bool Coin::init(const ItemDescriptor& desc)
{
	return Item::init(desc);
}

void Coin::onPickup()
{
	if (!m_active)
		return;

	m_active = false;
	++s_totalCoins;
}

int Coin::getTotalCoins()
{
	return s_totalCoins;
}

void Coin::reset()
{
	s_totalCoins = 0;
}
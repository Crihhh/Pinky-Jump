#pragma once

#include <Gameplay/Item.h>

class Coin : public Item
{
public:
	bool init(const ItemDescriptor& desc);

	void onPickup() override;

	static int getTotalCoins();
	static void reset();

private:
	static int s_totalCoins;
};
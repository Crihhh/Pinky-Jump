#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>

class Item : public GameObject
{
public:
	struct ItemDescriptor
	{
		sf::Vector2f position;
		sf::Texture* texture{ nullptr };
		sf::IntRect textureRect;
	};

	virtual ~Item() = default;

	virtual bool init(const ItemDescriptor& desc);

	virtual void update(float delta) override;
	virtual void render(sf::RenderWindow& window) override;

	// Colission
	sf::FloatRect getBounds() const;

	// Interaction player
	virtual void onPickup() = 0;

	bool isActive() const { return m_active; }

protected:
	sf::Sprite m_sprite;
	bool m_active{ true };
};
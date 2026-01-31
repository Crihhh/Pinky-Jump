#include <Gameplay/Item.h>
#include <SFML/Graphics/RenderWindow.hpp>

bool Item::init(const ItemDescriptor& ItemDescriptor)
{
	if (!ItemDescriptor.texture)
		return false;

	m_sprite.setTexture(*ItemDescriptor.texture);
	m_sprite.setTextureRect(ItemDescriptor.textureRect);
	m_sprite.setPosition(ItemDescriptor.position);
	m_sprite.setOrigin(0.f, 0.f);

	return true;
}

void Item::update(float)
{
	if (!m_active)
		return;
}

void Item::render(sf::RenderWindow& window)
{
	if (!m_active)
		return;

	window.draw(m_sprite);
}

sf::FloatRect Item::getBounds() const
{
	return m_sprite.getGlobalBounds();
}
#include <Gameplay/Enemy.h>
#include <SFML/Graphics/RenderWindow.hpp>

void Enemy::update(float deltaMilliseconds)
{
	if (m_dead)
		return;
	const float time = deltaMilliseconds / 1000.f;
	updateAI(time);
	Character::update(deltaMilliseconds);
	
}
bool Enemy::isGroundAhead(float direction) const
{

	if (!m_colliders || m_colliders->empty())
		return true;

	const sf::FloatRect bounds = m_sprite.getGlobalBounds();

	float probeX = direction > 0
		? bounds.left + bounds.width + 1.f
		: bounds.left - 1.f;

	float probeY = bounds.top + bounds.height + 5.f;

	sf::FloatRect probe(probeX, probeY, 2.f, 2.f);

	for (const auto& c : *m_colliders)
	{
		if (c.intersects(probe))
			return true;
	}

	return false;
}


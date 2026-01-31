#pragma once

#include <Gameplay/Character.h>
#include <SFML/Graphics.hpp>
#include <Gameplay/PowerUpType.h>
#include <unordered_map>

class Player : public Character
{
public:

	struct PlayerDescriptor : CharacterDescriptor
	{
		sf::Vector2f speed{ 0.f, .0f };
		sf::IntRect textureRect;
	};
	enum class PlayerAnim
	{
		Idle,
		Walk,
		Jump
	};

	//Sprite sheet disorganized
	std::unordered_map<PlayerAnim, std::vector<int>> m_animations;

	void update(float deltaMilliseconds) override;
	bool init(const CharacterDescriptor& playerDescriptor);

	//PowerUp
	void applyPowerUp(PowerUpType type);
	bool hasPowerUp() const;

	void bounce();

	int getLives() const { return m_health; }

private:

	void Input();
	void updateAnimation(float dt);

private:
	
	bool m_hasJumpPowerUp{ false };
	PlayerAnim m_currentAnim{ PlayerAnim::Idle };

	//Animation
	int m_animFrameIndex{ 0 };
	float m_animTimer{ 0.f };
	float m_animSpeed{ 0.15f };
	sf::Vector2i m_frameSize{ 64, 64 };
	
};
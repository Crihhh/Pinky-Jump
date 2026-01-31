#pragma once


#include <Gameplay/Character.h>
#include <SFML/Graphics/Sprite.hpp>


class Enemy : public Character
{
	public:

		virtual ~Enemy() = default;

		void update(float deltaMilliseconds) override;


	protected:
		virtual void updateAI(float time) = 0;

		bool isGroundAhead(float direction) const;

};
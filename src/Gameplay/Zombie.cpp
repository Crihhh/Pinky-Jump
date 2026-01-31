#include <Gameplay/Zombie.h>


bool Zombie::init(const CharacterDescriptor& zombieDescriptor)
{
    m_health = 1;
    Character::init(zombieDescriptor);
    return true;
}

void Zombie::updateAI(float deltaMilliseconds)
{

    if (!isGroundAhead(m_direction)|| m_velocity.x == 0.f)
    {
        m_direction *= -1.f;
    }
    m_velocity.x = m_direction * m_moveSpeed;

}



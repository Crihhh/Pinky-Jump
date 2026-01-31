#include <Gameplay/Character.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

bool Character::init(const CharacterDescriptor& CharacterDescriptor)
{
    if (!CharacterDescriptor.texture)
        return false;

    m_moveSpeed = CharacterDescriptor.moveSpeed;

    m_sprite.setTexture(*CharacterDescriptor.texture);
    m_sprite.setTextureRect(CharacterDescriptor.textureRect);
    m_sprite.setPosition(CharacterDescriptor.position);
    m_sprite.setOrigin(0.f, 0.f);

    return true;
}

void Character::update(float deltaMilliseconds)
{
    if (m_dead)
        return;


    const float dt = deltaMilliseconds / 1000.f;

    m_velocity.y += m_gravity * dt;

    moveXWithCollision(m_velocity.x * dt);
    moveYWithCollision(m_velocity.y * dt);
    m_position = m_sprite.getPosition();


    if (m_invulnerable)
    {
        m_invulnerableTime += dt;
        if (m_invulnerableTime >= m_invulnerableDuration)
        {
            m_invulnerable = false;
            m_invulnerableTime = 0.f;
        }
    }
}

void Character::render(sf::RenderWindow& window)
{
    if (!m_dead)
      window.draw(m_sprite);
}

void Character::setColliders(const std::vector<sf::FloatRect>* colliders)
{
    m_colliders = colliders;
}

void Character::moveXWithCollision(float dx)
{
    m_sprite.move(dx, 0.f);

    for (const auto& c : *m_colliders)
    {
        if (m_sprite.getGlobalBounds().intersects(c))
        {
            if (dx > 0)
                m_sprite.setPosition(c.left - m_sprite.getGlobalBounds().width,
                    m_sprite.getPosition().y);
            else if (dx < 0)
                m_sprite.setPosition(c.left + c.width,
                    m_sprite.getPosition().y);

            m_velocity.x = 0.f;
        }
    }
}

void Character::moveYWithCollision(float dy)
{
    m_sprite.move(0.f, dy);
    m_onGround = false;

    for (const auto& c : *m_colliders)
    {
        if (m_sprite.getGlobalBounds().intersects(c))
        {
            if (dy > 0)
            {
                m_sprite.setPosition(m_sprite.getPosition().x,c.top - m_sprite.getGlobalBounds().height);
                m_onGround = true;
            }
            else if (dy < 0)
            {
                m_sprite.setPosition(m_sprite.getPosition().x,
                    c.top + c.height);
            }

            m_velocity.y = 0.f;
        }
    }

}

sf::FloatRect Character::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

//Damage life
void Character::takeDamage(int damage)
{
    if (m_dead || m_invulnerable)
        return;

    m_health -= damage;
    if (m_health <= 0) 
    {
        m_health = 0;
        m_dead = true;
    }
    else
    {
        //invulnerable bc character died with 1 hit
        m_invulnerable = true;
        m_invulnerableTime = 0.f;
    }
      
}
void Character::kill() 
{
    m_health = 0;
    m_dead = true;
}

int  Character:: getHealth() const 
{
    return m_health; 
}
bool Character:: isDead() const 
{
    return m_dead; 
}


const sf::Vector2f& Character::getVelocity() const 
{ 
    return m_velocity; 
}
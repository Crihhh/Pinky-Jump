#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class Character : public GameObject
{
public:
    struct CharacterDescriptor
    {
        sf::Vector2f position;
        sf::Texture* texture{ nullptr };
        sf::IntRect textureRect;
        float moveSpeed{ 0.f };
    };

    virtual ~Character() = default;

    virtual bool init(const CharacterDescriptor& CharacterDescriptor);

    void update(float delta) override;
    void render(sf::RenderWindow& window) override;

    //Collision
    void setColliders(const std::vector<sf::FloatRect>* colliders);
    sf::FloatRect getBounds() const;

    //Damage life
    virtual void takeDamage(int damage);
    void kill();
    int  getHealth() const;
    bool isDead() const;

    //To get speed
    const sf::Vector2f& getVelocity() const;

protected:
    sf::Sprite m_sprite;

    sf::Vector2f m_velocity{ 0.f, 0.f };
    bool m_onGround{ false };

    float m_moveSpeed{ 0.f };
    float m_gravity{ 2000.f };
    float m_jumpForce{ 750.f };

    const std::vector<sf::FloatRect>* m_colliders{ nullptr };

    //Collision
    void moveXWithCollision(float dx);
    void moveYWithCollision(float dy);

    //Damage life
    int m_health = {1};
    bool m_dead = { false };

    //Time to get hit again
    bool m_invulnerable{ false };
    float m_invulnerableTime{ 0.f };
    float m_invulnerableDuration{ 1.f };
};
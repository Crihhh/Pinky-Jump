#include <Gameplay/Player.h>
#include <SFML/Window/Keyboard.hpp>
#include <Gameplay/PowerUpType.h>



bool Player::init(const CharacterDescriptor& playerDescriptor)
{
    m_health = 3;
    
    //The spritesheet doenst have tiles in order
    m_animations[PlayerAnim::Idle] = { 0, 6 };
    m_animations[PlayerAnim::Walk] = { 5, 8 };
    m_animations[PlayerAnim::Jump] = { 7 };

    Character::init(playerDescriptor);
    return true;
}
void Player::update(float deltaMilliseconds)
{
    Input();
    float dt = deltaMilliseconds / 1000.f;
    updateAnimation(dt);
    Character::update(deltaMilliseconds);
}

void Player::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_velocity.x = -m_moveSpeed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_velocity.x = m_moveSpeed;
    else
        m_velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_onGround)
    {
        m_velocity.y = -m_jumpForce;
        m_onGround = false;

    }

    //Sprite direction
    if (m_velocity.x < 0)
    {
        m_sprite.setScale(-1.f, 1.f); 
        m_sprite.setOrigin(static_cast<float>(m_frameSize.x), 0.f);
    }
    else if (m_velocity.x > 0)
    {
        m_sprite.setScale(1.f, 1.f);
        m_sprite.setOrigin(0.f, 0.f);
    }
}

void Player::applyPowerUp(PowerUpType type)
{
    
    switch (type)
    {
    case PowerUpType::Speed:
        m_moveSpeed *= 1.5f;
        break;

    case PowerUpType::Jump:
        m_jumpForce *= 1.3f;
        break;

    }
    m_hasJumpPowerUp = true;
}

bool Player::hasPowerUp() const
{
    return m_hasJumpPowerUp;
}

void Player::bounce()
{
    m_velocity.y = -m_jumpForce * 0.7f;
}

//Animations
void Player::updateAnimation(float dt)
{
    PlayerAnim newAnim = PlayerAnim::Idle;

    if (!m_onGround)
        newAnim = PlayerAnim::Jump;
    else if (std::abs(m_velocity.x) > 0.f)
        newAnim = PlayerAnim::Walk;

    if (newAnim != m_currentAnim)
    {
        m_currentAnim = newAnim;
        m_animFrameIndex = 0;
        m_animTimer = 0.f;
    }

    m_animTimer += dt;
    if (m_animTimer >= m_animSpeed)
    {
        m_animTimer = 0.f;
        m_animFrameIndex++;
        const auto& frames = m_animations[m_currentAnim];
        m_animFrameIndex %= frames.size();
    }

    int frame = m_animations[m_currentAnim][m_animFrameIndex];

    m_sprite.setTextureRect({frame * m_frameSize.x,0,m_frameSize.x,m_frameSize.y});
}
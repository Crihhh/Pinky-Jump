#include <Render/Camera.h>
#include <algorithm>
#include <cstdint>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

void Camera::init(const sf::Vector2f& viewSize)
{
    m_view.setSize(viewSize);
    m_view.setCenter(viewSize.x / 2.f, viewSize.y / 2.f);
}

void Camera::setWorldBounds(const sf::Vector2f& worldSize)
{
    m_worldSize = worldSize;
}

void Camera::follow(const sf::Vector2f& target)
{
    m_target = target;
}

void Camera::update()
{
    sf::Vector2f center = m_view.getCenter();

    float halfW = m_view.getSize().x / 2.f;
    float halfH = m_view.getSize().y / 2.f;

    //ClampCamera
    float clampedTargetX = std::clamp(m_target.x, halfW, m_worldSize.x - halfW);
    float clampedTargetY = std::clamp(m_target.y, halfH, m_worldSize.y - halfH);

    //Smooth movement
    const float smooth = 0.12f;
    center.x += (clampedTargetX - center.x) * smooth;
    center.y += (clampedTargetY - center.y) * smooth;

    m_view.setCenter(center);
}

const sf::View& Camera::getView() const
{
    return m_view;
}
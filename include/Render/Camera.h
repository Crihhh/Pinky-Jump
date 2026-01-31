#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class Camera
{
public:
    void init(const sf::Vector2f& viewSize);

    // Limits
    void setWorldBounds(const sf::Vector2f& worldSize);

    // Follow character
    void follow(const sf::Vector2f& target);
    void update();

    
    const sf::View& getView() const;
   

private:
    sf::View m_view;
    sf::Vector2f m_worldSize{ 0.f, 0.f };
    //Avoid camera jumps
    sf::Vector2f m_target { 0.f, 0.f };
};
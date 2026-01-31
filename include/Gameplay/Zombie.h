#pragma once

#include <Gameplay/Enemy.h>

class Zombie : public Enemy
{
public:
    bool init(const CharacterDescriptor& zombieDescriptor);
protected:
    void updateAI(float time) override;
private:
    float m_direction = -1.f;
};
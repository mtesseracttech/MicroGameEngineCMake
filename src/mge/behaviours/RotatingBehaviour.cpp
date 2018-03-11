#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour() : AbstractBehaviour()
{
    //ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
    //dtor
}

void RotatingBehaviour::update(float p_step)
{
    m_owner->rotate(p_step * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // rotates 45� per second
}

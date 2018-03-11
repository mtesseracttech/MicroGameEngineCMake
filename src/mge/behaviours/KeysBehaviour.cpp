#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

KeysBehaviour::KeysBehaviour(float p_moveSpeed, float p_turnSpeed)
        : AbstractBehaviour(), m_moveSpeed(p_moveSpeed), m_turnSpeed(p_turnSpeed)
{
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update(float p_step)
{
    float moveSpeed = 0.0f; //default if no keys
    float turnSpeed = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        moveSpeed = m_moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        moveSpeed = -m_moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        turnSpeed = -m_turnSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        turnSpeed = +m_turnSpeed;
    }
    //translate the object in its own local space
    m_owner->translate(glm::vec3(0.0f, 0.0f, moveSpeed * p_step));

    //we can also translate directly, basically we take the z axis from the matrix
    //which is normalized and multiply it by moveSpeed*step, than we add it to the
    //translation component
    //glm::mat4 transform = m_owner->getTransform();
    //transform[3] += transform[2] * moveSpeed*p_step;
    //m_owner->setTransform(transform);

    //rotate the object in its own local space
    m_owner->rotate(glm::radians(turnSpeed * p_step), glm::vec3(0.0f, 1.0f, 0.0f));

    //NOTE:
    //The reason the above happens in the local space of the object and not in the world space
    //is that we use the m_owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
    //The methods multiply the current transform with the translation/rotation matrix from left to right
    //meaning everything happens in local space.
}

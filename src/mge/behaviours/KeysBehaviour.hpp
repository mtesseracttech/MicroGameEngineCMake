#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
private:
    float m_moveSpeed;
    float m_turnSpeed;

public:
    KeysBehaviour(float p_moveSpeed = 5, float p_turnSpeed = 45);

    virtual ~KeysBehaviour();

    virtual void update(float p_step);
};

#endif // KEYSBEHAVIOUR_H

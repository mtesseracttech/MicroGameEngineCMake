#ifndef ROTATINGBEHAVIOUR_H
#define ROTATINGBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin
 */
class RotatingBehaviour : public AbstractBehaviour
{
public:
    RotatingBehaviour();

    virtual ~RotatingBehaviour();

    virtual void update(float p_step);

};

#endif // ROTATINGBEHAVIOUR_H

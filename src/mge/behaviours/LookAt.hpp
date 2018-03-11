#ifndef LookAt_H
#define LookAt_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Keeps the owner looking at the given target.
 */
class LookAt : public AbstractBehaviour
{
private:
    GameObject* m_target;   //what are we looking at?
public:
    LookAt(GameObject* p_target);

    virtual ~LookAt();

    virtual void update(float p_step);

private:

    LookAt(const LookAt&);

    LookAt& operator=(const LookAt&);

};

#endif // LookAt_H

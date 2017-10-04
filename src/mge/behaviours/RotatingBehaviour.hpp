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

		virtual void update(float pStep);

};

#endif // ROTATINGBEHAVIOUR_H

#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
		KeysBehaviour(float pMoveSpeed = 5, float pTurnSpeed = 45);
		virtual ~KeysBehaviour();
		virtual void update( float pStep );

    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // KEYSBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/LookAt.hpp"
#include "mge/core/GameObject.hpp"

LookAt::LookAt(GameObject* p_target) : AbstractBehaviour(), m_target(p_target)
{
}

LookAt::~LookAt()
{
    //dtor
}

/**
 * Looks at the given target
 */
void LookAt::update(float p_step)
{
    //two ways of doing the same thing:

    //Through GLM
    /*
    m_owner->setTransform(
        glm::inverse (
            glm::lookAt (m_owner->getWorldPosition(), m_target->getWorldPosition(), glm::vec3(0,1,0))
        )
    );
    */

    //manually
    //the other way then you would expect, the camera is flipped over the z axis we are staring out of its a.. basically ;)
    //this is due to how the perspective matrix is set up
    glm::vec3 forward = glm::normalize(m_owner->getLocalPosition() - m_target->getLocalPosition());
    glm::vec3 right   = glm::cross(glm::vec3(0, 1, 0), forward);
    glm::vec3 up      = glm::cross(forward, right);

    m_owner->setTransform(
            glm::mat4(glm::vec4(right, 0), glm::vec4(up, 0), glm::vec4(forward, 0),
                      glm::vec4(m_owner->getLocalPosition(), 1))
    );
}

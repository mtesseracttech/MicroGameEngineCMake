#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "mge/core/GameObject.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world to view matrix by taking the inverse of the camera transform
 * (see renderer).
 */
class Camera : public GameObject
{
	public:
		Camera(
            std::string pName = "camera",
            glm::vec3 pPosition = glm::vec3( 0.0f, 3.0f, 5.0f ),
            glm::mat4 pProjectionMatrix = glm::perspective (glm::radians(60.0f), 4.0f/3.0f, 0.1f, 1000.0f  )
        );

		virtual ~Camera();

        glm::mat4& getProjection();

	private:
		glm::mat4 _projection;

};

#endif // CAMERA_H

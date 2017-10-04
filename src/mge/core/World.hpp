#ifndef WORLD_H
#define WORLD_H

#include "mge/core/GameObject.hpp"

class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

	private:
	    Camera* _mainCamera;

        World(const World&);
        World& operator=(const World&);
};


#endif // WORLD_H

#ifndef WORLD_H
#define WORLD_H

#include "mge/core/GameObject.hpp"

class Camera;

class World : public GameObject
{
private:
    Camera* m_mainCamera;

public:
    World();

    void setMainCamera(Camera* p_camera);

    Camera* getMainCamera();

private:
    World(const World&);

    World& operator=(const World&);
};


#endif // WORLD_H

#include "mge/core/World.hpp"

using namespace std;

World::World() : GameObject("root"), m_mainCamera(nullptr)
{
    //ctor
}

void World::setMainCamera(Camera* p_camera)
{
    if (p_camera != nullptr) m_mainCamera = p_camera;
}

Camera* World::getMainCamera()
{
    return m_mainCamera;
}

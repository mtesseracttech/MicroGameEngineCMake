#include <iostream>
#include <GL/glew.h>
#include "mge/core/Renderer.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // default GL_BACK
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor((float) 0x2d / 0xff, (float) 0x6b / 0xff, (float) 0xce / 0xff, 1.0f);
}

Renderer::~Renderer()
{
}

void Renderer::setClearColor(int pR, int pG, int pB)
{
    glClearColor((float) pR / 0xff, (float) pG / 0xff, (float) pB / 0xff, 1.0f);
}

void Renderer::render(World* p_world)
{
    Camera* camera = p_world->getMainCamera();
    render(p_world, p_world->getTransform(), glm::inverse(camera->getWorldTransform()), camera->getProjection(), true);
}

void Renderer::render(GameObject* p_gameObject, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                      const glm::mat4& p_projectionMatrix, bool p_recursive)
{
    renderSelf(p_gameObject, p_modelMatrix, p_viewMatrix, p_projectionMatrix);
    if (p_recursive) renderChildren(p_gameObject, p_modelMatrix, p_viewMatrix, p_projectionMatrix, p_recursive);
}

void Renderer::renderSelf(GameObject* p_gameObject, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                          const glm::mat4& p_projectionMatrix)
{
    renderMesh(p_gameObject->getMesh(), p_gameObject->getMaterial(), p_modelMatrix, p_viewMatrix, p_projectionMatrix);
    renderMeshDebugInfo(p_gameObject->getMesh(), p_modelMatrix, p_viewMatrix, p_projectionMatrix);
}

void Renderer::renderMesh(Mesh* p_mesh, AbstractMaterial* p_material, const glm::mat4& p_modelMatrix,
                          const glm::mat4& p_viewMatrix, const glm::mat4& p_projectionMatrix)
{
    if (p_mesh != nullptr && p_material != nullptr)
        p_material->render(p_mesh, p_modelMatrix, p_viewMatrix, p_projectionMatrix);
}

void Renderer::renderMeshDebugInfo(Mesh* p_mesh, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                                   const glm::mat4& p_projectionMatrix)
{
    if (p_mesh != nullptr) p_mesh->drawDebugInfo(p_modelMatrix, p_viewMatrix, p_projectionMatrix);
}

void Renderer::renderChildren(GameObject* p_gameObject, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                              const glm::mat4& p_projectionMatrix, bool p_recursive)
{
    int childCount = p_gameObject->getChildCount();
    if (childCount < 1) return;

    //note that with a loop like this, deleting children during rendering is not a good idea :)
    GameObject* child = 0;
    for (int i = 0; i < childCount; i++)
    {
        child = p_gameObject->getChildAt(i);
        render(child, p_modelMatrix * child->getTransform(), p_viewMatrix, p_projectionMatrix, p_recursive);
    }
}



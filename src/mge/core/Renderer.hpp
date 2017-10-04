#ifndef RENDERER_H
#define RENDERER_H

#include <glm.hpp>

class World;
class GameObject;
class Camera;
class Mesh;
class AbstractMaterial;

/**
 * Renderer implements a default single pass forward renderer.
 */
class Renderer
{
	public:
		Renderer();
		virtual ~Renderer();

        //utility call
        void setClearColor (int pR, int pG, int pB);

        //convenience method to render whole world
        void render (World* pWorld);

        //render specific game object within the world, and optionally all its children
        void render(GameObject* pGameObject, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive);

        //renders a specific mesh at the given positions etc with the given material
        void renderMesh (Mesh* pMesh, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);
        void renderChildren (GameObject* pGameObject, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive);

        //helper method to render all the children of a gameobject
        void renderMeshDebugInfo (Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);

    private:
        //helper method to render a single gameobject
        void renderSelf (GameObject* pGameObject, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);

};

#endif // RENDERER_H

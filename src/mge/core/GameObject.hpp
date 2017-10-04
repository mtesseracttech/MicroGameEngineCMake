#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>
#include <glm.hpp>

class AbstractBehaviour;
class AbstractMaterial;
class World;
class Mesh;

/**
 * A GameObject wraps all data required to display an (interactive / dynamic) object, but knows nothing about OpenGL or rendering.
 * You will need to alter this class to add colliders etc.
 */
class GameObject
{
	public:
		GameObject(std::string pName = NULL, glm::vec3 pPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) );
		virtual ~GameObject();

        void setName (std::string pName);
        std::string getName() const;

        //contains local rotation, scale, position
		void setTransform (const glm::mat4& pTransform);
        const glm::mat4& getTransform() const;

        //access just the local position
		void setLocalPosition (glm::vec3 pPosition);
		glm::vec3 getLocalPosition() const;

        //get the objects world position by combining transforms
        //expensive operations!! Improvement would be to cache these transforms!
		glm::vec3 getWorldPosition() const;
		glm::mat4 getWorldTransform() const;

        //change local position, rotation, scaling
		void translate(glm::vec3 pTranslation);
		void rotate(float pAngle, glm::vec3 pAxis);
		void scale(glm::vec3 pScale);

        //mesh and material should be shared as much as possible
		void setMesh(Mesh* pMesh);
		Mesh* getMesh() const;

		void setMaterial (AbstractMaterial* pMaterial);
		AbstractMaterial* getMaterial() const;

		void setBehaviour(AbstractBehaviour* pBehaviour);
		AbstractBehaviour* getBehaviour() const;

		virtual void update(float pStep);

        //child management

        //shortcut to set the parent of pChild to ourselves
		void add (GameObject* pChild);
		//shortcut to set the parent of pChild to NULL
		void remove (GameObject* pChild);

		virtual void setParent (GameObject* pGameObject);
		GameObject* getParent();

        int getChildCount();
        GameObject* getChildAt (int pIndex);

	protected:
		std::string _name;
		glm::mat4 _transform;

        GameObject* _parent;
		std::vector<GameObject*> _children;

        Mesh* _mesh;
		AbstractBehaviour* _behaviour;
		AbstractMaterial* _material;

        //update children list administration
        void _innerAdd (GameObject* pChild);
		void _innerRemove (GameObject* pChild);

    private:
        GameObject(const GameObject&);
        GameObject& operator=(const GameObject&);
};

#endif // GAMEOBJECT_H

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
protected:
    std::string m_name;
    glm::mat4   m_transform;

    GameObject* m_parent;
    std::vector<GameObject*> m_children;

    Mesh             * m_mesh;
    AbstractBehaviour* m_behaviour;
    AbstractMaterial * m_material;

public:
    explicit GameObject(std::string p_name = nullptr, glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f));

    virtual ~GameObject();

    void setName(std::string p_name);

    std::string getName() const;

    //contains local rotation, scale, position
    void setTransform(const glm::mat4& p_transform);

    const glm::mat4& getTransform() const;

    //access just the local position
    void setLocalPosition(glm::vec3 p_position);

    glm::vec3 getLocalPosition() const;

    //get the objects world position by combining transforms
    //expensive operations!! Improvement would be to cache these transforms!
    glm::vec3 getWorldPosition() const;

    glm::mat4 getWorldTransform() const;

    //change local position, rotation, scaling
    void translate(glm::vec3 p_translation);

    void rotate(float p_angle, glm::vec3 p_axis);

    void scale(glm::vec3 p_scale);

    //mesh and material should be shared as much as possible
    void setMesh(Mesh* p_mesh);

    Mesh* getMesh() const;

    void setMaterial(AbstractMaterial* p_material);

    AbstractMaterial* getMaterial() const;

    void setBehaviour(AbstractBehaviour* p_behaviour);

    AbstractBehaviour* getBehaviour() const;

    virtual void update(float p_step);

    //child management

    //shortcut to set the parent of pChild to ourselves
    void add(GameObject* p_child);

    //shortcut to set the parent of pChild to NULL
    void remove(GameObject* p_child);

    virtual void setParent(GameObject* p_parent);

    GameObject* getParent();

    int getChildCount();

    GameObject* getChildAt(int pIndex);

protected:
    //update children list administration
    void innerAdd(GameObject* p_child);

    void innerRemove(GameObject* p_child);

private:
    GameObject(const GameObject&);

    GameObject& operator=(const GameObject&);
};

#endif // GAMEOBJECT_H

#include <cassert>
#include <iostream>

#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

GameObject::GameObject(std::string p_name, glm::vec3 p_position)
        : m_name(p_name), m_transform(glm::translate(p_position)),
          m_parent(nullptr), m_children(), m_mesh(nullptr), m_behaviour(nullptr), m_material(nullptr)
{
}

GameObject::~GameObject()
{
    //detach all children
    std::cout << "GC running on:" << m_name << std::endl;

    while (!m_children.empty())
    {
        GameObject* child = m_children[0];
        remove(child);
        delete child;
    }

    //do not forget to delete behaviour, material, mesh, collider manually if required!
}

void GameObject::setName(std::string p_name)
{
    m_name = p_name;
}

std::string GameObject::getName() const
{
    return m_name;
}

void GameObject::setTransform(const glm::mat4& p_transform)
{
    m_transform = p_transform;
}

const glm::mat4& GameObject::getTransform() const
{
    return m_transform;
}

void GameObject::setLocalPosition(glm::vec3 p_position)
{
    m_transform[3] = glm::vec4(p_position, 1);
}

glm::vec3 GameObject::getLocalPosition() const
{
    return glm::vec3(m_transform[3]);
}

void GameObject::setMaterial(AbstractMaterial* p_material)
{
    m_material = p_material;
}

AbstractMaterial* GameObject::getMaterial() const
{
    return m_material;
}

void GameObject::setMesh(Mesh* p_mesh)
{
    m_mesh = p_mesh;
}

Mesh* GameObject::getMesh() const
{
    return m_mesh;
}

void GameObject::setBehaviour(AbstractBehaviour* p_behaviour)
{
    m_behaviour = p_behaviour;
    m_behaviour->setOwner(this);
}

AbstractBehaviour* GameObject::getBehaviour() const
{
    return m_behaviour;
}

void GameObject::setParent(GameObject* p_parent)
{
    //remove from previous parent
    if (m_parent != nullptr)
    {
        m_parent->innerRemove(this);
        m_parent = nullptr;
    }

    //set new parent
    if (p_parent != nullptr)
    {
        m_parent = p_parent;
        m_parent->innerAdd(this);
    }
}

GameObject* GameObject::getParent()
{
    return m_parent;
}

void GameObject::innerAdd(GameObject* p_child)
{
    //set new parent
    p_child->m_parent = this;
    m_children.push_back(p_child);
}

void GameObject::innerRemove(GameObject* p_child)
{
    for (auto i = m_children.begin(); i != m_children.end(); ++i)
    {
        if (*i == p_child)
        {
            (*i)->m_parent = nullptr;
            m_children.erase(i);
            return;
        }
    }
}

void GameObject::add(GameObject* p_child)
{
    p_child->setParent(this);
}

void GameObject::remove(GameObject* p_child)
{
    p_child->setParent(nullptr);
}

////////////

//costly operation, use with care
glm::vec3 GameObject::getWorldPosition() const
{
    return glm::vec3(getWorldTransform()[3]);
}

//costly operation, use with care
glm::mat4 GameObject::getWorldTransform() const
{
    if (m_parent == nullptr) return m_transform;
    else return m_parent->getWorldTransform() * m_transform;
}

////////////

void GameObject::translate(glm::vec3 p_translation)
{
    setTransform(glm::translate(m_transform, p_translation));
}

void GameObject::scale(glm::vec3 p_scale)
{
    setTransform(glm::scale(m_transform, p_scale));
}

void GameObject::rotate(float p_angle, glm::vec3 p_axis)
{
    setTransform(glm::rotate(m_transform, p_angle, p_axis));
}

//all game objects are updated in a backward loop, first the behaviour is updated, then all children are updated
void GameObject::update(float p_step)
{
    if (m_behaviour) m_behaviour->update(p_step);

    for (int i = static_cast<int>(m_children.size() - 1); i >= 0; --i)
    {
        m_children[i]->update(p_step);
    }
}

int GameObject::getChildCount()
{
    return static_cast<int>(m_children.size());
}

GameObject* GameObject::getChildAt(int pIndex)
{
    return m_children[pIndex];
}


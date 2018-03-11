#include <cassert>
#include <iostream>
#include "mge/behaviours/AbstractBehaviour.hpp"

AbstractBehaviour::AbstractBehaviour() : m_owner(nullptr)
{}

AbstractBehaviour::~AbstractBehaviour()
{
    m_owner = nullptr;
}

void AbstractBehaviour::setOwner(GameObject* p_gameObject)
{
    m_owner = p_gameObject;
}


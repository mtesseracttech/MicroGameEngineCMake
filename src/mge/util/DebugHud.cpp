#include <cassert>
#include <iostream>

using namespace std;

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"

DebugHud::DebugHud(sf::RenderWindow* p_window) : m_window(p_window), m_debugInfo(), m_font(), m_debugText()
{
    assert (m_window);

    if (!m_font.loadFromFile(config::MGE_FONT_PATH + "arial.ttf"))
    {
        cout << "Could not load font, exiting..." << endl;
        return;
    }

    createDebugHud();
}

DebugHud::~DebugHud()
{
    //dtor
}

void DebugHud::createDebugHud()
{
    m_debugText.setString("");
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(16);
    m_debugText.setFillColor(sf::Color::White);
}

void DebugHud::setDebugInfo(std::string p_info)
{
    m_debugText.setString(p_info);
    m_debugText.setPosition(10, 10);
}

void DebugHud::draw()
{
    //glDisable( GL_CULL_FACE );
    glActiveTexture(GL_TEXTURE0);
    m_window->pushGLStates();
    m_window->draw(m_debugText);
    m_window->popGLStates();
}

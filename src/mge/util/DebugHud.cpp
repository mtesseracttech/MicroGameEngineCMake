#include <cassert>
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"

DebugHud::DebugHud( sf::RenderWindow * aWindow ): _window( aWindow ), _debugInfo(), _font(), _debugText()
{
	assert ( _window != NULL );

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        cout << "Could not load font, exiting..." << endl;
        return;
    }

    _createDebugHud();
}

DebugHud::~DebugHud()
{
	//dtor
}

void DebugHud::_createDebugHud() {
    _debugText.setString("");
    _debugText.setFont(_font);
	_debugText.setCharacterSize(16);
	_debugText.setFillColor(sf::Color::White);
}

void DebugHud::setDebugInfo(std::string pInfo) {
    _debugText.setString(pInfo);
	_debugText.setPosition(10, 10);
}

void DebugHud::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(_debugText);
	_window->popGLStates();
}

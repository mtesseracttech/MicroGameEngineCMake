#ifndef DEBUGHUD_H
#define DEBUGHUD_H

#include <SFML/Graphics.hpp>
#include <iostream>

class DebugHud
{
private:
    sf::RenderWindow* m_window;
    sf::Font    m_font;
    sf::Text    m_debugText;
    std::string m_debugInfo;

public:
    
    DebugHud(sf::RenderWindow* p_window);

    virtual ~DebugHud();

    void draw();

    void setDebugInfo(std::string p_info);

private:

    void createDebugHud();

    DebugHud(const DebugHud&);

    DebugHud& operator=(const DebugHud&);
};

#endif // DEBUGHUD_H

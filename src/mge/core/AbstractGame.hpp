#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>

class World;

class Renderer;

/**
 * Defines the basic structure for a game, with defaults already filled in.
 * Your main game loop should run:
 *
 *  initialize
 *  run
 *
 * in order.
 */
class AbstractGame
{
protected:

    sf::RenderWindow* m_window;   //sfml window to render into
    Renderer        * m_renderer; //the renderer class to render the world
    World           * m_world;    //the root game object that represents our scene
    float m_fps;       //stores the real fps

public:

    AbstractGame();

    virtual ~AbstractGame();

    //creates a window, initializes glew, a renderer and a world instance
    virtual void initialize();

    //run the actual process of updating all objects, rendering them and processing events
    virtual void run();

protected:

    //methods above delegate behaviour to the methods below so that you can override it in a subclass
    //initialize sfml rendering context
    virtual void initializeWindow();

    //print info about the current driver version etc
    virtual void printVersionInfo();

    //initialize the extension wrangler
    virtual void initializeGlew();

    //create our own custom renderer instance
    virtual void initializeRenderer();

    //initialize a scene root to which we can attach/add objects
    virtual void initializeWorld();

    //initialize the actual scene, to be done by a subclass
    virtual void initializeScene() = 0;

    //call update on all game objects in the display root
    virtual void update(float p_step);

    //render all game objects in the display root
    virtual void render();

    //process any sfml window events (see SystemEventDispatcher/Listener)
    virtual void processEvents();

private:
    AbstractGame(const AbstractGame&);

    AbstractGame& operator=(const AbstractGame&);
};

#endif // ABSTRACTGAME_H

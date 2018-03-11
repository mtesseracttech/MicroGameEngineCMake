#include "AbstractGame.hpp"
#include <iostream>
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"

AbstractGame::AbstractGame() : m_window(NULL), m_renderer(NULL), m_world(NULL), m_fps(0)
{
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete m_window;
    delete m_renderer;
    delete m_world;
}

void AbstractGame::initialize()
{
    std::cout << "Initializing engine..." << std::endl << std::endl;
    initializeWindow();
    printVersionInfo();
    initializeGlew();
    initializeRenderer();
    initializeWorld();
    initializeScene();
    std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

///SETUP

void AbstractGame::initializeWindow()
{
    std::cout << "Initializing window..." << std::endl;
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game!", sf::Style::Default,
                                    sf::ContextSettings(24, 8, 0, 3, 3));
    //m_window->setVerticalSyncEnabled(true);
    std::cout << "Window initialized." << std::endl << std::endl;
}

void AbstractGame::printVersionInfo()
{
    std::cout << "Context info:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    //print some debug stats for whoever cares
    const GLubyte* renderer    = glGetString(GL_RENDERER);
    const GLubyte* vendor      = glGetString(GL_VENDOR);
    const GLubyte* version     = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::initializeGlew()
{
    std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
    std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl
              << std::endl;
}

void AbstractGame::initializeRenderer()
{
    //setup our own renderer
    std::cout << "Initializing renderer..." << std::endl;
    m_renderer = new Renderer();
    std::cout << "Renderer done." << std::endl << std::endl;
}

void AbstractGame::initializeWorld()
{
    //setup the world
    std::cout << "Initializing world..." << std::endl;
    m_world = new World();
    std::cout << "World initialized." << std::endl << std::endl;
}

///LOOP

void AbstractGame::run()
{
    sf::Clock updateClock;
    sf::Clock renderClock;
    sf::Time  timeSinceLastUpdate = sf::Time::Zero;
    sf::Time  timePerFrame        = sf::seconds(1.0f / 60.0f);


    while (m_window->isOpen())
    {
        timeSinceLastUpdate += updateClock.restart();

        if (timeSinceLastUpdate > timePerFrame)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            while (timeSinceLastUpdate > timePerFrame)
            {
                timeSinceLastUpdate -= timePerFrame;
                update(timePerFrame.asSeconds());
            }

            render();
            m_window->display();

            float timeSinceLastRender = renderClock.restart().asSeconds();
            if (timeSinceLastRender != 0) m_fps = 1.0f / timeSinceLastRender;
        }

        processEvents();
    }
}

void AbstractGame::update(float p_step)
{
    m_world->update(p_step);
}

void AbstractGame::render()
{
    m_renderer->render(m_world);
}

void AbstractGame::processEvents()
{
    sf::Event event;
    bool      exit = false;

    //we must empty the event queue
    while (m_window->pollEvent(event))
    {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you...
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type)
        {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    exit = true;
                }
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
    }

    if (exit)
    {
        m_window->close();
    }
}




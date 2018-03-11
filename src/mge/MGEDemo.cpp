#include <glm.hpp>
#include <iostream>
#include <string>

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into m_window, m_renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo() : AbstractGame(), m_hud(0)
{
}

void MGEDemo::initialize()
{
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
    std::cout << "Initializing HUD" << std::endl;
    m_hud = new DebugHud(m_window);
    std::cout << "HUD initialized." << std::endl;
}

//build the game m_world
void MGEDemo::initializeScene()
{
    m_renderer->setClearColor(0, 0, 0);

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    m_world->add(camera);
    m_world->setMainCamera(camera);

    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    //Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* suzannaMeshF     = Mesh::load(config::MGE_MODEL_PATH + "suzanna_flat.obj");
    Mesh* teapotMeshS      = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");

    //MATERIALS

    AbstractMaterial* colorMaterial    = new ColorMaterial(glm::vec3(0.2f, 0, 0.2f));
    AbstractMaterial* textureMaterial  = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
    AbstractMaterial* textureMaterial2 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));

    //SCENE SETUP

    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(textureMaterial);
    m_world->add(plane);

    GameObject* teapot = new GameObject("teapot", glm::vec3(-3, 1, 0));
    teapot->setMesh(teapotMeshS);
    teapot->setMaterial(textureMaterial2);
    teapot->setBehaviour(new KeysBehaviour());
    m_world->add(teapot);

    GameObject* monkey = new GameObject("monkey", glm::vec3(3, 1, 0));
    monkey->setMesh(suzannaMeshF);
    monkey->setMaterial(colorMaterial);
    monkey->setBehaviour(new RotatingBehaviour());
    m_world->add(monkey);

    camera->setBehaviour(new LookAt(teapot));
}

void MGEDemo::render()
{
    AbstractGame::render();
    updateHud();
}

void MGEDemo::updateHud()
{
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int) m_fps) + "\n";

    m_hud->setDebugInfo(debugInfo);
    m_hud->draw();
}

MGEDemo::~MGEDemo()
{
    //dtor
}

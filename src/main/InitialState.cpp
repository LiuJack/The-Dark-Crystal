#include "InitialState.h"

#include "ConfigurationManager.h"
#include "MenuState.h"
#include "QAManager.h"
#include "RecordManager.h"

#include <Graphics/DisplayManager.hpp>
#include <Core/ResourceManager.hpp>
#include <Scene/StateManager.hpp>
#include <Utils/Random.hpp>

#include <SFML/Audio/Listener.hpp>

InitialState::InitialState() {}

void InitialState::onInitialize() {
    RecordManager* record_mgr = RecordManager::get();
    record_mgr->initialize();

    QAManager* qa_mgr = QAManager::getInstance();
    qa_mgr->initialize();
    qa_mgr->loadQuestions("QA.xml");

    dt::Random::initialize();

    dt::ResourceManager::get()->addResourceLocation("", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("gui", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("gui/digits", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("images", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("musics", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("sounds", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("texts", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("models", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("scripts", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("videos", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("particles", "FileSystem");

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    dt::Scene::SceneSP scene = addScene(new dt::Scene("initial_scene"));
    
    auto camnode = scene->addChildNode(new dt::Node("camera"));
    camnode->addComponent(new dt::CameraComponent("camera_component"));

    ConfigurationManager* config_mgr = ConfigurationManager::getInstance();
    config_mgr->loadConfig();

    auto display_settings = config_mgr->getScreenSetting();
    auto sound_settings = config_mgr->getSoundSetting();

    dt::DisplayManager::get()->setWindowSize(1280, 800);

    if (display_settings.getFullScreen()) {
        dt::DisplayManager::get()->setFullscreen(true);
    }

    sf::Listener::setGlobalVolume(sound_settings.getMainVolume());
}

void InitialState::onDeinitialize() {}

void InitialState::updateStateFrame(double simulation_frame_time) {
    dt::StateManager::get()->setNewState(new MenuState());
}
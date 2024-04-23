#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include "display.h"
#include "raycaster.h"
#include "texturemanager.h"
#include "map.h"
#include "player.h"

class Engine
{
public:
    Engine();

    void Loop();

private:
    void Setup();
    void ProcessInput();
    void Update();
    void Render();

    bool m_isRunning = false;
    
    uint32_t m_previousFrameTime;
    float m_deltaTime;

    std::shared_ptr<Display> m_display;
    std::shared_ptr<Raycaster> m_raycaster;
    std::shared_ptr<TextureManager> m_textureManager;

    std::shared_ptr<Map> m_map;
    std::shared_ptr<Player> m_player;
};

#endif
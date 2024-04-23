#include "engine.h"
#include "defines.h"

Engine::Engine()
{
    m_display = std::make_shared<Display>(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_raycaster = std::make_shared<Raycaster>();
    m_textureManager = std::make_shared<TextureManager>();

    Setup();
    m_isRunning = true;
}

void Engine::Loop()
{
    while (m_isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Engine::Setup()
{
    m_map = std::make_shared<Map>();
    m_player = std::make_shared<Player>(400.0f, 300.0f);
}

void Engine::ProcessInput()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_CONTROLLERDEVICEADDED:
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                switch (event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        m_player->SetWalkDirection(WALK_FORWARD);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        m_player->SetWalkDirection(WALK_BACKWARD);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        m_player->SetTurnDirection(TURN_LEFT);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        m_player->SetTurnDirection(TURN_RIGHT);
                        break;
                }
                break;
            case SDL_CONTROLLERBUTTONUP:
                switch (event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        m_player->SetWalkDirection(WALK_NONE);
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        m_player->SetTurnDirection(TURN_NONE);
                        break;
                }
                break;
        }
    }
}

void Engine::Update()
{
    int32_t timeToWait = MILLISECS_PER_FRAME - SDL_GetTicks() - m_previousFrameTime;
    if (timeToWait > 0)
        SDL_Delay(timeToWait);
    
    m_deltaTime = (float) (SDL_GetTicks() - m_previousFrameTime) / 1000.0f;
    if (m_deltaTime > 0.016f)
        m_deltaTime = 0.016f;
    
    m_previousFrameTime = SDL_GetTicks();

    m_player->Move(m_deltaTime, m_map);
    m_raycaster->CastRays(m_player, m_map);
}

void Engine::Render()
{
    // Don't need to clear the screen, as we'll overwrite it all anyway
    m_raycaster->RenderWalls(m_display, m_player, m_textureManager);
    m_map->Render(m_display);
    m_raycaster->RenderRays(m_display, m_player);
    m_player->Render(m_display);

    m_display->RenderFrame();
}
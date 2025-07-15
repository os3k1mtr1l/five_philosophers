#include"header/game.h"
#include<rlImGui.h>

void Game::initResources(uint16_t config_width, uint16_t config_height)
{
    m_scene = LoadRenderTexture(config_width, config_height);
}

void Game::initGameAttributes()
{
    m_diningroom.Start();
}

Game::Game()
{
    ConfigManager::LoadConfig("config.json");
    const Config& cfg = ConfigManager::GetConfig();

    SetConfigFlags(cfg.fullscreen? FLAG_FULLSCREEN_MODE : 0);
    InitWindow(cfg.windowWidth, cfg.windowHeight, "Five philosophers");
    
    int monitor = GetCurrentMonitor();
    
    SetWindowMinSize(800, 600);
    SetWindowMaxSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    
    if(!cfg.fullscreen)
    {
        SetWindowPosition(
            GetMonitorWidth(monitor) / 2 - cfg.windowWidth / 2,
            GetMonitorHeight(monitor) / 2 - cfg.windowHeight / 2
        );
    }

    SetTargetFPS(cfg.fps);

    rlImGuiSetup(true);
    initResources(cfg.windowWidth, cfg.windowHeight);
    initGameAttributes();
}

Game::~Game()
{
    rlImGuiShutdown();
    UnloadRenderTexture(m_scene);
    CloseWindow();
}

void Game::Run()
{
    while(!WindowShouldClose())
    {
        update();
        draw();
    }
}
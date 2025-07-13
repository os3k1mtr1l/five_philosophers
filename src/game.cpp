#include"header/game.h"
#include<rlImGui.h>

void Game::initResources(uint16_t config_width, uint16_t config_height)
{
    m_scene = LoadRenderTexture(config_width, config_height);
}

void Game::initGameAttributes()
{
    
}

Game::Game()
{
    InitWindow(0, 0, "2D Template");
    ConfigManager::LoadConfig("config.json");

    int monitor = GetCurrentMonitor();
    uint16_t config_width = ConfigManager::GetConfig().windowWidth;
    uint16_t config_height = ConfigManager::GetConfig().windowHeight;
    
    SetWindowMinSize(800, 600);
    SetWindowMaxSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    
    SetWindowSize(config_width, config_height);

    SetWindowPosition(GetMonitorWidth(monitor) / 2 - config_width / 2, GetMonitorHeight(monitor) / 2 - config_height / 2);

    SetTargetFPS(ConfigManager::GetConfig().fps);

    rlImGuiSetup(true);
    initResources(config_width, config_height);
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
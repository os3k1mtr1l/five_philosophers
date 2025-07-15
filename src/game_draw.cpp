#include"header/game.h"
#include<imgui.h>
#include<rlImGui.h>

void Game::drawScene()
{
    BeginTextureMode(m_scene);
    {
        ClearBackground(WHITE);

        m_diningroom.Draw();
    }
    EndTextureMode();
}

void Game::composeFrame()
{
    BeginDrawing();
    rlImGuiBegin();
    {
        ClearBackground(BLACK);
        
        DrawTextureRec(
            m_scene.texture,
            {0, 0, static_cast<float>(m_scene.texture.width), static_cast<float>(-m_scene.texture.height)},
            {0, 0},
            WHITE);
    }
    rlImGuiEnd();
    EndDrawing();
}

void Game::draw()
{
    drawScene();
    
    composeFrame();
}
#pragma once
#include<raylib.h>
#include"config.h"
#include"dining_room.h"

class Game
{
    public:
        Game();
        ~Game();
        void Run();

    private:
        void initResources(uint16_t config_width, uint16_t config_height);
        void initGameAttributes();

        void update();
        void draw();

        void drawScene();
        void composeFrame();

        RenderTexture2D m_scene;
        DiningRoom m_diningroom;
};
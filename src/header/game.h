#pragma once
#include<raylib.h>
#include"config.h"

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
        void draw() const;

        void drawScene() const;
        void composeFrame() const;

        RenderTexture2D m_scene;
};
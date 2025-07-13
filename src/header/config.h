#pragma once
#include<cstdint>
#include<filesystem>

#pragma pack(push, 1)

struct Config
{
    uint16_t windowWidth;
    uint16_t windowHeight;
    uint8_t fps;
    bool fullscreen;
};

#pragma pack(pop)

class ConfigManager
{
    public:
        static void LoadConfig(const std::filesystem::path& path);
        static void LoadConfig();
        static void SaveConfig(const std::filesystem::path& path);
        static const Config& GetConfig();

    private:
        static Config s_config;
        static bool s_is_initialized;
};
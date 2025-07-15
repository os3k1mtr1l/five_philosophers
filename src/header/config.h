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

    uint8_t philosophers_count;
    uint64_t eating_phase_time_ms;
    uint64_t thinking_phase_time_ms;
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
#include"header/config.h"
#include<iostream>
#include<fstream>
#include<raylib.h>
#include<json.hpp>

using json = nlohmann::json;

Config ConfigManager::s_config{0};
bool ConfigManager::s_is_initialized = false;

void ConfigManager::LoadConfig()
{
    s_config.windowWidth = 800;
    s_config.windowHeight = 600;
    s_config.fps = 60;
    s_config.fullscreen = false;
    s_config.philosophers_count = 5;
    s_config.thinking_phase_time_ms = 1500;
    s_config.eating_phase_time_ms = 2500;

    s_is_initialized = true;
}

const Config& ConfigManager::GetConfig()
{
    return s_config;
}

void ConfigManager::SaveConfig(const std::filesystem::path& path)
{
    if(!s_is_initialized)
    {
        TraceLog(LOG_WARNING, "CONFIG: Config uninitialized. Operation discarded", path.string().c_str());
        return;
    }

    std::ofstream file(path);
    
    if(!file.is_open())
    {
        TraceLog(LOG_WARNING, "CONFIG: Failed to open file: %s. Operation discarded", path.string().c_str());
        return;
    }
    
    json j;
    j["window"]["width"]                        = s_config.windowWidth;
    j["window"]["height"]                       = s_config.windowHeight;
    j["window"]["fps"]                          = s_config.fps;
    j["window"]["fullscreen"]                   = s_config.fullscreen;
    j["philosophers"]["count"]                  = s_config.philosophers_count;
    j["philosophers"]["thinking_phase_time_ms"] = s_config.thinking_phase_time_ms;
    j["philosophers"]["eating_phase_time_ms"]   = s_config.eating_phase_time_ms;

    file << j.dump(4);
    
    TraceLog(LOG_INFO, "CONFIG: Saved");
    file.close();
}

void ConfigManager::LoadConfig(const std::filesystem::path& path)
{
    std::ifstream file(path);
    TraceLog(LOG_INFO, "CONFIG: Loading config from: %s",
                path.string().c_str()
            );
    LoadConfig();
    
    if(!file.is_open())
    {
        TraceLog(LOG_WARNING, "CONFIG: Failed to open file: %s. Loading default settings",
                    path.string().c_str()
                );
        SaveConfig(path);
    }
    else
    {
        json j;
        file >> j;
        
        s_config.windowWidth              = j["window"].value("width", s_config.windowWidth);
        s_config.windowHeight             = j["window"].value("height", s_config.windowHeight);
        s_config.fps                      = j["window"].value("fps", s_config.fps);
        s_config.fullscreen               = j["window"].value("fullscreen", s_config.fullscreen);
        s_config.philosophers_count       = j["philosophers"].value("count", s_config.philosophers_count);        
        s_config.thinking_phase_time_ms   = j["philosophers"].value("thinking_phase_time_ms", s_config.thinking_phase_time_ms);        
        s_config.eating_phase_time_ms     = j["philosophers"].value("eating_phase_time_ms", s_config.eating_phase_time_ms);        
    }
    
    TraceLog(
        LOG_INFO, "CONFIG: Loaded config:\n" \
        "\tWIDTH: %d\n"\
        "\tHEIGHT: %d\n"\
        "\tFPS: %d\n"\
        "\tFULLSCREEN: %s\n"\
        "\tPHILOSOPHERS_COUNT: %d\n"\
        "\tTHINKING TIME MS: %d\n"\
        "\tEATING TIME MS: %d"\
        ,
        s_config.windowWidth,
        s_config.windowHeight,
        s_config.fps,
        s_config.fullscreen? "true" : "false",
        s_config.philosophers_count,
        s_config.thinking_phase_time_ms,
        s_config.eating_phase_time_ms
    );
    file.close();
}
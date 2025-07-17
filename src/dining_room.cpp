#include"header/dining_room.h"
#include"header/config.h"
#include<math.h>

using namespace std::chrono_literals;

const Color philosopher_color[] = {
    WHITE,
    BLUE,
    RED,
    GREEN
};

void DiningRoom::thread_sleep(uint64_t ms)
{
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::milliseconds(ms);

    while (m_running && std::chrono::steady_clock::now() < end_time)
    {
        std::this_thread::sleep_for(1ms);
    }
}

void DiningRoom::ft_philosophers(int id)
{
    uint8_t philosophers_count = ConfigManager::GetConfig().philosophers_count;
    uint64_t eating_ms = ConfigManager::GetConfig().eating_phase_time_ms;
    uint64_t thinking_ms = ConfigManager::GetConfig().thinking_phase_time_ms;

	while (m_running)
	{
        m_mio.lock();
        m_philosophers[id].state = PhilosopherState::THINKING;
        m_mio.unlock();
        
        thread_sleep(thinking_ms);
        
        m_mio.lock();
        m_philosophers[id].state = PhilosopherState::HUNGRY;
        m_mio.unlock();
        
        size_t left = id;
        size_t right = (id + 1) % philosophers_count;
        
        if (id == philosophers_count - 1)
        {
            m_forks[right]->lock();
            thread_sleep(20);
            m_forks[left]->lock();
        }
        else
        {
            m_forks[left]->lock();
            thread_sleep(20);
            m_forks[right]->lock();
        }
        
        m_mio.lock();
        m_philosophers[id].state = PhilosopherState::EATING;
        m_mio.unlock();
        
        thread_sleep(eating_ms);
        
        m_mio.lock();
        m_philosophers[id].state = PhilosopherState::NOTHING;
        m_mio.unlock();
        
        m_forks[left]->unlock();
        m_forks[right]->unlock();
	}
}

void DiningRoom::Start()
{
    uint8_t philosophers_count = ConfigManager::GetConfig().philosophers_count;
    
    m_forks.reserve(philosophers_count);
    for(int i = 0; i < philosophers_count; i++)
        m_forks.emplace_back(std::make_unique<std::mutex>());
    m_philosophers.reserve(philosophers_count);

    m_main_radius = (ConfigManager::GetConfig().windowHeight / 2.0f) - 100.0f;

    m_length = 2 * PI * m_main_radius;
    m_distance = m_length / philosophers_count;
    m_sub_radius = m_main_radius / 10;
    m_degree = 360.0f / philosophers_count;

    for (int i = 0; i < philosophers_count; i++)
    {
        m_philosophers.emplace_back(Philosopher{
            .self = std::thread(&DiningRoom::ft_philosophers, this, i),
            .state = PhilosopherState::NOTHING
        });
    }
}

void DiningRoom::Draw()
{
    std::lock_guard<std::mutex> mio(m_mio);

    Vector2 center{ ConfigManager::GetConfig().windowWidth / 2.0f,
                    ConfigManager::GetConfig().windowHeight / 2.0f };

    DrawCircleLinesV(center, m_main_radius, BLACK);

    for (int i = 0; i < ConfigManager::GetConfig().philosophers_count; i++)
    {
        Vector2 new_point{0, 0};
        float rad = m_degree * i * DEG2RAD;
        new_point.x = center.x + m_main_radius * cos(rad);
        new_point.y = center.y + m_main_radius * sin(rad);

        DrawCircleV(new_point, m_sub_radius, philosopher_color[(int)m_philosophers[i].state]);
        DrawCircleLinesV(new_point, m_sub_radius, BLACK);
        DrawText(
            TextFormat("%s", state_names[(int)m_philosophers[i].state]),
            new_point.x + m_sub_radius,
            new_point.y + m_sub_radius,
            8,
            BLACK
        );
    }
}

void DiningRoom::Update()
{
    std::lock_guard<std::mutex> mio(m_mio);
    m_running = !WindowShouldClose();
}

DiningRoom::~DiningRoom()
{
    m_running = false;
	for (Philosopher& philosopher : m_philosophers)
    {
        if (philosopher.self.joinable())
        {
            philosopher.self.join();
        }
    }
}
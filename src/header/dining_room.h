#pragma once
#include<raylib.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<semaphore>
#include<vector>
#include<atomic>
#include<memory>

enum class PhilosopherState
{
	NOTHING,
	THINKING,
	HUNGRY,
	EATING
};

inline const char* state_names[] = {
	"Nothing",
	"Thinking",
	"Hungry",
	"Eating"
};

struct Philosopher
{
	std::thread self;
	PhilosopherState state;
};

class DiningRoom
{
	public:
		~DiningRoom();

		void Start();
		void Draw();
		void Update();

	private:
		void ft_philosophers(int id);
		void thread_sleep(uint64_t ms);

		std::atomic_bool m_running;

		std::mutex m_mio;
		std::vector<std::unique_ptr<std::mutex>> m_forks;
		std::vector<Philosopher> m_philosophers;

		float m_main_radius;

		float m_length;
		float m_distance;
		float m_sub_radius;
		float m_degree;
};
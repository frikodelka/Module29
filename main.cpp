// Module_29_Yurkina_Marya
#include <chrono>
#include <thread>
#include <ctime>
#include <random>
#include <vector>
#include "FineGrainedQueue.h"

int main()
{
	srand(time(nullptr));

	FineGrainedQueue queue;
	std::vector<std::thread> threads;

	for (int i = 0; i < 100; ++i)
	{
		threads.push_back(std::thread([&queue, &i]() {std::this_thread::sleep_for(std::chrono::seconds (3)); queue.insertIntoMiddle(i, i); }));
	}

	for (size_t i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	printQueue(queue);

	return 0;
}
// Module_29_Yurkina_Marya
#pragma once
#include <mutex>

class FineGrainedQueue;
void printQueue(FineGrainedQueue&);

struct Node
{
	int value;
	Node* next;
	std::mutex node_mutex;
};

class FineGrainedQueue
{
private:
	Node* head;
	std::mutex queue_mutex;

public:
	FineGrainedQueue();
	FineGrainedQueue(FineGrainedQueue&) = delete;
	FineGrainedQueue(FineGrainedQueue&&) = delete;
	~FineGrainedQueue();

	void insertIntoMiddle(int value, int pos);

	FineGrainedQueue& operator=(FineGrainedQueue&) = delete;
	FineGrainedQueue& operator=(FineGrainedQueue&&) = delete;

	friend void printQueue(FineGrainedQueue&);
};

// Module_29_Yurkina_Marya
#include <iostream>
#include <mutex>
#include "FineGrainedQueue.h"

void printQueue(FineGrainedQueue& queue)
{
	Node* node = queue.head;

	while (node)
	{

		std::cout << node->value << " ";
		node = node->next;

		if (node)
		{
			std::cout << "\t";
		}
	}

	std::cout << std::endl;
}

FineGrainedQueue::FineGrainedQueue() : head(nullptr)
{
}

FineGrainedQueue::~FineGrainedQueue()
{
	Node* node = head;

	while (node)
	{
		Node* next = node->next;
		delete node;
		node = next;
	}
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
	Node* node = new Node();
	node->value = value;
	node->next = nullptr;

	Node* current_node = nullptr;
	size_t current_pos = 0;

	queue_mutex.lock();
	if (!head)
	{
		head = node;
	}
	else if (!pos)
	{
		head->node_mutex.lock();
		node->next = head;
		head = node;
		head->next->node_mutex.unlock();
	}
	else
	{
		head->node_mutex.lock();
		current_node = head;
	}
	queue_mutex.unlock();

	while (current_node && current_pos < pos)
	{
		++current_pos;
		Node* next_node = current_node->next;
		if (next_node)
		{
			next_node->node_mutex.lock();
		}

		if (current_pos == pos || !next_node)
		{
			node->node_mutex.lock();
			current_node->next = node;
			node->next = next_node;
			node->node_mutex.unlock();

			if (next_node)
			{
				next_node->node_mutex.unlock();
			}
		}

		current_node->node_mutex.unlock();
		current_node = next_node;
	}
}
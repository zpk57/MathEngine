#pragma once

#include <queue>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>

// Class provides thread pool with one FIFO queue for threads set.
class ThreadPool
{
public:	
	class IThreadEvent
	{
	public:
		virtual ~IThreadEvent() = default;
		virtual void execute() = 0;
	};
	
public:	
	ThreadPool();
	~ThreadPool();
	
	int start(size_t threads);
	
	int stop();
	
	int addEvent(IThreadEvent* event);

private:	
	IThreadEvent* getEvent();
	
	bool canSleep();
	
	void threadFunction();
	
private:
	std::queue<IThreadEvent*> m_queue;
	std::mutex m_mutex;
	
	std::condition_variable	 m_cv;
	bool m_stopped;
	
	std::vector<std::thread> m_threads;
};
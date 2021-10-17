   
#include "ThreadPool.h"
#include <iostream>


ThreadPool::ThreadPool() : 
	m_stopped( false )
{}

ThreadPool::~ThreadPool()
{
	stop();
}

int ThreadPool::start(size_t threads)
{
	m_threads.reserve(threads);
	for (size_t i = 0; i < threads; ++i) {
		m_threads.emplace_back(&ThreadPool::threadFunction, this);
	}
	return 0;
}

int ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> ul(m_mutex);
		if (m_stopped) {
			return 0;
		}
		m_stopped = true;
	}
	m_cv.notify_all();
	
	for (auto &thread : m_threads) {
		thread.join();
	}

	m_threads.clear();

	return 0;
}

int ThreadPool::addEvent(ThreadPool::IThreadEvent* event)
{
	{
		std::unique_lock<std::mutex> ul(m_mutex);
		m_queue.push(event);
	}
	m_cv.notify_one();
	return 0;
}

ThreadPool::IThreadEvent* ThreadPool::getEvent()
{
	if (0 == m_queue.size()) {
		return nullptr;
	}
	IThreadEvent* retval = m_queue.front();
	m_queue.pop();
	return retval;
}

bool ThreadPool::canSleep()
{
	return m_queue.empty() && !m_stopped;
}

void ThreadPool::threadFunction()
{
	while (true) {
		IThreadEvent* event;
		{
			std::unique_lock<std::mutex> ul(m_mutex);
			m_cv.wait(ul, [&](){ return !canSleep(); });
			
			if (m_stopped) {
				return;
			}
			
			event = getEvent();
		}
		
		if (nullptr == event) {
			continue;
		}
		
		event->execute();
		delete event;
	}
}
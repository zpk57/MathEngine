#pragma once

#include "../Scheduling/ThreadPool.h"
#include "../Data/Definitions.h"
#include <future>
#include <functional>

// CalculationContext provides task scheduling.
// Provides threads scheduling, can accept new tasks, etc.
// Designed to use at calculation process,
// e.g. when some algorithm decides to split his task for other thread, etc.
// Also may be configured from outside for special task.

using WorkEvent = std::function<void(CalculationContext&)>;

class CalculationContext
{
public:
	CalculationContext(const DocumentPtr& doc);

public:
	// Main run and sync method.
	void calculate(size_t threads);

	// Work scheduling.
	void schedule(WorkEvent&& work);

	const DocumentPtr& document() const;

private:
	class WorkPoolEvent;
	friend class WorkPoolEvent;

	void onPoolEventFinish();

private:
	DocumentPtr		   m_doc;
	ThreadPool		   m_threadPool;
	std::atomic_size_t m_inProgress;
	std::promise<void> m_promise;
};

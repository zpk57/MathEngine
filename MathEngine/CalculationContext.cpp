#include "CalculationContext.h"


class CalculationContext::WorkPoolEvent : public ThreadPool::IThreadEvent
{
public:
	WorkPoolEvent(CalculationContext& context, WorkEvent&& work)
		: m_context(context)
		, m_work(std::move(work))
	{
	}

	void execute() override
	{
		m_work(m_context);

		m_context.onPoolEventFinish();
	}

private:
	CalculationContext& m_context;
	WorkEvent m_work;
};


CalculationContext::CalculationContext(const DocumentPtr& doc)
	: m_doc(doc)
{
}

void CalculationContext::schedule(WorkEvent && work)
{
	++m_inProgress;

	m_threadPool.addEvent(new WorkPoolEvent(*this, std::move(work)));
}

void CalculationContext::calculate(size_t threads)
{
	m_threadPool.start(threads);

	m_promise.get_future().wait();

	m_threadPool.stop();
}

void CalculationContext::onPoolEventFinish()
{
	if (--m_inProgress == 0)
		m_promise.set_value();
}

const DocumentPtr& CalculationContext::document() const
{
	return m_doc;
}

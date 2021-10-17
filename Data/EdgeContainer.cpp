
#include "EdgeContainer.h"
#include "Cell.h"


const EdgeContainer::Container& EdgeContainer::raw() const
{
	return m_content;
}

void EdgeContainer::add(const CellPtr& item)
{
	//m_content[item->name()] = std::make_unique<Edge>(item);

	m_content.push_back(std::make_unique<Edge>(item));
}

bool EdgeContainer::addUnique(const CellPtr& item)
{
	for (const auto& itemEx : m_content)
		if (itemEx->cell() == item)
			return false;

	add(item);

	return true;
}

bool EdgeContainer::remove(const CellPtr& item)
{
	//m_content.erase(item->name());

	for (auto& itemEx : m_content)
	{
		if (itemEx->cell() == item)
		{
			std::swap(m_content.back(), itemEx);
			m_content.pop_back();
			return true;
		}
	}

	return false;
}

void EdgeContainer::clear()
{
	m_content.clear();
}

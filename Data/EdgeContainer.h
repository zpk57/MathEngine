#pragma once

#include "Definitions.h"
#include "Edge.h"
#include <unordered_map>

// Container to retain Cells relations.
class EdgeContainer
{
	//using Container = std::unordered_map<std::string, EdgePtr>;
	using Container = std::vector<EdgePtr>;
public:
	const Container& raw() const;

	void add      (const CellPtr& item);
	bool addUnique(const CellPtr& item);
	bool remove   (const CellPtr& item);
	void clear    ();

private:
	Container m_content;
};

template<typename Iterator>
inline const EdgePtr& rawEdge(Iterator&& it)
{
	//return it.second;
	return it;
}

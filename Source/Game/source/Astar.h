//#pragma once
//#include <queue> 
//#include <utility> 
//#include <memory>
//#include <unordered_map>
//#include <Vector2.h>
////#include "Grid.h"
//
//class Grid;
//enum class NodeTile;
//
//template<typename T, typename prioratyT>
//struct PriorityQueue
//{
//	typedef std::pair<prioratyT, T> PQElement;
//	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement >> elements;
//
//	inline bool Empty() const
//	{
//		return elements.empty();
//	}
//
//	inline void Put(T aItem, prioratyT aPriority)
//	{
//		elements.emplace(aItem, aPriority);
//	}
//
//	T Get()
//	{
//		T bestItem = elements.top().second;
//		elements.pop();
//		return bestItem;
//	}
//};
//
//class Astar
//{
//public:
//
//	Astar() = default;
//	~Astar() = default;
//
//	template<typename Location>
//	void AstarPath(Grid* aGrid, Location aStart, Location aGoal,
//		std::unordered_map<Location, Location>& aPreviusSerch,
//		std::unordered_map<Location, float>& aCostSoFar);
//	float Heuristic(CommonUtilities::Vector2<float> aPosOne, CommonUtilities::Vector2<float> aPosTwo);
//private:
//
//};


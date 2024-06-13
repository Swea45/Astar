#pragma once
#include "Grid.h"
#include <queue> 
#include <utility> 
#include <memory>
#include <unordered_map>
#include <Vector2.h>

class SpriteLoader;

template<typename T, typename prioratyT>
struct PriorityQueue
{
	typedef std::pair<prioratyT, T> PQElement; 

	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool Empty() const
	{
		return elements.empty();
	}

	inline void Put(T aItem, prioratyT aPriority)
	{

		elements.emplace(aPriority, aItem);
	}

	T Get()
	{
		T bestItem = elements.top().second;
		elements.pop();
		return bestItem;
	}
};

class Astar
{
public:

	Astar() = default;
	~Astar() = default;

	template<typename Location>
	void AstarPath(Grid* aGrid, Location aStart, Location aGoal,
		std::unordered_map<Location, Location>& aPreviusSerch,
		std::unordered_map<Location, float>& aCostSoFar, SpriteLoader* aSpriteLoader);
	
	template<typename Location>
	bool SlowStartAstarPath(Grid* aGrid, Location aStart, Location aGoal,
		std::unordered_map<Location, Location>& aPreviusSerch,
		std::unordered_map<Location, float>& aCostSoFar, 
		SpriteLoader* aSpriteLoader);

	template<typename Location>
	std::vector<Location> RecreatePath(Location aStart, Location aGoal,
		std::unordered_map< Location, Location> aPathSearched);

	float Heuristic(CommonUtilities::Vector2<float> aPosOne, CommonUtilities::Vector2<float> aPosTwo);
	template<typename Location>
	void DrawPath(std::vector<Location> aPath, Grid* aGrid, SpriteLoader* aSpriteLoader);
private:

	template<typename Location>
	float Cost(CommonUtilities::Vector2<float> aGridPos, std::unordered_map<Location, Location>& aPreviusSerch);
	template<typename Location, typename T, typename prioratyT>
	bool SlowAstarPath(Grid* aGrid, Location aGoal,
		std::unordered_map<Location, Location>& aPreviusSerch,
		std::unordered_map<Location, float>& aCostSoFar, SpriteLoader* aSpriteLoader, PriorityQueue<T, prioratyT>& aQueue);
};

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Render();
	template<typename Location>
	void Search();
private:
	Astar myAstar;
	Grid myGrid;
	SpriteLoader* mySpriteLoader;

	bool mySlowSerching = false;
};
//#include "Astar.h"
//
//template<typename Location>
//void Astar::AstarPath(Grid* aGrid, Location aStart, Location aGoal,
//	std::unordered_map<Location, Location>& aPreviusSerch, 
//	std::unordered_map<Location, float>& aCostSoFar) 
//{
//	PriorityQueue<Location, Location> frontier; 
//	frontier.Put(aStart, 0); 
//
//	aPreviusSerch[aStart] = aStart; 
//	aCostSoFar[aStart] = 0; 
//
//	while (!frontier.Empty())
//	{
//		Location current = frontier.Get(); 
//
//		if (current == aGoal)
//		{
//			std::cout << "Found path";
//			break;
//		}
//
//		for (Location next : aGrid->Neighbors(current)) 
//		{
//			float cost = aCostSoFar[current];// +aGrid->Cost(current, next); //add Cost to gird
//			if (aCostSoFar.find(next) == aCostSoFar.end() || cost < aCostSoFar[next])
//			{
//				aCostSoFar[next] = cost;
//				float priority = cost + Heuristic(next, aGoal);
//				frontier.Put(next, priority);
//				aPreviusSerch[next] = current; 
//			}
//		}
//	}
//
//}
//
//float Astar::Heuristic(CommonUtilities::Vector2<float> aPosOne, CommonUtilities::Vector2<float> aPosTwo)
//{
//	return std::abs(aPosOne.x - aPosTwo.x) + std::abs(aPosOne.y - aPosTwo.y);
//}

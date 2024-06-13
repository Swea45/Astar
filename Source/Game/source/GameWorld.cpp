#include "stdafx.h"
#include "GameWorld.h"
#include "spriteloader.h"
#include "CommonUtilities/includes/Input.h"
#include "Astar.h"
#include "imgui/imgui.h"
#include "Node.h"

extern CommonUtilities::Input inputManager;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld() 
{
}

void GameWorld::Init()  
{
	mySpriteLoader = new SpriteLoader;
	mySpriteLoader->Init(*Tga::Engine::GetInstance());
	
	mySpriteLoader->AddSharedData(L"Sprites/PlayerNode.DDS"); 
	mySpriteLoader->AddSharedData(L"Sprites/GoalNode.DDS"); 
	mySpriteLoader->AddSharedData(L"Sprites/OpenNode.DDS");
	mySpriteLoader->AddSharedData(L"Sprites/BlockNode.DDS");
	mySpriteLoader->AddSharedData(L"Sprites/SearchedNode.DDS");
	mySpriteLoader->AddSharedData(L"Sprites/PathNode.DDS");

	
	myGrid.Init(30, mySpriteLoader); 
}

void GameWorld::Update(float aTimeDelta)
{
	aTimeDelta;
	myGrid.Update(mySpriteLoader);
	if (ImGui::Begin("Astar"))
	{
		if (ImGui::Button("Find path", ImVec2(150, 30)))
		{
			Search<CommonUtilities::Vector2<float>>(); 
		}
		if (ImGui::Button("Slow serch", ImVec2(150, 30)))
		{
			mySlowSerching = true;
		}
		ImGui::End();
	}

	if (mySlowSerching)
	{
		static std::unordered_map<CommonUtilities::Vector2<float>, CommonUtilities::Vector2<float>> priviusPos;
		static std::unordered_map<CommonUtilities::Vector2<float>, float> costSoFar;
		if (myAstar.SlowStartAstarPath(&myGrid, myGrid.GetStart(), myGrid.GetGoal(), priviusPos, costSoFar, mySpriteLoader))
		{

			std::vector<CommonUtilities::Vector2<float>> path = myAstar.RecreatePath(myGrid.GetStart(), myGrid.GetGoal(), priviusPos); 
			myAstar.DrawPath(path, &myGrid, mySpriteLoader); 
			
			
			mySlowSerching = false;
			priviusPos.clear();
			costSoFar.clear();
		}
	}
}

void GameWorld::Render()
{
	myGrid.Render();
}



template<typename Location>
void GameWorld::Search() 
{
	std::unordered_map<Location, Location> priviusPos;
	std::unordered_map<Location, float> costSoFar;
	
	Astar astar;
	astar.AstarPath(&myGrid, myGrid.GetStart(), myGrid.GetGoal(), priviusPos, costSoFar, mySpriteLoader);

	std::vector<Location> path = astar.RecreatePath(myGrid.GetStart(), myGrid.GetGoal(), priviusPos);
	astar.DrawPath(path, &myGrid, mySpriteLoader);

} 


template<typename Location>
void Astar::AstarPath(Grid* aGrid, Location aStart, Location aGoal,
	std::unordered_map<Location, Location>& aPreviusSerch,
	std::unordered_map<Location, float>& aCostSoFar, SpriteLoader* aSpriteLoader) 
{
	PriorityQueue<Location, float> frontier;
	frontier.Put(aStart, 0);

	aPreviusSerch[aStart] = aStart;
	aCostSoFar[aStart] = 0;

	while (!frontier.Empty())
	{
		Location current = frontier.Get();
		aGrid->GetNodeAtGridPos(current).SetType(aSpriteLoader->GetSprite(4), NodeTile::Serched);

		if (current == aGoal)
		{
			std::cout << "Found path";
			break;
		}
	
		for (Location next : aGrid->Neighbors(current))
		{
			float cost = aCostSoFar[current] + Cost(next, aPreviusSerch); 
			cost;
			if (aCostSoFar.find(next) == aCostSoFar.end() || cost < aCostSoFar[next]) 
			{
				aCostSoFar[next] = cost;
				float priority = cost + Heuristic(next, aGoal);
				frontier.Put(next, priority);
				aPreviusSerch[next] = current;
			}
		}
	}

}

template<typename Location>
bool Astar::SlowStartAstarPath(Grid* aGrid, Location aStart, Location aGoal, 
	std::unordered_map<Location, Location>& aPreviusSerch, 
	std::unordered_map<Location, float>& aCostSoFar, SpriteLoader* aSpriteLoader)
{
	static bool started = false;
	static PriorityQueue<Location, float> frontier;
	if (!started)
	{
		frontier.Put(aStart, 0);

		aPreviusSerch[aStart] = aStart;
		aCostSoFar[aStart] = 0;
		started = true;
	}

	if (SlowAstarPath(aGrid, aGoal, aPreviusSerch, aCostSoFar, aSpriteLoader, frontier))
	{
		started = false;
		return true;
	}
	return false;
}

template<typename Location>
std::vector<Location> Astar::RecreatePath(Location aStart, Location aGoal, std::unordered_map<Location, Location> aPathSearched)
{
	std::vector<Location> path;
	Location current = aGoal;
	if (aPathSearched.find(aGoal) == aPathSearched.end())
	{
		std::cout << "No path found" << std::endl;
		return path;
	}
	while (current != aStart)
	{
		path.push_back(current);
		current = aPathSearched[current];
	}
	path.push_back(aStart);
	std::reverse(path.begin(), path.end());
	return path;
}

template<typename Location>
void Astar::DrawPath(std::vector<Location> aPath, Grid* aGrid, SpriteLoader* aSpriteLoader)
{
	for (int i = 0; i < aPath.size(); i++)
	{
		aGrid->GetNodeAtGridPos(aPath[i]).SetType(aSpriteLoader->GetSprite(5), NodeTile::Path);
	}
}

template<typename Location>
float Astar::Cost(CommonUtilities::Vector2<float> aGridPos, std::unordered_map<Location, Location>& aPreviusSerch)
{
	float cost = aPreviusSerch.find(aGridPos) != aPreviusSerch.end() ? 5.0f : 1.0f;
	return cost;
}

template<typename Location, typename T, typename prioratyT>
bool Astar::SlowAstarPath(Grid* aGrid, Location aGoal, 
	std::unordered_map<Location, Location>& aPreviusSerch, 
	std::unordered_map<Location, float>& aCostSoFar, 
	SpriteLoader* aSpriteLoader, PriorityQueue<T, prioratyT>& aQueue)
{
	if (aQueue.Empty())
	{
		return true;
	}
	Location current = aQueue.Get(); 
	aGrid->GetNodeAtGridPos(current).SetType(aSpriteLoader->GetSprite(4), NodeTile::Serched);

	if (current == aGoal)
	{
		std::cout << "Found path";
		return true;
	}

	for (Location next : aGrid->Neighbors(current))
	{
		float cost = aCostSoFar[current] + Cost(next, aPreviusSerch);
		if (aCostSoFar.find(next) == aCostSoFar.end() || cost < aCostSoFar[next])
		{
			aCostSoFar[next] = cost;
			float priority = cost + Heuristic(next, aGoal);
			aQueue.Put(next, priority);
			aPreviusSerch[next] = current;
		}
	}
	return false;
}

float Astar::Heuristic(CommonUtilities::Vector2<float> aPosOne, CommonUtilities::Vector2<float> aPosTwo)
{
	return std::abs(aPosOne.x - aPosTwo.x) + std::abs(aPosOne.y - aPosTwo.y);
}
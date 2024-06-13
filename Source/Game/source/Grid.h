#pragma once
#include <vector>
#include <array>
#include "Vector2.h"

class Node;
class SpriteLoader;
enum class NodeTile;


class Grid
{
public:
	Grid();
	~Grid();

	void Init(int aSize, SpriteLoader* aSpriteLoader);
	void Update(SpriteLoader* aSpriteLoader);
	void Render();

	CommonUtilities::Vector2<float> GetNodeGridPos(int aNr);
	CommonUtilities::Vector2<float> ScreenToGridPos(CommonUtilities::Vector2<float> aPos);
	Node& GetNodeAtGridPos(CommonUtilities::Vector2<float> aGridPos); 
	int GetNodeNr(CommonUtilities::Vector2<float> aPosition); 

	CommonUtilities::Vector2<float> GetStart();
	CommonUtilities::Vector2<float> GetGoal();
	
	std::vector<CommonUtilities::Vector2<float>> Neighbors(CommonUtilities::Vector2<float> aGridPos);

private:

	void CreateGrid(SpriteLoader* aSpriteLoader); 

	bool InBounds(CommonUtilities::Vector2<float> aGridPos);  
	bool Passable(CommonUtilities::Vector2<float> aGridPos);  
	
	std::vector<Node*> myNodes;
	std::array<CommonUtilities::Vector2<float>, 4> myDirs; 
	int myTileIndex;

	NodeTile myTiles[5];
	float myNodeSize = 25;
	int mySize = 0;

	CommonUtilities::Vector2<float> myPlayerPos; 
	CommonUtilities::Vector2<float> myGoalPos; 

};


#pragma once
#include "Vector2.h" 
#include "CollisionBox2D.h"

enum class NodeTile
{
	Player,
	Goal,
	Open,
	Closed,
	Serched,
	Path,
	size
};

namespace Tga
{
	struct Sprite2DInstanceData;
	struct SpriteSharedData;
	class SpriteDrawer;
}

class Node
{
public:
	Node(Tga::SpriteSharedData* aSharedData, CommonUtilities::Vector2<float> aPosition);
	~Node();

	void Init(); 
	void Update();
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void SetType(Tga::SpriteSharedData* aSharedData, NodeTile aNodeTile);
	CommonUtilities::Vector2<float> GetPosition();
	CollisionBox2D* GetCollisionBox();
	NodeTile GetNodeType();

private:
	CommonUtilities::Vector2<float> myPosition;
	Tga::Sprite2DInstanceData* mySpriteInstans;
	Tga::SpriteSharedData* mySharedData;
	CollisionBox2D myCollisionBox;
	NodeTile myNodeTile;
};


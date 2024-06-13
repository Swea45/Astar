#include "Node.h"
#include <tge/engine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>

Node::Node(Tga::SpriteSharedData* aSharedData, CommonUtilities::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySharedData = aSharedData; 
	mySpriteInstans = new Tga::Sprite2DInstanceData();

	mySpriteInstans->myPosition = { aPosition.x, aPosition.y };
	mySpriteInstans->myPivot = { 0.5f, 0.5f };
	mySpriteInstans->mySize = mySharedData->myTexture->CalculateTextureSize();  
	mySpriteInstans->myColor = { 1, 1, 1, 1 };

	myCollisionBox.SetCorner(
		{ mySpriteInstans->mySize.x * -0.5f, mySpriteInstans->mySize.y * -0.5f }, 
		{ mySpriteInstans->mySize.x * 0.5f, mySpriteInstans->mySize.y * 0.5f });
	myNodeTile = NodeTile::Open;
}

Node::~Node()
{
	mySpriteInstans = nullptr;
	mySharedData = nullptr;
}

void Node::Init()
{
}

void Node::Update()
{

}

void Node::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	//Tga::SpriteBatchScope batch = aSpriteDrawer.BeginBatch(*mySharedData);  
	aSpriteDrawer.Draw(*mySharedData, *mySpriteInstans);
	//batch.Draw(*mySpriteInstans);
}

void Node::SetType(Tga::SpriteSharedData* aSharedData, NodeTile aNodeTile)
{
	myNodeTile = aNodeTile;
	mySharedData = aSharedData;
}

CommonUtilities::Vector2<float> Node::GetPosition() 
{
	return myPosition;
}

CollisionBox2D* Node::GetCollisionBox()
{
	return &myCollisionBox;
}

NodeTile Node::GetNodeType()
{
	return myNodeTile;
}

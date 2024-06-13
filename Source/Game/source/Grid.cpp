#include "Grid.h"
#include "Node.h"
#include "spriteloader.h"
#include "tge/engine.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include "imgui/imgui.h"
#include "CommonUtilities/includes/Input.h"
#include "Windows.h"
#include "unordered_map"

extern CommonUtilities::Input inputManager;

Grid::Grid()
{
	myTiles[0] = NodeTile::Player;
	myTiles[1] = NodeTile::Goal;
	myTiles[2] = NodeTile::Open;
	myTiles[3] = NodeTile::Closed;
	myTiles[4] = NodeTile::Serched;
	myDirs = { CommonUtilities::Vector2<float>{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
}

Grid::~Grid()
{
}

void Grid::Init(int aSize, SpriteLoader* aSpriteLoader) 
{
	mySize = aSize;
	myTileIndex = 0;
	CreateGrid(aSpriteLoader);
}

void Grid::Update(SpriteLoader* aSpriteLoader)
{
	if (ImGui::Begin("Selct Tile"))
	{
		if (ImGui::Button("Player Tile", ImVec2(75, 30)))
		{
			myTileIndex = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Goal Tile", ImVec2(75, 30)))
		{
			myTileIndex = 1;
		}

		if (ImGui::Button("Open Tile", ImVec2(75, 30)))
		{
			myTileIndex = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button("Closed Tile", ImVec2(75, 30)))
		{
			myTileIndex = 3;
		}
		if (ImGui::Button("Clear board", ImVec2(150, 30)))
		{
			for (int i = 0; i < myNodes.size(); i++)
			{
				myNodes[i]->SetType(aSpriteLoader->GetSprite(2), NodeTile::Open);
			}
		}

		if (ImGui::TreeNode("Slider"))
		{
			ImGui::SliderInt("Tile ID: ", &myTileIndex, 0, 4);
			ImGui::TreePop();
		}
		ImGui::End();  
	}


	CommonUtilities::Vector2<float> mousePos = { (float)inputManager.GetMousePosision().x, (float)inputManager.GetMousePosision().y };
	CommonUtilities::Vector2<float> mousePosFix = { mousePos.x, 900.0f - mousePos.y }; 
	for (int i = 0; i < myNodes.size(); i++)
	{
		if (myNodes[i]->GetCollisionBox()->CollisionWithPoint(myNodes[i]->GetPosition(), mousePosFix)) 
		{
			if (inputManager.GetKeyPressed(0x01))
			{

				if (myTileIndex == (int)NodeTile::Player)				
				{
					myNodes[GetNodeNr(myPlayerPos)]->SetType(aSpriteLoader->GetSprite((int)NodeTile::Open), myTiles[(int)NodeTile::Open]);
					myPlayerPos = myNodes[i]->GetPosition() - CommonUtilities::Vector2<float>{ myNodeSize, myNodeSize };
				}
				else if (myTileIndex == (int)NodeTile::Goal)
				{
					myNodes[GetNodeNr(myGoalPos)]->SetType(aSpriteLoader->GetSprite((int)NodeTile::Open), myTiles[(int)NodeTile::Open]);
					myGoalPos = myNodes[i]->GetPosition() - CommonUtilities::Vector2<float>{ myNodeSize, myNodeSize };
				}
				myNodes[i]->SetType(aSpriteLoader->GetSprite(myTileIndex), myTiles[myTileIndex]);

				std::cout << "X: " << GetNodeGridPos(i).x << " Y: " << GetNodeGridPos(i).y << " I: " << i << " Nr: " 
					<< GetNodeNr(myNodes[i]->GetPosition() - CommonUtilities::Vector2<float>{ myNodeSize, myNodeSize }) << "\n";

			}
		}
	}
}

void Grid::Render()
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
	for (int i = 0; i < myNodes.size(); i++)
	{
		myNodes[i]->Render(spriteDrawer);
	}
}

CommonUtilities::Vector2<float> Grid::GetNodeGridPos(int aNr)
{
	return (myNodes[aNr]->GetPosition() - CommonUtilities::Vector2<float>{myNodeSize, myNodeSize}) / myNodeSize; 
}

CommonUtilities::Vector2<float> Grid::ScreenToGridPos(CommonUtilities::Vector2<float> aPos)
{
	int x = (int)floor((aPos.x) / myNodeSize);
	int y = (int)floor((aPos.y) / myNodeSize);
	return { (float)x, (float)y };
}

Node& Grid::GetNodeAtGridPos(CommonUtilities::Vector2<float> aGridPos) 
{
	return *myNodes[(int)aGridPos.y + ((int)aGridPos.x * mySize)];
}

int Grid::GetNodeNr(CommonUtilities::Vector2<float> aPosition)
{
	int nodeX = (int)floor(aPosition.x / myNodeSize);
	int nodeY = (int)floor(aPosition.y / myNodeSize);

	return nodeY + (nodeX * mySize);
}

CommonUtilities::Vector2<float> Grid::GetStart()
{
	return ScreenToGridPos(myPlayerPos);
}

CommonUtilities::Vector2<float> Grid::GetGoal()
{
	return ScreenToGridPos(myGoalPos);
}

void Grid::CreateGrid(SpriteLoader* aSpriteLoader)
{
	for (int x = 0; x < mySize; x++)
	{
		for (int y = 0; y < mySize; y++)
		{
			Node* node = new Node(aSpriteLoader->GetSprite(2), { x * myNodeSize + myNodeSize, y * myNodeSize + myNodeSize }); 
			myNodes.push_back(node);
		}
	}
}

bool Grid::InBounds(CommonUtilities::Vector2<float> aGridPos)
{
	return 0 <= aGridPos.x && aGridPos.x < mySize &&
		0 <= aGridPos.y && aGridPos.y < mySize;
}

bool Grid::Passable(CommonUtilities::Vector2<float> aGridPos)
{
	return (GetNodeAtGridPos(aGridPos).GetNodeType() != NodeTile::Closed);
}

std::vector <CommonUtilities::Vector2<float>> Grid::Neighbors(CommonUtilities::Vector2<float> aGridPos)
{
	std::vector<CommonUtilities::Vector2<float>> result;
	for (CommonUtilities::Vector2<float> dir : myDirs)
	{
		CommonUtilities::Vector2<float> next{ aGridPos.x + dir.x, aGridPos.y + dir.y };
		if (InBounds(next) && Passable(next))
		{
			result.push_back(next);
		}
	}

	if ((int)(aGridPos.x + aGridPos.y) % 2 == 0) 
	{
		std::reverse(result.begin(), result.end());
	}

	return result;
}

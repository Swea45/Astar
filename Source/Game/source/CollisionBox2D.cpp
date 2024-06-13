#include "CollisionBox2D.h"

CollisionBox2D::CollisionBox2D()
{
}

CollisionBox2D::~CollisionBox2D()
{
}

bool CollisionBox2D::CollisionWithPoint(CommonUtilities::Vector2<float> aPosition, CommonUtilities::Vector2<float> aPositionToCheck)
{
	return aPositionToCheck.x >= aPosition.x + myBotCornerSize.x &&  aPositionToCheck.x <= aPosition.x + myTopCornerSize.x  &&
		aPositionToCheck.y >= aPosition.y + myBotCornerSize.y && aPositionToCheck.y <= aPosition.y + myTopCornerSize.y;
}

void CollisionBox2D::SetCorner(CommonUtilities::Vector2<float> aBotCorner, CommonUtilities::Vector2<float> aTopCorner) 
{
	myTopCornerSize = aTopCorner;
	myBotCornerSize = aBotCorner;
}

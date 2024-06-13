#pragma once
#include "Vector2.h" 
class CollisionBox2D
{
public:
	CollisionBox2D();
	~CollisionBox2D();

	bool CollisionWithPoint(CommonUtilities::Vector2<float> aPosition, CommonUtilities::Vector2<float> aPositionToCheck);
	void SetCorner(CommonUtilities::Vector2<float> aBotCorner, CommonUtilities::Vector2<float> aTopCorner);

private:
	CommonUtilities::Vector2<float> myTopCornerSize; 
	CommonUtilities::Vector2<float> myBotCornerSize;

};


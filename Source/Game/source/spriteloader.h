#pragma once
#include <vector>
#include <cwchar>
namespace Tga
{
	struct SpriteSharedData;
	class Engine;
}

class SpriteLoader
{
public:
	SpriteLoader();
	~SpriteLoader();

	void AddSharedData(wchar_t* aAddres);
	void Init(Tga::Engine& aEngine);
	Tga::SpriteSharedData* GetSprite(int aColorID);
private:
	std::vector<Tga::SpriteSharedData*> mySharedData;
	Tga::Engine* myEngine;

};


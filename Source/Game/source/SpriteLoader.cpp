
#include "spriteloader.h"
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/engine.h>

SpriteLoader::SpriteLoader()
{
}

SpriteLoader::~SpriteLoader()
{
	for (int i = 0; i < mySharedData.size(); i++)
	{
		delete mySharedData[i];
		mySharedData[i] = nullptr;
	}
	mySharedData.clear();
	myEngine = nullptr;
}

void SpriteLoader::AddSharedData(wchar_t* aAddres)
{
	Tga::SpriteSharedData* sharedData = new Tga::SpriteSharedData();
	sharedData->myTexture = myEngine->GetTextureManager().GetTexture(aAddres);
	mySharedData.push_back(sharedData);
}

void SpriteLoader::Init(Tga::Engine& aEngine)
{
	myEngine = &aEngine;
}

Tga::SpriteSharedData* SpriteLoader::GetSprite(int aColorID)
{
	return mySharedData[aColorID];
}

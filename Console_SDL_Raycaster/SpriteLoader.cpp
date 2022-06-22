#include "SpriteLoader.h"

SpriteLoader* SpriteLoader::SpriteLoaderPtr;

SpriteLoader::SpriteLoader()
{
#if !_PS4
	int flag = IMG_INIT_PNG;
	int initted = IMG_Init(flag);
	if ((initted & flag) != flag)
	{
		printf("Oh no, PNG Failed. Big F \n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}
#else
	//PS4 image library init here
#endif

	SpriteLoaderPtr = this;
	LoadSprite();
}

SpriteLoader::~SpriteLoader()
{
	//Delete every loaded sprite
	for (Sprite* i : SpriteList)
	{
#if !_PS4
		SDL_DestroyTexture(static_cast<SDL_Texture*>(i->Image));
#else
		//PS4 sprite deletion code here
#endif

		i->Image = nullptr;
	}
	SpriteList.clear();

	//Clean up
#if !_PS4
	IMG_Quit();
#else
	//Close PS4 image stuff here
#endif

}

//Load sprite from address
Sprite* SpriteLoader::LoadSprite(std::string address, std::string SName, bool sheet)
{
	//If sprite already exists, return it
	for (Sprite* i : SpriteList)
	{
		if (i->Address == address)
		{
			printf("Sprite Already Loaded");
			return i;
		}
	}

	int Width = 0;
	int Height = 0;

	//Load image
#if !_PS4
	SDL_Surface* tempSurf = IMG_Load(address.c_str());
	if (!tempSurf)
	{
		printf("%s\n", SDL_GetError());
		return nullptr;
	}
	Width = tempSurf->w;
	Height = tempSurf->h;

#else
	//PS4 SPRITE LOAD CODE HERE
#endif
	//Create Sprite
	Sprite* newBoi = new Sprite;

	//Set values
	newBoi->Address = address;
	newBoi->Name = SName;
	newBoi->SpriteHeight = Height;

	//If spritesheet, do sheet calculations. EACH SPRITE MUST BE SQUARED. Eg: 256 x 128 = two sprites.
	if (sheet)
	{
		float spriteNumber = Width / Height;
		//Is width valid?
		if (Width == Height * spriteNumber)
		{
			if (spriteNumber == 1)
			{
				printf("Tried to load spritesheet, but only 1 sprite was found. Loading as regular sprite. \n");
				newBoi->Spritesheet = false;
				newBoi->SpriteWidth = Width;
			}
			else
			{
				printf("SpriteSheet Loaded Successfully \n");
				newBoi->SpriteWidth = newBoi->SpriteHeight;
				newBoi->NumberOfSprites = spriteNumber;
				newBoi->Spritesheet = true;
			}
		}
		else
		{
			printf("Spritesheet load failed. Loading as regular sprite. \n");
			newBoi->Spritesheet = false;
			newBoi->SpriteWidth = Width;
		}
	}
	else
	{
		printf("Sprite loaded successfully as regular sprite. \n");
		newBoi->SpriteWidth = Width;
	}

	//Add to list
	SpriteList.push_back(newBoi);


	//Create texture and clean up
#if !_PS4
	newBoi->Image = SDL_CreateTextureFromSurface(Renderer_SDL::RendererSDLPtr->GetRendererPtr(), tempSurf);
	SDL_FreeSurface(tempSurf);
#else
	//PS4 SPRITE LOAD CLEANUP HERE
#endif
	return newBoi;
}


Sprite* SpriteLoader::GetSprite(std::string textureToGet, bool IsAddress)
{
	if (IsAddress)
	{
		for (Sprite* i : SpriteList)
		{
			if (i->Address == textureToGet)
			{
				return i;
			}
		}
	}
	else
	{
		for (Sprite* i : SpriteList)
		{
			if (i->Name == textureToGet)
			{
				return i;
			}
		}
	}

	printf("Texture Not found");
	return nullptr;
}

#pragma once
#include "Sprite.h"
class SpriteNode
{
public:
	SpriteNode(void);
	~SpriteNode(void);

	 

	Sprite getSprite();
	void setSprite(Sprite sprite);
	
private:

	//set the sprite
	Sprite sprite;
	SpriteNode tailNode; //referrs to the address of the next Sprite Node
	
};


#pragma once
#include "Sprite.h";
#include "SpriteNode.h";

class SpriteLinkedList
{
public:
	SpriteLinkedList(void);
	~SpriteLinkedList(void);

	Sprite getSprite();
	void nextSprite(); 
	void addSprite(Sprite sprite);
	

private:
	SpriteNode firstSpriteNode;
	SpriteNode thisSpriteNode;
	SpriteNode lastSpriteNode;	
};




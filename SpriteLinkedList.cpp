#include "SpriteLinkedList.h"
SpriteLinkedList::SpriteLinkedList(void)
{
}
SpriteLinkedList::~SpriteLinkedList(void)
{
} 

SpriteLinkedList::SpriteLinkedList(Sprite sprite)
{
	firstSpriteNode = new SpriteNode;
	firstSpriteNode.sprite = this.sprite;
	thisSpriteNode = firstSpriteNode;
	lastSpriteNode = firstSpriteNode;
}

Sprite SpriteLinkedList::getSprite()
{
	return this->thisSpriteNode.sprite;
}

void SpriteLinkedList::nextSprite()
{
	if (thisSpriteNode.tailNode.sprite == null)
	{
		thisSpriteNode = firstSpriteNode;
	}
	else
		this->thisSpriteNode = this->thisSpriteNode.tailNode;
}

void SpriteLinkedList::addSprite(Sprite newSprite)
{
	SpriteNode sprite1 = new SpriteNode;
	sprite1.sprite = newSprite;
	lastSpriteNode.tailNode = sprite1;
	lastSpriteNode = lastSpriteNode.tailNode;
}
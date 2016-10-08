#ifndef _H_CHARACTERS_H_
#define _H_CHARACTERS_H_
#include"cocos2d.h"
using namespace cocos2d;
class HCharactersManagerBase;
class HCharactersBase:public CCSprite
{
public:
	
	
	static HCharactersBase* create()
	{
		HCharactersBase* pRet = new HCharactersBase();
    if (pRet != NULL)
    {
        pRet->autorelease();
		pRet->textureSpriteFrame=CCArray::create();
		pRet->textureSpriteFrame->retain();
		pRet->walkUp=CCArray::create();
		pRet->walkUp->retain();
		pRet->walkDown=CCArray::create();
		pRet->walkDown->retain();
		pRet->walkLeft=CCArray::create();
		pRet->walkLeft->retain();
		pRet->walkRight=CCArray::create();
		pRet->walkRight->retain();

    }
    return pRet;
	}

	//
	void setWalkUp(CCArray*walkUpArg)
	{
		walkUp=walkUpArg;
	}

	CCArray* getWalkUp()
	{
		return walkUp;
	}

	void setWalkDown(CCArray*walkDownArg)
	{
		walkDown=walkDownArg;
	}
	
	CCArray* getWalkDown()
	{
		return walkDown;
	}

	void setWalkLeft(CCArray*walkLeftArg)
	{
		walkLeft=walkLeftArg;
	}

	CCArray* getWalkLeft()
	{
		return walkLeft;
	}

	void gsetWalkRight(CCArray*walkRightArg)
	{
		walkRight=walkRightArg;
	}

	CCArray* getWalkRight()
	{
		return walkRight;
	}
	void setHTexture(CCTexture2D*hTextureArg)
	{
		hTexture=hTextureArg;
	}
	
protected:
	 CCTexture2D* hTexture;

	 CCArray * textureSpriteFrame;
    
	 CCArray *walkUp;
	 CCArray *walkDown;
	 CCArray *walkLeft;
	 CCArray*walkRight;
};


















#endif //_H_CHARACTERS_H_
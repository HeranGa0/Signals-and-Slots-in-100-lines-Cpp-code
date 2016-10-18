#ifndef __H_CHARACTERS_H__
#define __H_CHARACTERS_H__
#include"cocos2d.h"

using namespace cocos2d;

class HCharactersBase:public CCSprite
{
public:
	
	static HCharactersBase* create()
	{
		HCharactersBase* pRet = new HCharactersBase();
		if (pRet != NULL&&pRet->init())
     {
        pRet->autorelease();
		return pRet;
		
	 }
		else
	 {
		delete pRet;
		pRet=NULL;
		return NULL;
	 }
	}

	 virtual bool init(void);

	/*static HCharactersBase* create(std::string cPath)
	{
		HCharactersBase* pRet = new HCharactersBase();
    if (pRet != NULL)
    {
        pRet->autorelease();
		pRet->characPath=CCString::create(cPath);
		pRet->characPath->autorelease();
    }
    return pRet;
	}*/

	void setCPath(std::string cPath);

	CCString getCPath();

	void addImageUsingTextureCache(const char *cPath);

	CCArray* insertTextureSpriteFrames(float width,float height,int row,int column);

	void setInitialTexture();

	CCArray* obtainDirection(int num);
	
	

protected:
    int directionCal(CCPoint currentPos, CCPoint targetPos);
	CCTexture2D*texture;
	
	CCString *characPath;

	

	CCArray * TextureSpriteFrame;


	CCArray *walkUp;
	CCArray *walkDown;
	CCArray *walkLeft;
	CCArray*walkRight;

};



class MainCharacter: public HCharactersBase
{
public:
	static MainCharacter* create()
	{
		MainCharacter* pRet = new MainCharacter();
		
		if (pRet != NULL&&pRet->init())
        {
           pRet->autorelease();
		   return pRet;
	
        }
		else
		{
			delete pRet;
			pRet=NULL;
			return NULL;

		}

   
	}

	virtual bool init(void);
	CCActionInterval* walkingAnimation(CCPoint clickPoint, CCPoint currentPoint,int groupNum);

	void stopForConversation(HCharactersBase*target,CCSprite*textBox);
	
private:
	enum Direction
	{up=0,down,left,right};
	CCArray*reciever;
	
	


};


class NPC:public HCharactersBase
{
public:
	virtual bool init(void);
	//(CCSprite*NPC,CCPoint tLeft,CCPoint tRight,CCPoint bRight,CCPoint bLeft);
	 bool setNPCMovement(std::vector<CCPoint> posGroup);
		
	/*void stopAction(CCNode*NPC1)
	{
		//(CCSprite*)NPC1->stopAllActions();
		CCSprite*NPCReceiver= reinterpret_cast<CCSprite*>(NPC1);
		NPCReceiver->stopAllActions();
	}*/
	//void clickOnNPC(CCSprite*mainCharacter);
	 CREATE_FUNC(NPC);

    CCArray* textGroup;
	void setTextIntoBox(CCSprite*textBox);
	void setTextContentByArray(CCArray* content );
	void setTextOffBox(CCSprite*textBox);
	bool ifAndSetBoxStatus();
	int count;
	int scale;
	bool _ifBoxOn;
	bool _ifOnConversation;
	void ifSetConversationOn(bool On);
	bool iSConservationOn();
private:
	
	

};












#endif //__H_CHARACTERS_H__
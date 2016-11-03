#ifndef __H_CHARACTORS_H__
#define __H_CHARACTORS_H__
#include"cocos2d.h"
#include"HNPCTexts.h"
using namespace cocos2d;

/***********************************************************
Warning: 
Most of the functions or methods are not perfect currently,which need many corrections.
Their existence is to work properly and simply during the testing period.
警告：
大多数函数和方法目前都不是完美的，在后期将会大改动，
他们目前存在的原因是因为在前期能比较简单的测试
************************************************************/

//class HCharactorBase, which serves as the base class of all Charactors subclasses.
class HCharactorsBase:public CCSprite
{
public:
	
	//two segments create method Seg1:
	static HCharactorsBase* create()
	{
		HCharactorsBase* pRet = new HCharactorsBase();
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

	//two segments create method Seg2:
	virtual bool init(void);

	//At present it is useless, need more supplementaries
	//此函数目前禁用，待补充
	void setCPath(std::string cPath);

	//At present it is useless, need more supplementaries
	//此函数目前禁用，待补充
	CCString getCPath();

	//Currently the following 3 functions are the only way to insert image into Charactors. The picture should be the assembly of a set of movement.
	//下面的三个函数是目前唯一添加人物图片的方法，使用的图片应为一系列动作图片的集合
	/*Example to insert piction:
	NPC1=NPC::create(new Maid());
	NPC1->addImageUsingTextureCache("maid.png");
	NPC1->insertTextureSpriteFrames(32,48,4,4);
	NPC1->setInitialTexture();*/
	
	//Function1: addImage by picture path
	void addImageUsingTextureCache(const char *cPath);

	//Function2: insert textureSriteFrames by manually setting the arguments of spaces among subpictures
	//手动设置子图片间的距离
	CCArray* insertTextureSpriteFrames(float width,float height,int row,int column);

	//Function3: set initial (or static) picture for the Charactor
	//手动设置人物的静止时的图片
	void setInitialTexture();

	
	
	
protected:
	//There are four arrays each includes a set of walking items on one direction
	//下面是4个数组，每个数组都涵盖了在某个方向上行走的一些列图片帧
	CCArray *walkUp;
	CCArray *walkDown;
	CCArray *walkLeft;
	CCArray*walkRight;

	// obtain the direction the Charactor should go, while 1,2,3,4 represent down,left,right,up: down=1,left=2,right=3,up=4
    int directionCal(CCPoint currentPos, CCPoint targetPos);

	// using the num for direction to require the corresponding array, still down=1,left=2,right=3,up=4
	CCArray*sendDirectionArray(int num);

	// texture2D for the static picture of the Charactor
	CCTexture2D*texture;

	//useless currently
	CCString *characPath;

	//array includes total TextureSpriteFrames
	CCArray * TextureSpriteFrame;
	
	
private:
	
};


// class for main Charactor
class MainCharactor: public HCharactorsBase
{
public:
	static MainCharactor* create()
	{
		MainCharactor* pRet = new MainCharactor();
		
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
	// Insert the walking animation to the Charactor. 
	CCActionInterval* walkingAnimation(CCPoint clickPoint, CCPoint currentPoint);

	//only call when the Charactor stops to conduct a conversation.
	void stopForConversation(HCharactorsBase*target);
	
private:
	enum Direction
	{up=0,down,left,right};
	CCArray*reciever;
};


class NPC:public HCharactorsBase
{
public:
	
	virtual bool init(trial*NPCobj);

	static NPC* create(trial*name)
	{
		NPC* pRet = new NPC();
		
		if (pRet != NULL&&pRet->init(name))
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

	//This function enables the NPC to move automatically according to the points set you send to them.
	//这个函数能使NPC自动沿着你给的点集合移动，类似于口袋妖怪中的NPC
	 bool setNPCMovement(CCPoint a,...);
	
	// the following six functions are to conduct the dialog box and dialog texts Warning：this function is incomplete, where bugs exist
	//以下的六个函数处理对话框和对话文字，此功能尚不完善，有bug
	void setTextIntoBox();
	void setTextContentByArray();
	void setTextOffBox();
	void ifSetConversationOn(bool On);
	bool iSConservationOn();
	bool ifAndSetBoxStatus();

	CCArray* textGroup;
	int count;
	int scale;
	bool _ifBoxOn;
	bool _ifOnConversation;
	CCLabelTTF * NPCnameLabel;
	CCSprite*textBox;

	~NPC()
	{
		CCSprite::~CCSprite();
		delete H_delete;
	}
private:
	trial* H_delete;
};












#endif //__H_CHARACTORS_H__
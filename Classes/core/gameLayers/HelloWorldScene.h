#ifndef __HELLOWORLD_SCENE_H2__
#define __HELLOWORLD_SCENE_H2__

#include "cocos2d.h"
#include"HCharactors.h"
#include"HMaps.h"
#include"HTexts.h"
class HelloWorld2 : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
    //create macro
    CREATE_FUNC(HelloWorld2);

	//calls when layer is entering
	virtual void onEnter();

	//calls when layer is exsting
	virtual void onExit();

	//calss when clicking
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	//juege if main Charactor hit the obstacles
	void judgeIfHitObstacles();

	//calls when mian Charactor finishes actions
	void actionFinished()
	{
		mainCharactor->stopActionByTag(01);
		this->unschedule(SEL_SCHEDULE(&HelloWorld2::myUpdate));
	}

	//after clicking tothe screen, this function is called to condect mainCharactor's actions
	void createCMovingAction(CCPoint currentPos,CCPoint targetPos);

	//Charactors stop to do conversations
	void stopForConversation();
	
	//Always keep the main Charactor on the central of the screen. Cautions: Layer is moving when not touching the edges,then main Charactor starts to move.
	//总是把主人公放在屏幕中心，再未达到边缘时是layer在移动，达到边缘后改为主人公移动
	CCPoint setViewPosition(CCPoint viewPos);
	CCPoint view;
	CCArray *qiu;

private:
	
	MainCharactor*mainCharactor;
	TmxLayer* map1;
	NPC*NPC1;
	HMenuManager* hMenuManager;
	float saveX;
	float saveY;
	float cSpeed;
	void myUpdate(float m);
	CCPoint remove;
	
};

#endif // __HELLOWORLD_SCENE_H2__

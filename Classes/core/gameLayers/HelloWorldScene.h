#ifndef __HELLOWORLD_SCENE_H2__
#define __HELLOWORLD_SCENE_H2__

#include "cocos2d.h"
#include"HCharacters.h"
#include"HMaps.h"

class HelloWorld2 : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld2);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	void judgeIfHitObstacles();

	void actionFinished()
	{
		mainCharacter->stopActionByTag(01);
		this->unschedule(SEL_SCHEDULE(&HelloWorld2::myUpdate));
	}

	void createCMovingAction(CCPoint currentPos,CCPoint targetPos);
	void stopForConversation();
	///!!!
	CCPoint setViewPosition(CCPoint viewPos);
	CCPoint view;
	CCArray *qiu;

private:
	
	MainCharacter*mainCharacter;
	TmxLayer* map1;
	NPC*NPC1;
	float saveX;
	float saveY;
	float cSpeed;
	void myUpdate(float m);
};

#endif // __HELLOWORLD_SCENE_H2__

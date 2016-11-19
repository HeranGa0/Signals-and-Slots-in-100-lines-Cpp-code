#include "HelloWorldScene.h"
#include "AppMacros.h"


USING_NS_CC;


Scene* HelloWorld::scene()
{
	
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	view = Vec2(0, 0);

    mainCharactor = MainCharactor::create("CharactorList.png", 32, 48, 4, 3);
	mainCharactor->setPosition(Vec2(200, 200));
	this->addChild(mainCharactor, 2, 999);
	
    auto npc = NPC::create("maid.png", 32, 48, 4, 4);
	npc->setNPCMovement(Vec2(250, 250), Vec2(300, 250), Vec2(300, 200), Vec2(250, 250));
	npc->setPosition(Vec2(250, 250));
	this->addChild(npc, 5);

    mapManager = HTMXManager::create("livingRoom.tmx");
	mapManager->setAntiAliasforMapChildren();
	mapManager->addObstacles("Shelters");
	mapManager->retain();
	auto map = mapManager->getMap();
	addChild(map, 0, 998);

    auto eglView = Director::getInstance()->getOpenGLView();
	mH = mapManager->getMapHeight() - eglView->getFrameSize().height;
	mW = mapManager->getMapWidth() - eglView->getFrameSize().width;

	mainCharactor->setObsForCharac(mapManager->getObstacles());

	this->setlUpdateOn(true);

    auto singleTouch = EventListenerTouchOneByOne::create();
	singleTouch->onTouchBegan = [this](Touch* touch, Event  *event)->bool
	{
		mainCharactor->stopAllActions();
		auto clickPos = touch->getLocationInView();//»ñµÃ´¥ÃþÎ»ÖÃ
		clickPos = Director::getInstance()->convertToGL(clickPos);
		Vec2 fixedClickPos = clickPos - view;
		mainCharactor->createWalkingAction(fixedClickPos, mainCharactor->getPosition());
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(singleTouch, this);
    return true;
}

Vec2 HelloWorld::setViewPosition(Vec2 screenCenter)
{   
	Vec2 playerPos = Vec2(mainCharactor->getPosition());
	
	float placementX = screenCenter.x - playerPos.x;
	float placementY = screenCenter.y - playerPos.y;
	
	Vec2 final;
	
	if (mH>0 && mW>0)
	{
		if (placementY >= -mH&&placementY <= 0) {
			if (placementX >= -mW&&placementX <= 0) {

			}
			else {
				placementX = placementX>0 ? 0 : (-mW);
			}
		}
		else if (placementX >= -mW && placementX <= 0) {
			placementY = placementY>0 ? 0 : (-mH);
		}
	}

	 
	else if (mH>0 && mW <= 0)
	{
		if (placementY<-mH || placementY>0) {
			placementY = placementY>0 ? 0 : (-mH);
		}
		placementX = 0;
	}

    else
	{
		placementX = 0;
		placementY = 0;
	}
	final = Vec2(placementX, placementY);
	this->setPosition(final);
	view = final;
	return final;

}

void HelloWorld::menuCloseCallback(Ref* sender)
{
	
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

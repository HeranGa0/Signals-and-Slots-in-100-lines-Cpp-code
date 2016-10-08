#include "HelloWorldScene.h"
#define H_ABSOLUTE(x)\
if((x)<=0) x=-x


USING_NS_CC;

CCScene* HelloWorld2::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld2 *layer = HelloWorld2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	//this->setPosition(50,100);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	map1=TmxLayer::create();
	//map1->retain();
	map1->retain();
	int uy=1; int iu=-1;
	H_ABSOLUTE(uy);
	H_ABSOLUTE(iu);
	
	map1->setMapPath("trial2.tmx");  
	CCTMXTiledMap*map=map1->getMap();
	addChild(map,0,998);  
	map->setPosition(0,0);
	map1->setAntiAliasforMapChildren();
	CCTMXLayer*layer=map->layerNamed("background");
	//!!!!!!!!!
	
	map1->addObstacles("Shelters"); 

	mainCharacter=MainCharacter::create();
	//mainCharacter->retain();

	//mainCharacter->retain();
	//!!!!!!!!!!!!!!!!!!!!!!!!
	mainCharacter->addImageUsingTextureCache("trial1_MainCharac.png");
	
	CCArray*spritesA= mainCharacter->insertTextureSpriteFrames(32,48,4,3);
	
	//mainCharacter= CCSprite::createWithSpriteFrame((CCSpriteFrame*)(spritesA->objectAtIndex(0)));
	mainCharacter->setInitialTexture();
	
	mainCharacter->setPosition(ccp(200,200));
	map->setScale(1.0f);
	//mainCharacter->setScale(1.0f);
	this->addChild(mainCharacter,2,999);
	
	NPC1=NPC::create();
	//NPC1->retain();
	NPC1->addImageUsingTextureCache("maid.png");
	NPC1->insertTextureSpriteFrames(32,48,4,4);
	NPC1->setInitialTexture();
	//NPC1=CCSprite::createWithSpriteFrame((CCSpriteFrame*)(ANPC->objectAtIndex(0)));
	NPC1->setPosition(ccp(250,250));
	addChild(NPC1,3,888);
	std::vector<CCPoint> points(8);
	points[0]=ccp(250,250);
	points[1]=ccp(300,250);
	points[2]=ccp(300,200);
	points[3]=ccp(250,200);
	points[4]=ccp(250,100);
	points[5]=ccp(400,100);
	points[6]=ccp(400,250);
	points[7]=ccp(100,250);

	NPC1->setNPCMovement(points);
		//ccp(250,250),ccp(300,250),ccp(300,200),ccp(250,200));
   
    
    return true;
}

void HelloWorld2::onEnter()
{
	  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);  
    CCLayer::onEnter();  

}
void HelloWorld2::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
bool HelloWorld2::ccTouchBegan(CCTouch*touch,CCEvent*event)
{
	if((touch->getLocation().getDistance(NPC1->getPosition()))<=40)
	{
		mainCharacter->stopForConversation(NPC1);
		return false;
	}
	CCPoint t=touch->getLocation();
	unschedule(SEL_SCHEDULE(&HelloWorld2::myUpdate));
	 schedule(SEL_SCHEDULE(&HelloWorld2::myUpdate),0.01f);
	mainCharacter->stopAllActions();
	CCPoint p=CCPoint(t.x-view.x,t.y-view.y);
	//CCActionInterval* walk= mainCharacter->walkingAnimation(touch->getLocation(),this->mainCharacter->getPosition(),3);
	CCActionInterval* walk= mainCharacter->walkingAnimation(p,this->mainCharacter->getPosition(),3);
	mainCharacter->runAction(walk);
	//this->createCMovingAction(this->mainCharacter->getPosition(),touch->getLocation());
	this->createCMovingAction(this->mainCharacter->getPosition(),p);
	
	
	
	return true;
}

CCPoint HelloWorld2::setViewPosition(CCPoint viewPos)
{
    //CCPoint viewPos=CCPoint(200,200);
	CCPoint playerPos=CCPoint(mainCharacter->getPosition());
	//CCPoint actualPos=CCPoint(playerPos.x,playerPos.y);
	//float placementX=0;
	//float placementY=0;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	float placementX=viewPos.x-playerPos.x;
	float placementY=viewPos.y-playerPos.y;
	float mH=map1->getMapHeight()-eglView->getFrameSize().height;
	float mW=map1->getMapWidth()-eglView->getFrameSize().width;
	
	//H_ABSOLUTE(mW);
	CCPoint final;
	if(mH>0&&mW>0)
	{
	if(placementY>=-mH&&placementY<=0){
	   if(placementX>=-mW&&placementX<=0){ 
		  // placementX=viewPos.x-actualPos.x; 
		  // placementY=viewPos.y-actualPos.y;
		  // placementY=0;
		   
		   //view=final;
		   
	   }
	   else{
		   placementX=placementX>0?0:(-mW);
		  // placementY=viewPos.y-actualPos.y;
		  

	   }
	   /*final=CCPoint(placementX,placementY);
	   this->setPosition(final);
		view=final;
	    return final;*/
	}
	else if(placementX>=-(map1->getMap()->getMapSize().width*32-640)&&placementX<=0){
		   //placementX=viewPos.x-actualPos.x;
		 // placementY=0;
		placementY= placementY>0?0:(-mH);
		   /*
		final=CCPoint(placementX,placementY);
	   this->setPosition(final);
		view=final;
	    return final;*/
	}
}

	else if(mH>0&&mW<=0)
	{
		if(placementY<-mH||placementY>0){
			placementY= placementY>0?0:(-mH);
		}
		placementX=0;
	}
	
		

	else
	{
		placementX=0;
		placementY=0;
	}
	final=CCPoint(placementX,placementY);
	   this->setPosition(final);
		view=final;
	    return final;
	
}

void HelloWorld2::judgeIfHitObstacles()
{
	if((mainCharacter->getPosition().getDistance(NPC1->getPosition()))<=10)
	{
		mainCharacter->stopAllActions();
		return;
	}
	int pX=mainCharacter->getPositionX();
	int pY=mainCharacter->getPositionY();
	
	CCObject*subject=NULL;
	CCArray* ar=map1->getObstacles();
	
	
	  CCARRAY_FOREACH(ar,subject)
	{
		int jLx=((AddiTionDictionary*)(((CCDictionary*)subject)->objectForKey("limits")))->getCollisionLimit("left");
		int jRx=((AddiTionDictionary*)(((CCDictionary*)subject)->objectForKey("limits")))->getCollisionLimit("right");
		int jUy=((AddiTionDictionary*)(((CCDictionary*)subject)->objectForKey("limits")))->getCollisionLimit("up");
		int jDy=((AddiTionDictionary*)(((CCDictionary*)subject)->objectForKey("limits")))->getCollisionLimit("down");


		if((pX>=jLx)&&(pX<=jRx)&&(pY>=jDy)&&(pY<=jUy))
	{
		/*if(dynALX[count]==doorLX&&doorRX==dynARX[count]&&doorDY==dynADY[count]&&doorUY==dynAUY[count])
		{
			player->stopAllActions();
			player->setPosition(saveX,saveY);
			CCDirector::sharedDirector()->purgeCachedData();
			MyScene1*outdoor=MyScene1::create();
			outdoor->runTest();

		}*/
		mainCharacter->stopAllActions();
		//this->unschedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
		//player->runAction(CCMoveTo::create(0.01f,ccp(player->getPositionX(),Dy-1)));
		//if(ifU)player->setPosition(player->getPositionX(),Dy-1);
		//if(!ifU)player->setPosition(player->getPositionX(),Uy+1);
		mainCharacter->setPosition(ccp(saveX,saveY));
		break;
		}
		
		//this->schedule(SEL_SCHEDULE(&HelloWorld::myUpdate));
		
	}
	saveX=mainCharacter->getPositionX();
	saveY=mainCharacter->getPositionY();
	
}

void HelloWorld2::createCMovingAction(CCPoint currentPos,CCPoint targetPos)
{
	cSpeed=currentPos.getDistance(targetPos)/80;

	
	
	
	CCActionInstant* stopCB=CCCallFunc::create(this,SEL_CallFunc(&HelloWorld2::actionFinished));
	//CCActionInterval*action=CCJumpBy::create(1, ccp(0,0), 100, 1);
	//CCActionInterval*action2=action->reverse();
	CCActionInterval*moveTo=CCMoveTo::create(cSpeed,targetPos);
	mainCharacter->runAction(CCSequence::create(moveTo,stopCB,NULL));
	
}

void HelloWorld2::myUpdate(float m)
{ 
	
	judgeIfHitObstacles();
	setViewPosition(CCPoint(200,200));
	
}
void HelloWorld2::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

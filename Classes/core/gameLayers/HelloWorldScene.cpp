#include "HelloWorldScene.h"
#include"HNPCTexts.h"
#define H_ABSOLUTE(x)\
if((x)<=0) x=-x
// when many scenes here might be a mistake
static CCSprite*textBox=NULL;

USING_NS_CC;

CCScene* HelloWorld2::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld2 *layer = HelloWorld2::create();

    // add layer as a child to scene
	scene->addChild(layer->getParent());
	if(!textBox)
	{
		textBox=CCSprite::create("textBox.png");
		textBox->retain();
		layer->getParent()->addChild(textBox);
		textBox->setPosition(ccp(190,140));
		textBox->setScale(0.4f);
		textBox->setVisible(false);
		}
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
	
	CCNode*layerParent=CCNode::create();
	layerParent->addChild(this);
	layerParent->retain();
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	map1=TmxLayer::create();
	map1->retain();
	this->getParent()->getPosition();
	map1->setMapPath("trial2.tmx");  
	CCTMXTiledMap*map=map1->getMap();
	addChild(map,0,998);  
	map->setPosition(0,0);
	map1->setAntiAliasforMapChildren();
	CCTMXLayer*layer=map->layerNamed("background");
	//!!!!!!!!!
	map1->addObstacles("Shelters"); 
	map->setScale(1.0f);
	
	mainCharacter=MainCharacter::create();
	//!!!!!!!!!!!!!!!!!!!!!!!!
	mainCharacter->addImageUsingTextureCache("trial1_MainCharac.png");
	CCArray*spritesA= mainCharacter->insertTextureSpriteFrames(32,48,4,3);
	mainCharacter->setInitialTexture();
	mainCharacter->setPosition(ccp(200,200));
	this->addChild(mainCharacter,2,999);
	
	NPC1=NPC::create(new Maidd());
	NPC1->addImageUsingTextureCache("maid.png");
	NPC1->insertTextureSpriteFrames(32,48,4,4);
	NPC1->setInitialTexture();
	NPC1->setPosition(ccp(250,250));
	addChild(NPC1,3,888);
	NPC1->setNPCMovement(ccp(250,250),ccp(300,250),ccp(300,200),ccp(250,250));
	
	NPC1->setTextContentByArray();
		
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
	if(NPC1->iSConservationOn())
	{    
		NPC1->setTextOffBox(textBox);
		NPC1->setTextIntoBox(textBox);
		return true;
	}

	if(((touch->getLocation().getDistance(NPC1->getPosition()))<=30)
		&&mainCharacter->getPosition().getDistance(NPC1->getPosition())<=60)
	{   //here is the problem:
		mainCharacter->stopForConversation(NPC1,textBox);
		return false;
	}

	textBox->setVisible(false);
	CCPoint t=touch->getLocation();
	unschedule(SEL_SCHEDULE(&HelloWorld2::myUpdate));
	schedule(SEL_SCHEDULE(&HelloWorld2::myUpdate),0.01f);
	mainCharacter->stopAllActions();
	CCPoint p=CCPoint(t.x-view.x,t.y-view.y);
	CCActionInterval* walk= mainCharacter->walkingAnimation(p,this->mainCharacter->getPosition(),3);
	mainCharacter->runAction(walk);
	this->createCMovingAction(this->mainCharacter->getPosition(),p);
	return true;
}

CCPoint HelloWorld2::setViewPosition(CCPoint viewPos)
{
    CCPoint playerPos=CCPoint(mainCharacter->getPosition());
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	float placementX=viewPos.x-playerPos.x;
	float placementY=viewPos.y-playerPos.y;
	float mH=map1->getMapHeight()-eglView->getFrameSize().height;
	float mW=map1->getMapWidth()-eglView->getFrameSize().width;
	
	CCPoint final;
	
	if(mH>0&&mW>0)
	{
	if(placementY>=-mH&&placementY<=0){
	   if(placementX>=-mW&&placementX<=0){ 
		 
	   }
	   else{
		   placementX=placementX>0?0:(-mW);
		  }
	   }
	else if(placementX>=-(map1->getMap()->getMapSize().width*32-640)&&placementX<=0){
		placementY= placementY>0?0:(-mH);
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
		mainCharacter->stopAllActions();
		mainCharacter->setPosition(ccp(saveX,saveY));
		break;
		}
	}
	saveX=mainCharacter->getPositionX();
	saveY=mainCharacter->getPositionY();
}

void HelloWorld2::createCMovingAction(CCPoint currentPos,CCPoint targetPos)
{
	cSpeed=currentPos.getDistance(targetPos)/80;
	CCActionInstant* stopCB=CCCallFunc::create(this,SEL_CallFunc(&HelloWorld2::actionFinished));
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

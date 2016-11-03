#include"HCharactors.h"




bool HCharactorsBase::init(void)
{
	if(!CCSprite::init())
	{
		return false;
	}
	texture=NULL;
	TextureSpriteFrame=CCArray::create();
	TextureSpriteFrame->retain();
	walkDown=CCArray::create();
	walkDown->retain();
	walkLeft=CCArray::create();
	walkLeft->retain();
	walkRight=CCArray::create();
	walkRight->retain();

	return true;
}

void HCharactorsBase::setCPath(std::string cPath)
{
	characPath=CCString::create(cPath);
	characPath->retain();
}

CCString HCharactorsBase::getCPath()
{
	if(characPath){
	return (*characPath);
	}
	return ("NULL");
}

void HCharactorsBase::addImageUsingTextureCache( const char * cPath)
{
	CCTexture2D*textureR=CCTextureCache::sharedTextureCache()->addImage(cPath);
	texture=textureR;
	texture->retain();
	characPath=CCString::createWithContentsOfFile(cPath);
	characPath->retain();
	TextureSpriteFrame=CCArray::create();
	TextureSpriteFrame->retain();
	walkDown=CCArray::create();
	walkDown->retain();
	walkLeft=CCArray::create();
	walkLeft->retain();
	walkRight=CCArray::create();
	walkRight->retain();
	walkUp=CCArray::create();
	walkUp->retain();
}

CCArray* HCharactorsBase::insertTextureSpriteFrames(float width,float height,int row,int column)
{
	for(int rCount=0;rCount<=row-1;rCount++)
	{
		for(int cCount=0;cCount<=column-1;cCount++)
		{
			CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(this->texture, CCRectMake(width*cCount, height*rCount,width, height));
			this->TextureSpriteFrame->addObject(frame0);
		}
	}
	int n=0;
	auto forWalk=[&n,this,column](CCArray*sub){
		int ub=n+column-1;
		for(;n<=ub;n++){
			sub->addObject(TextureSpriteFrame->objectAtIndex(n));
			
		}
		sub->addObject(TextureSpriteFrame->objectAtIndex(n-column));};

	forWalk(walkDown);
	forWalk(walkLeft);
	forWalk(walkRight);
	forWalk(walkUp);
	return this->TextureSpriteFrame;
}

int HCharactorsBase::directionCal(CCPoint currentPos,CCPoint targetPos)
{
	int direction;
	if(targetPos.x>= currentPos.x)
	{
		if(targetPos.y>= currentPos.y)
		{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))>=1)
			{
				direction=3;
			}
			else
			{
				direction=4;
			}
		}
		else{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))<=-1)
			{
				direction=3;
			}
			else
			{
				direction=1;
			}
		}
	  }
	
	else{
		if(targetPos.y>= currentPos.y)
		{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))<=-1)
			{
				direction=2;
			}
			else
			{
				direction=4;
			}
		}
		else{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))>=1)
			{
				direction=2;
			}
			else{
				direction=1;
			}
		} 
	}
	return direction;
}


void HCharactorsBase::setInitialTexture()
{
	CCSpriteFrame* sub=(CCSpriteFrame*)TextureSpriteFrame->objectAtIndex(0);
	this->setTexture(sub->getTexture());
	this->setTextureRect(sub->getRect());
}


CCArray* HCharactorsBase::sendDirectionArray(int num)
{
	switch(num)
	{
	case 1: return walkDown;
	case 2: return walkLeft;
	case 3: return walkRight;
	case 4: return walkUp;
	default: return NULL;
	}
}



bool MainCharactor::init(void)
{
	if(!HCharactorsBase::init())
	{
		return false;
	}
	reciever=CCArray::create();
    reciever->retain();
	return true;
}

CCActionInterval* MainCharactor::walkingAnimation(CCPoint clickPoint, CCPoint currentPoint)
{
	if(reciever)reciever->removeAllObjects();
	int direction;// down=1,left=2,right=3,up=4
	direction=directionCal(currentPoint,clickPoint);
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(sendDirectionArray(direction), 0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCActionInterval* seq = CCSequence::create( animate,NULL);
    CCActionInterval* final=CCRepeatForever::create( seq );
	//tag 01
	final->setTag(01);
	return final;
}


void MainCharactor::stopForConversation(HCharactorsBase*target)
{
	CCPoint mCh=this->getPosition();
	CCPoint targetPos=target->getPosition();
	this->stopAllActions();
	target->stopAllActions();
	((NPC*)target)->ifSetConversationOn(true);
	((NPC*)target)->setTextIntoBox();
}


bool NPC::setNPCMovement(CCPoint a,...)
{
	CCActionInterval*blank=CCActionInterval::create(2.0f);
	CCArray* actionGroup=CCArray::create();
	CCPoint substitute=a;
	 va_list cvar;  
    va_start (cvar, a);
	
	auto actionCreate=[this,actionGroup,blank](CCPoint cPos,CCPoint tPos){
		float speed=tPos.getDistance(cPos)/80;
		CCArray *moveFrames=sendDirectionArray(directionCal(cPos,tPos));
		CCActionInterval*moveTo=CCMoveTo::create(speed,tPos);
		CCAnimation*animation=CCAnimation::createWithSpriteFrames(moveFrames,0.2);
		CCAnimate*animate=CCAnimate::create(animation);
		int times=moveTo->getDuration()/animate->getDuration()+1;
		CCRepeat*repeat=CCRepeat::create(animate,times);
		moveTo->setDuration(times*animate->getDuration());
		CCSpawn*spawn=CCSpawn::create(moveTo,repeat,NULL);
		actionGroup->addObject(spawn);
		actionGroup->addObject(blank);

	};
		while(1)
		{
			CCPoint ref=va_arg(cvar,CCPoint);
			if(ref.equals(a))
			{
				va_end(cvar);
				break;
			}
			actionCreate(substitute,ref);
			substitute=ref;
		}
	
	actionCreate(substitute,a);
	
	if(NULL==this)
	{
		return false;
	}
	CCSequence*sequence=CCSequence::create(actionGroup);
	CCRepeatForever*action=CCRepeatForever::create(sequence);
	this->runAction(action);

	return true;
}

bool NPC::init(trial* NPCobj)
{
	if(!HCharactorsBase::init())
	{
		return false;
	}
	H_delete=NPCobj;
	count=-1;
	_ifBoxOn=false;
	_ifOnConversation=false;

	
	textBox=CCSprite::create("textBox.png");
	textBox->setScale(0.4f);
	textBox->setVisible(false);
	addChild(textBox,1);

	textGroup=NPCobj->sendTextsArray();
	const char*name=NPCobj->returnName();
	NPCnameLabel= CCLabelTTF::create(name, "A Damn Mess.ttf", 26,  
                                          CCSize(800,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	NPCnameLabel->setVisible(false);
	NPCnameLabel->setPosition(ccp(100,100));
	NPCnameLabel->setScale(0.6);
	addChild(NPCnameLabel,2);
	return true;
}

void NPC::setTextContentByArray()
{  
	CCObject*son=NULL;
	CCObject*grandson=NULL;
	CCLayer*y1=(CCLayer*)( this->getParent());
	CCNode*y2=(CCNode*)(y1->getParent());
	CCARRAY_FOREACH(textGroup,son)
	{
		CCArray*texts=(CCArray*)son;
		
		int yDistance=160;
		CCARRAY_FOREACH(texts,grandson)
		{
			CCLabelTTF*final=(CCLabelTTF*)grandson;
			final->setPosition(ccp(328,yDistance));
			yDistance-=10;
			final->setScale(0.5);
			final->setVisible(false);
			
			y2->getPosition();
			y2->addChild(final,10);
		}
	    count++;
	}
	scale=count;
	
}

void NPC::setTextIntoBox()
{
	if((count)!=-1)
	{
		CCObject*sub=NULL;
		NPCnameLabel->setPosition((ccp(395,235)-this->getPosition()));
		NPCnameLabel->setVisible(true);
		CCARRAY_FOREACH((CCArray*)(textGroup->objectAtIndex(scale-count)),sub)
		{
			CCLabelTTF* rece=(CCLabelTTF*)sub;
			rece->setVisible(true);
		}
	_ifBoxOn=true;
	textBox->setPosition((ccp(300,200)-this->getPosition()));
	textBox->setVisible(true);
	}
	else
	{
		
		ifSetConversationOn(false);
		count=scale;
	}
}

bool NPC::ifAndSetBoxStatus()
{
	if(_ifBoxOn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void NPC::setTextOffBox()
{
	CCObject*sub=NULL;
		CCARRAY_FOREACH((CCArray*)(textGroup->objectAtIndex(scale-count)),sub)
	{
		CCLabelTTF* rece=(CCLabelTTF*)sub;
		rece->setVisible(false);
	}
	count--;
	textBox->setVisible(false);
	_ifBoxOn=false;
}

void NPC::ifSetConversationOn(bool ifOn)
{
	if(ifOn)
	{
		_ifOnConversation=true;
	}
	else
	{
		_ifOnConversation=false;
	}
}

bool NPC::iSConservationOn()
{
	return _ifOnConversation;
}

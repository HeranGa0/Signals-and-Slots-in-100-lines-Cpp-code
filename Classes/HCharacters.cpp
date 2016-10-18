#include"HCharacters.h"
#include"HNPCTexts.h"


bool HCharactersBase::init(void)
{
	if(!CCSprite::init())
	{
		return false;
	}
	texture=NULL;
	
	return true;
}

void HCharactersBase::setCPath(std::string cPath)
{
	characPath=CCString::create(cPath);
	characPath->retain();
	TextureSpriteFrame=CCArray::create();
	TextureSpriteFrame->retain();
	walkDown=CCArray::create();
	walkDown->retain();
	walkLeft=CCArray::create();
	walkLeft->retain();
	walkRight=CCArray::create();
	walkRight->retain();
	
}

CCString HCharactersBase::getCPath()
{
	if(characPath){
	return (*characPath);
	}
	return ("NULL");
}

void HCharactersBase::addImageUsingTextureCache( const char * cPath)
{
	CCTexture2D*textureR=CCTextureCache::sharedTextureCache()->addImage(cPath);
	texture=textureR;
	texture->retain();
	characPath=CCString::createWithContentsOfFile(cPath);
	//characPath=CCString::create(cPath);
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
	
	

	//!!!!!!!!!!!!!!!!!!!!!!
	
}

CCArray* HCharactersBase::insertTextureSpriteFrames(float width,float height,int row,int column)
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

int HCharactersBase::directionCal(CCPoint currentPos,CCPoint targetPos)
{
	int direction;// down=1,left=2,right=3,up=4
	if(targetPos.x>= currentPos.x)
	{
		if(targetPos.y>= currentPos.y)
		{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))>=1)
			{
				direction=3;

			}
			else{
				direction=4;
			}
		}
		else{
			if(((targetPos.x- currentPos.x)/(targetPos.y- currentPos.y))<=-1)
			{
				direction=3;

			}
			else{
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
			else{
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


void HCharactersBase::setInitialTexture()
{
	CCSpriteFrame* sub=(CCSpriteFrame*)TextureSpriteFrame->objectAtIndex(0);
	this->setTexture(sub->getTexture());
	this->setTextureRect(sub->getRect());
	

}


CCArray* HCharactersBase::obtainDirection(int num)
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



bool MainCharacter::init(void)
{
	if(!HCharactersBase::init())
	{
		return false;
	}
	reciever=CCArray::create();
    reciever->retain();
	return true;
}

CCActionInterval* MainCharacter::walkingAnimation(CCPoint clickPoint, CCPoint currentPoint,int groupNum)
{
	if(reciever)reciever->removeAllObjects();
	int direction;// down=1,left=2,right=3,up=4
	direction=directionCal(currentPoint,clickPoint);
	/*for(int count=1;count<=groupNum;count++)
	{   
	
		reciever->addObject((TextureSpriteFrame->objectAtIndex((direction-1)*groupNum+count-1)));
	//reciever->addObject((TextureSpriteFrame->objectAtIndex((direction-1)*3+1)));
	//reciever->addObject((TextureSpriteFrame->objectAtIndex((direction-1)*3+2)));
	//reciever->addObject((TextureSpriteFrame->objectAtIndex((direction-1)*4+3)));
	}*/
	
	
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(obtainDirection(direction), 0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCActionInterval* seq = CCSequence::create( animate,NULL);
    CCActionInterval* final=CCRepeatForever::create( seq );
	//tag 01
	final->setTag(01);
	return final;
}


void MainCharacter::stopForConversation(HCharactersBase*target,CCSprite*textBox)
{
	CCPoint mCh=this->getPosition();
	CCPoint targetPos=target->getPosition();
	
	
		this->stopAllActions();
		target->stopAllActions();
		((NPC*)target)->ifSetConversationOn(true);
		((NPC*)target)->setTextIntoBox(textBox);
	
}


bool NPC::setNPCMovement(std::vector<CCPoint> posGroup)
	//(CCSprite*NPC, CCPoint tLeft,CCPoint tRight,CCPoint bRight,CCPoint bLeft)
{
	CCActionInterval*blank=CCActionInterval::create(2.0f);
	CCArray* actionGroup=CCArray::create();
	for(std::vector<CCPoint>::const_iterator iter=posGroup.begin();iter!=posGroup.end()-1;iter++)
	{
		CCPoint cPos=*iter;
		CCPoint tPos=*(iter+1);
		
		float speed=tPos.getDistance(cPos)/80;
		CCArray *moveFrames=obtainDirection(directionCal(cPos,tPos));
		CCActionInterval*moveTo=CCMoveTo::create(speed,tPos);

		
	//	CCCallFuncN*stopWalking=CCCallFuncN::create(this,SEL_CallFuncN(&NPC::stopAction));
		//stopWalking->setDuration(moveTo->getDuration());
	//	CCRepeatForever*repeat=CCRepeatForever::create(animate);
			//moveTo->getDuration()/animate->getDuration()+1);
		//animate->setDuration(moveTo->getDuration());
		CCAnimation*animation=CCAnimation::createWithSpriteFrames(moveFrames,0.2);

		CCAnimate*animate=CCAnimate::create(animation);

		
		int times=moveTo->getDuration()/animate->getDuration()+1;
		CCRepeat*repeat=CCRepeat::create(animate,times);
		moveTo->setDuration(times*animate->getDuration());
	//	CCSequence*trial=CCSequence::createWithTwoActions(moveTo,stopWalking);
		CCSpawn*spawn=CCSpawn::create(moveTo,repeat,NULL);
			//moveTo,repeat,stopWalking,NULL);
		actionGroup->addObject(spawn);
		actionGroup->addObject(blank);


	}
	
	CCPoint cPos=posGroup.back();
	CCPoint tPos=posGroup.front();
	float speed=tPos.getDistance(cPos)/80;
		CCArray *moveFrames=obtainDirection(directionCal(cPos,tPos));
		CCActionInterval*moveTo=CCMoveTo::create(speed,tPos);
		CCAnimation*animation=CCAnimation::createWithSpriteFrames(moveFrames,0.2);
		CCAnimate*animate=CCAnimate::create(animation);
		int times=moveTo->getDuration()/animate->getDuration()+1;
		CCRepeat*repeat=CCRepeat::create(animate,times);
		moveTo->setDuration(times*animate->getDuration());
	//	CCSequence*trial=CCSequence::createWithTwoActions(moveTo,stopWalking);
		CCSpawn*spawn=CCSpawn::create(moveTo,repeat,NULL);
			//moveTo,repeat,stopWalking,NULL);
		actionGroup->addObject(spawn);
		actionGroup->addObject(blank);
	/*CCActionInterval*walkToRight=CCMoveTo::create(tRight.getDistance(tLeft)/80,tRight);
	CCActionInterval*walkToDown=CCMoveTo::create(tRight.getDistance(bRight)/80,bRight);
	CCActionInterval*walkToLeft=CCMoveTo::create(bRight.getDistance(bLeft)/80,bLeft);
	CCActionInterval*walkToUp=CCMoveTo::create(bLeft.getDistance(tLeft)/80,tLeft);

	CCAnimation *animationR = CCAnimation::createWithSpriteFrames(walkRight, 0.2f);
    CCAnimate *animateR = CCAnimate::create(animationR);
	CCAnimation *animationD = CCAnimation::createWithSpriteFrames(walkDown, 0.2f);
    CCAnimate *animateD = CCAnimate::create(animationD);
	CCAnimation *animationL = CCAnimation::createWithSpriteFrames(walkLeft, 0.2f);
    CCAnimate *animateL = CCAnimate::create(animationL);
	CCAnimation *animationU = CCAnimation::createWithSpriteFrames(walkUp, 0.2f);
    CCAnimate *animateU = CCAnimate::create(animationU);
	animateR->setDuration(walkToRight->getDuration());
	animateD->setDuration(walkToDown->getDuration());
	animateL->setDuration(walkToLeft->getDuration());
	animateU->setDuration(walkToUp->getDuration());
	CCActionInterval*blank=CCActionInterval::create(0.5);
	//CCFiniteTimeAction*fBlank((CCFiniteTimeAction*)(blank));
	//fBlank->setDuration(0.2);

	CCSpawn* pRight=CCSpawn::create(walkToRight,animateR,NULL);
	CCSpawn* pDown=CCSpawn::create(walkToDown,animateD,NULL);
	CCSpawn* pLeft=CCSpawn::create(walkToLeft,animateL,NULL);
	CCSpawn* pUp=CCSpawn::create(walkToUp,animateU,NULL);*/

	if(NULL==this)
	{
		return false;
	}
	CCSequence*sequence=CCSequence::create(actionGroup);
		//(pRight,blank,pDown,blank,pLeft,blank,pUp,blank,NULL);
	CCRepeatForever*action=CCRepeatForever::create(sequence);
	this->runAction(action);

	return true;


	
}

bool NPC::init(void)
{
	if(!HCharactersBase::init())
	{
		return false;
	}
	//textGroup=CCArray::create();
	//textGroup->retain();
	count=-1;
	_ifBoxOn=false;
	
	_ifOnConversation=false;
	Maidd *sam=new Maidd();
	textGroup=sam->sendTextsArray();
	return true;
}

void NPC::setTextContentByArray(CCArray* content)
{  //this->getParent()->addChild(textBox,0);
	//textGroup->addObjectsFromArray(content);
	
	CCObject*son=NULL;
	CCObject*grandson=NULL;
	CCARRAY_FOREACH(textGroup,son)
	{
		CCArray*texts=(CCArray*)son;
		
		int yDistance=150;
		CCARRAY_FOREACH(texts,grandson)
		{
			CCLabelTTF*final=(CCLabelTTF*)grandson;
		//final->retain();
		final->setPosition(ccp(240,yDistance));
		yDistance-=10;
		final->setScale(0.5);
		final->setVisible(false);
		CCLayer*y1=(CCLayer*)( this->getParent());
		
		CCNode*y2=(CCNode*)(y1->getParent());
		y2->getPosition();
		y2->addChild(final,10);
		
		
	}
	    count++;
	}
	scale=count;
}

void NPC::setTextIntoBox(CCSprite*textBox)
{
	if((count)!=-1)
	{
		CCObject*sub=NULL;
		CCARRAY_FOREACH((CCArray*)(textGroup->objectAtIndex(scale-count)),sub)
	{
		CCLabelTTF* rece=(CCLabelTTF*)sub;
		rece->setVisible(true);
	}
		
	//((CCLabelTTF*)(textGroup->objectAtIndex(scale-count)))->setVisible(true);
	_ifBoxOn=true;
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

void NPC::setTextOffBox(CCSprite*textBox)
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
/*void NPC::clickOnNPC(CCSprite*mainCharacter)
{

}*/
#include"HCharactors.h"


bool HCharactorsBase::initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column)
{
	if (!Sprite::init())
	{
		return false;
	}
	texture = NULL;
	addImageUsingTextureCache(pictureListPath);
	insertTextureSpriteFrames(subWidth, subHeight, row, column);
	setInitialTexture();
	setAnimationVector();
	setAnchorPoint(Vec2(0.5, 0.5));
	setScale(0.8f);
	return true;
}

void HCharactorsBase::addImageUsingTextureCache(const char * cPath)
{
	texture = Director::getInstance()->getTextureCache()->addImage(cPath);
	
	texture->retain();
	//characPath = CCString::createWithContentsOfFile(cPath);
	//characPath->retain();
}

void HCharactorsBase::insertTextureSpriteFrames(float width, float height, int row, int column)
{
	auto selectVector=[this](int jNum)->Vector<SpriteFrame*>&
	{
		switch (jNum)
		{
			case 0: return vWalkDown;
			case 1: return vWalkLeft;
			case 2: return vWalkRight;
			case 3: return vWalkUp;
			default: log("error"); 
		}
	};
	for (int rCount = 0; rCount <= row - 1; rCount++)
	{
	     auto &frameVector = selectVector(rCount);
		for (int cCount = 0; cCount <= column - 1; cCount++)
		{
			auto *frame0 = SpriteFrame::createWithTexture(this->texture, Rect(width*cCount, height*rCount, width, height));
			frameVector.pushBack(frame0);
		}

	}
	
}

int HCharactorsBase::directionCal(Vec2 currentPos, Vec2 targetPos)
{
	int direction;
	if (targetPos.x >= currentPos.x)
	{
		if (targetPos.y >= currentPos.y)
		{
			if (((targetPos.x - currentPos.x) / (targetPos.y - currentPos.y)) >= 1)
			{
				direction = 3;
			}
			else
			{
				direction = 4;
			}
		}
		else {
			if (((targetPos.x - currentPos.x) / (targetPos.y - currentPos.y)) <= -1)
			{
				direction = 3;
			}
			else
			{
				direction = 1;
			}
		}
	}

	else {
		if (targetPos.y >= currentPos.y)
		{
			if (((targetPos.x - currentPos.x) / (targetPos.y - currentPos.y)) <= -1)
			{
				direction = 2;
			}
			else
			{
				direction = 4;
			}
		}
		else {
			if (((targetPos.x - currentPos.x) / (targetPos.y - currentPos.y)) >= 1)
			{
				direction = 2;
			}
			else {
				direction = 1;
			}
		}
	}
	return direction;
}


void HCharactorsBase::setInitialTexture()
{
	auto sub = vWalkDown.at(0);
	this->setTexture(sub->getTexture());
	this->setTextureRect(sub->getRect());
}


 


 
 bool MainCharactor::initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column)
 {
	 if (!HCharactorsBase::initWithPictureList(pictureListPath,subWidth,subHeight,row,column))
	 {
		 return false;
	 }
	 
	 return true;
 }

 Action* MainCharactor::runWalkingAnimation(Vec2 clickPoint, Vec2 currentPoint)
 {
	
	 int direction;// down=1,left=2,right=3,up=4
	 direction = directionCal(currentPoint, clickPoint);
	 auto walkingAnimation=this->runAction(vWalkingAnimation.at(direction-1));
	 return walkingAnimation;
 }

 
 Action* MainCharactor::createWalkingAction(Vec2 clickPoint, Vec2 currentPoint)
 {
	 float cSpeed = currentPoint.getDistance(clickPoint) / 80.0;
	 auto walkingAnimation = this->runWalkingAnimation(clickPoint, currentPoint);
	 auto afterCast = reinterpret_cast<Node*>(walkingAnimation);
	 auto stopCB = CallFuncN::create(std::bind(stopWalkingAnimation,afterCast));
	 int a = 4;
	 auto moveTo = MoveTo::create(cSpeed, clickPoint);
	 auto finalAction= this->runAction(Sequence::create(moveTo, stopCB, nullptr));
	 return finalAction;
	 
 }

 Vec4 MainCharactor::judgeIfTouchObstacles()
 {
	 float pX = this->getPositionX();
	 float pY = this->getPositionY();
	 Vec4 obsReturnPos=Vec4(0,0,0,0);
	
	 for (auto obsInfo : (*obstaclesForCharactor))
	 {
		 int jLx = obsInfo["left"];
		 int jRx = obsInfo["right"];
		 int jUy = obsInfo["up"];
		 int jDy = obsInfo["down"];

		 if ((pX >= jLx) && (pX <= jRx) && (pY >= jDy) && (pY <= jUy))
		 {
			 this->stopAllActions();
			 this->setPosition(savePoint);
			 obsReturnPos = Vec4(jLx, jRx, jDy, jUy);
			 break;
		 }
	 }
	 savePoint = Vec2(pX, pY);


	 return obsReturnPos;
 }

 

bool NPC::initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column)
 {
	if (!HCharactorsBase::initWithPictureList(pictureListPath, subWidth, subHeight, row, column))
	{
		return false;
	}

	return true;
 }

bool NPC::setNPCMovement(Vec2 a, ...)
{
	//ActionInterval*blank = ActionInterval::
	//CCArray* actionGroup = CCArray::create();
	Vector<FiniteTimeAction*> actionVec;
	Vec2 substitute = a;
	va_list cvar;
	va_start(cvar, a);

	auto determineSpriteFrameVec = [this](int index){
		switch (index){
		case 1: return &vWalkDown;
		case 2: return &vWalkLeft;
		case 3: return &vWalkRight;
		case 4: return &vWalkUp;
		default: CCLOG("error");
		}
	};
	auto delay = DelayTime::create(1.0f);
	auto actionCreate = [this, &actionVec,determineSpriteFrameVec,delay](Vec2 cPos, Vec2 tPos) {
		float speed = tPos.getDistance(cPos) / 80;
		//CCArray *moveFrames = sendDirectionArray(directionCal(cPos, tPos));
		int direction = directionCal(cPos, tPos);
		auto walkFrames = determineSpriteFrameVec(direction);
		auto moveTo = MoveTo::create(speed, tPos);
		auto animation = Animation::createWithSpriteFrames(*walkFrames, 0.2);
		auto animate = Animate::create(animation);
		int times = moveTo->getDuration() / animate->getDuration() + 1;
		auto repeat = Repeat::create(animate, times);
		moveTo->setDuration(times*animate->getDuration());
		auto spawn = Spawn::create(moveTo, repeat, NULL);
		actionVec.pushBack(spawn);
		actionVec.pushBack(delay);
	  };
	while (true)
	{
		Vec2 ref = va_arg(cvar, Vec2);
		if (ref.equals(a))
		{
			va_end(cvar);
			break;
		}
		actionCreate(substitute, ref);
		substitute = ref;
	}

	actionCreate(substitute, a);

	if (NULL == this)
	{
		return false;
	}
	auto sequence = Sequence::create(actionVec);
	auto action = RepeatForever::create(sequence);
	this->runAction(action);
	return true;
}
#ifndef __H_CHARACTORS_H__
#define __H_CHARACTORS_H__
#include"cocos2d.h"
#include"HMaps.h"
USING_NS_CC;

/** define
* class HCharactorBase, which serves as the base class of all Charactors subclasses.
*/
class HCharactorsBase :public Sprite
{
public:
   /**
	* init by the giving argument list
	*  @param const char*  pictureListPath the address of the picture
	*  @param float subWidth the width between each frame
	*  @param float subHeight the height between each frame
	*  @param int row the number of rows in the picture
	*  @param int row the number of columns in the picture
	*  @return if success
	*/
	virtual bool initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column);

protected:
   /**
	* There are four vectors each includes a set of walking frames on one direction
	* 下面是4个容器，每个数组都涵盖了在某个方向上行走的一系列图片帧
	*/
	Vector<SpriteFrame*>vWalkUp;
	Vector<SpriteFrame*>vWalkDown;
	Vector<SpriteFrame*>vWalkLeft;
	Vector<SpriteFrame*>vWalkRight;

	/** @brief vector includes walkingAnimation down=1,left=2,right=3,up=4 */ 
	Vector<RepeatForever*>vWalkingAnimation;
	
   /**
	* calculate the direction by the giving points
	*  @param Vec2 currentPos The current position of Charactor
	*  @param Vec2 currentPos The target position for Charactor to move
	*  @return the direction according to down=1,left=2,right=3,up=4
	*/
	int directionCal(Vec2 currentPos, Vec2 targetPos);

protected:
	

private:
   /**
	*  add Image by using the TextureCache. This function would implement automatically in the function "initWithPictureList"
	*  @param const char *cPath The path of the image
	*/
	void addImageUsingTextureCache(const char *cPath);

   /**
	* Function2: insert textureSriteFrames by manually setting the arguments of spaces among subpictures. This function would implement automatically in the function "initWithPictureList"
	*  @param float width the width between each frame
	*  @param float height the height between each frame
	*  @param int row the number of rows in the picture
	*  @param int row the number of columns in the picture
	*/
    void insertTextureSpriteFrames(float width, float height, int row, int column);

	/**
	*  Function3: set initial (or static) picture for the Charactor. This function would implement automatically in the function "initWithPictureList"
	*/
	void setInitialTexture();


	/**
	*  create and put the Animations into the vWalkingAnimation by the giving Vector<SpriteFrame*>
	*  Vector<SpriteFrame*> &sub the spriteFrame Vector
	*/
	inline void setEachAnimaVec(Vector<SpriteFrame*> &sub)
	{
		auto animation = Animation::createWithSpriteFrames(sub, 0.2f);
		auto animate = Animate::create(animation);
		auto * seq = Sequence::create(animate, NULL);
		auto * forever = RepeatForever::create(seq);
		vWalkingAnimation.pushBack(forever);
	}

	/**
	*  set all SpriteFrames Vectors into vWalkingAnimation
	*/
	inline void setAnimationVector()
	{
		setEachAnimaVec(vWalkDown);
		setEachAnimaVec(vWalkLeft);
		setEachAnimaVec(vWalkRight);
		setEachAnimaVec(vWalkUp);
	}

	/** @brief the initial image of the Charactor */
	Texture2D* texture;
};



/** define
* class MainCharactor
*/

class MainCharactor : public HCharactorsBase
{
public:
	static MainCharactor* create(const char* pictureListPath, float subWidth, float subHeight, int row, int column)
	{
		MainCharactor* pRet = new MainCharactor();

		if (pRet != NULL&&pRet->initWithPictureList(pictureListPath, subWidth, subHeight, row, column))
		{
		
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

   /**
	*  init by the giving argument list
	*  @param const char*  pictureListPath the address of the picture
	*  @param float subWidth the width between each frame
	*  @param float subHeight the height between each frame
	*  @param int row the number of rows in the picture
	*  @param int row the number of columns in the picture
	*  @return if success
	*/
	virtual bool initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column) override;
	
   /**
	*  run the walkingAction of mainCharator by the giving Points
	*  @param Vec2 currentPos The current position of mainCharactor
	*  @param Vec2 currentPos The target position for mainCharactor to move
	*  @return the walkingAction
	*/
	Action* runWalkingAnimation(Vec2 clickPoint, Vec2 currentPoint);

   /**
	*  create the walkingAction of mainCharator by the giving Points
	*  @param Vec2 currentPos The current position of mainCharactor
	*  @param Vec2 currentPos The target position for mainCharactor to move
	*  @return the walkingAction
	*/
	Action* createWalkingAction(Vec2 clickPoint,Vec2 currentPoint );

	/** @brief Function which MainCaractor->stopAction  */
    std::function<void(Node*)> stopWalkingAnimation = [this](Node* walkingAnimation)
	{
		auto removeCast =reinterpret_cast<Action*>(walkingAnimation);
		this->stopAction(removeCast);
	};

	//second way
	/*std::function<void()> stopWalkingAnimation = [this]()
	{
		
		this->stopActionByTag(1);
	};*/

   /**
	*  set Obstacles for the mainCharactor from a giving obstacles vector
	*  @param std::vector<std::map<std::string, float>>* obstaclesVec a obstacles vector
	*/
	inline void setObsForCharac(std::vector<std::map<std::string, float>>* obstaclesVec)
	{
		obstaclesForCharactor = obstaclesVec;
		setHUpdateOn(true);
	}

   /**
	*  set Obstacles for the mainCharactor from a giving obstacles vector
	*  @return the obstacles coordinate mainCharactor hit
	*/
	Vec4 judgeIfTouchObstacles();

	/**
	*  If set HUpdateOn 
	*  @param bool ifOn true=on, false=off
	*/
	inline void setHUpdateOn(bool ifOn)
	{
		if (ifOn) {
			schedule(HUpdate, 0.01f, "judgeIfHitObstacles");
		}
		else {
			unschedule("judgeIfHitObstacles");
			
		}
	}
private:
	Vec2 savePoint;

	/** @brief updating lambda function  */
	std::function<void(float)> HUpdate = [this](float m){
		judgeIfTouchObstacles();
	};
	std::vector<std::map<std::string, float>>* obstaclesForCharactor;
	
};



/** define
* class NPC
*/
class NPC :public HCharactorsBase
{
public:

	/**
	* init by the giving argument list
	*  @param const char*  pictureListPath the address of the picture
	*  @param float subWidth the width between each frame
	*  @param float subHeight the height between each frame
	*  @param int row the number of rows in the picture
	*  @param int row the number of columns in the picture
	*  @return if success
	*/
	virtual bool initWithPictureList(const char* pictureListPath, float subWidth, float subHeight, int row, int column) override;

	static NPC* create(const char* pictureListPath, float subWidth, float subHeight, int row, int column)
	{
		NPC* pRet = new NPC();

		if (pRet != NULL&&pRet->initWithPictureList(pictureListPath, subWidth, subHeight, row, column))
		{
			pRet->autorelease();
			return pRet;
		}

		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	/**
	*  This function enables the NPC to move automatically according to the points set you send to them.
	*  @param Vec2 a first position of NPC
	*  @param var pos a series of points which NPC moves along with
	*  @return if success
	*/
	bool setNPCMovement(Vec2 a, ...);

	
};


#endif //__H_CHARACTORS_H__
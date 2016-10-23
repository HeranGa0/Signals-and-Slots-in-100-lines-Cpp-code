#ifndef __H_MAPS_H_
#define __H_MAPS_H_
#include"cocos2d.h"
#include"HCharacters.h"
using namespace cocos2d;
class AddiTionDictionary: public CCDictionary
{
public:
	static AddiTionDictionary* create()
	{
		AddiTionDictionary* pRet = new AddiTionDictionary();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
	}

	//for up,down,left,right limits
	int getCollisionLimit(const char*limit)
	{
		if("up"==limit){
			return Uy;
		}
		else if("down"==limit){
			return Dy;
		}
		else if("left"==limit){
			return Lx;
		}
		else if("right"==limit){
			return Rx;
		}
		else{
			return -1;
		}

	}

	void setCollisionLimit(int pUy,int pDy,int pRx,int pLx)
	{
		Uy=pUy;
		Dy=pDy;
		Rx=pRx;
		Lx=pLx;
	}
private:
	int Lx;
	int Rx;
	int Uy;
	int Dy;

};
class MapLayerBase: public CCLayer
{
public:
	virtual bool init()
	{
		if ( !CCLayer::init() )
    {
        return false;
    }
		return true;
	}
};

class TmxLayer: public MapLayerBase
{
public:
	virtual bool init()
	{
		
		if ( !MapLayerBase::init() )
    {
        return false;
    }
		return true;
	}

	static TmxLayer* create();
	static TmxLayer* create(const char* mapPath);

	void setMapPath(const char*mapPath)
	{
		map=CCTMXTiledMap::create(mapPath);
		mH=(map->getMapSize().height)*(map->getTileSize().height);
		mW=(map->getMapSize().width)*(map->getTileSize().width);
		obstacles=CCArray::create();
		obstacles->retain();
	}

	void setAntiAliasforMapChildren();

	CCArray* addObstacle(const char*objectGroupName,const char*objectName);

	CCArray* addObstacles(const char*objectGroupName);

	void setObstaclesTrue(bool n);

	CCArray* getObstacles();

	CCTMXTiledMap *getMap()
	 {
		 return map;
	 }
	
    float getMapWidth()
	{
		return mW;
	}

	float getMapHeight()
	{
		return mH;
	}

private:
	 CCTMXTiledMap *map;
	 CCArray*obstacles;
	 float mW;
	 float mH;
};





#endif//__H_MAPS_H_
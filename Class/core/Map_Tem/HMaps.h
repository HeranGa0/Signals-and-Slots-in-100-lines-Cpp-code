#ifndef __H_MAPS_H_
#define __H_MAPS_H_
#include"cocos2d.h"
using namespace cocos2d;


/** define
* class MapManagerBase, which serves as the base class of all types of maps
*/
class MapManagerBase : public Layer
{
public:

	virtual bool init() override
	{
		if (!Layer::init())
		{
			return false;
		}
		return true;
	}
};



/** define
* class HTMXManager manages TMX maps
*/
class HTMXManager : public MapManagerBase
{
public:
	virtual bool init() override
	{

		if (!MapManagerBase::init())
		{
			return false;
		}
		return true;
	}

	static HTMXManager* create();
	static HTMXManager* create(const char* mapPath);

	inline void setMapPath(const char*mapPath)
	{
		map = TMXTiledMap::create(mapPath);
		mH = (map->getMapSize().height)*(map->getTileSize().height);
		mW = (map->getMapSize().width)*(map->getTileSize().width);
	}

	void setAntiAliasforMapChildren();

	/**
	*  add an Obstacle from an object group of the map into std::vector<std::map<std::string, float>> obstaclesVec;
	*  @param const char*objectGroupName ObjectGroup's name
	*  @param const char*objectName object's name
	*/
	void addObstacle(const char*objectGroupName, const char*objectName);

	/**
	*  automatically add Obstacles from an object group of the map into std::vector<std::map<std::string, float>> obstaclesVec;
	*  @param const char*objectGroupName ObjectGroup's name
	*/
	void addObstacles(const char*objectGroupName);

    std::vector<std::map<std::string, float>>* getObstacles();

	inline TMXTiledMap *getMap()
	{
		return map;
	}

	inline float getMapWidth()
	{
		return mW;
	}

	inline float getMapHeight()
	{
		return mH;
	}

private:
	//TMXLayer 
	TMXTiledMap *map;
	float mW;
	float mH;
	std::vector<std::map<std::string, float>> obstaclesVec;
	std::map<std::string, float> obstacleInfo;
};





#endif//__H_MAPS_H_

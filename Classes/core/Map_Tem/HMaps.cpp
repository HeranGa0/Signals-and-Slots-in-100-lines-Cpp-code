#include"HMaps.h"

HTMXManager* HTMXManager::create()
{
	HTMXManager*pRet = new HTMXManager();

	if (pRet && pRet->init())
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
HTMXManager* HTMXManager::create(const char*mapPath)
{
	HTMXManager*pRet = new HTMXManager();

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		pRet->setMapPath(mapPath);
		pRet->mH = (pRet->map->getMapSize().height)*(pRet->map->getTileSize().height);
		pRet->mW = (pRet->map->getMapSize().width)*(pRet->map->getTileSize().width);
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void HTMXManager::setAntiAliasforMapChildren()
{
	auto pChildrenVec = map->getChildren();
	for (auto pObject : pChildrenVec)
	{
		((SpriteBatchNode*)pObject)->getTexture()->setAntiAliasTexParameters();
	}
}

void HTMXManager::addObstacle(const char*objectGroupName, const char*objectName)
{
	auto* objGroup = map->getObjectGroup(objectGroupName);
	auto obj = objGroup->getObject(objectName);

	int Lx = (obj.at("x")).asInt();
	int Rx = (obj.at("width")).asInt() + Lx;
	int Dy = (obj.at("y")).asInt();
	int Uy = Dy+(obj.at("height")).asInt();
	
	
	obstacleInfo["up"] = Uy;
	obstacleInfo["down"] = Dy;
	obstacleInfo["right"] = Rx;
	obstacleInfo["left"] = Lx;
	obstaclesVec.push_back(obstacleInfo);
	obstacleInfo.clear();
}

void HTMXManager::addObstacles(const char*objectGroupName)
{

	
	auto* objGroup = map->getObjectGroup(objectGroupName);
	auto objects = objGroup->getObjects();
	
	for (auto obj : objects)
	{
		int Lx = (obj.asValueMap().at("x")).asInt();
		int Rx = (obj.asValueMap().at("width")).asInt() + Lx;
		int Dy = (obj.asValueMap().at("y")).asInt();
		int Uy = Dy + (obj.asValueMap().at("height")).asInt();

		//std::map<std::string, float> obstacleInfo;
		obstacleInfo["up"] = Uy;
		obstacleInfo["down"] = Dy;
		obstacleInfo["right"] = Rx;
		obstacleInfo["left"] = Lx;
		obstaclesVec.push_back(obstacleInfo);
		obstacleInfo.clear();
	}

}

 std::vector<std::map<std::string, float>>* HTMXManager::getObstacles()
{
	return &obstaclesVec;
}
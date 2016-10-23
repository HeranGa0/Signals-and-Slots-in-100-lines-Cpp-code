#include"HMaps.h"

TmxLayer* TmxLayer::create()
{
	TmxLayer*pRet=new TmxLayer();

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
TmxLayer* TmxLayer::create(const char*mapPath)
{
	TmxLayer*pRet=new TmxLayer();

	if (pRet && pRet->init()) 
    { 
        pRet->autorelease(); 
		pRet->setMapPath(mapPath);
		pRet->mH=(pRet->map->getMapSize().height)*(pRet->map->getTileSize().height);
		pRet->mW=(pRet->map->getMapSize().width)*(pRet->map->getTileSize().width);
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

void TmxLayer::setAntiAliasforMapChildren()
{
	 CCArray* pChildrenArray = map->getChildren();  
     CCSpriteBatchNode* child = NULL;  
     CCObject* pObject = NULL;  
     CCARRAY_FOREACH(pChildrenArray, pObject)  
     {  
         child = (CCSpriteBatchNode*)pObject;  
	     if(!child)  
         break;  
		 child->getTexture()->setAntiAliasTexParameters();  
       }  
}

CCArray* TmxLayer::addObstacle(const char*objectGroupName,const char*objectName)
{
	if(!obstacles)
	{
		obstacles=CCArray::create();
		obstacles->retain();
	}
	CCTMXObjectGroup* objGroup = map->objectGroupNamed(objectGroupName); 
	CCDictionary*obj= objGroup->objectNamed(objectName);
	obstacles->addObject(obj);

	//add object's limits of collision : up,down,left and right
	int Lx=((CCString*)obj->objectForKey("x"))->intValue();
			
	int Rx=((CCString*)obj->objectForKey("width"))->intValue()+Lx;

	int Dy=((CCString*)obj->objectForKey("y"))->intValue();
		
    int Uy=Dy+(((CCString*)obj->objectForKey("height"))->intValue());
			
	AddiTionDictionary*limits=AddiTionDictionary::create();
	limits->setCollisionLimit(Uy,Dy,Rx,Lx);
	obj->setObject(limits,"limits");

	return obstacles;
		
}

CCArray* TmxLayer::addObstacles(const char*objectGroupName)
{
	
	//!!!!!!!!!!
	CCTMXObjectGroup* objGroup = map->objectGroupNamed(objectGroupName); 
	
	//add objects' limits of collision : up,down,left and right
	CCObject*subject=NULL;
	CCARRAY_FOREACH(objGroup->getObjects(),subject)
   {
	   CCDictionary*obj=(CCDictionary*)subject;
	   int Lx=((CCString*)obj->objectForKey("x"))->intValue();
			
	  int Rx=((CCString*)obj->objectForKey("width"))->intValue()+Lx;

	  int Dy=((CCString*)obj->objectForKey("y"))->intValue();
		
      int Uy=Dy+(((CCString*)obj->objectForKey("height"))->intValue());
			
	  AddiTionDictionary*limits=AddiTionDictionary::create();
	  limits->retain();
	  limits->setCollisionLimit(Uy,Dy,Rx,Lx);
	  obj->setObject(limits,"limits");
	 }
	
	obstacles->addObjectsFromArray(objGroup->getObjects());
	
	return obstacles;
}

CCArray* TmxLayer::getObstacles()
{
	int a=0;
	return obstacles;
}
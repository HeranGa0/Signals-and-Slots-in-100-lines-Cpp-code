#include"cocos2d.h"
using namespace cocos2d;
/********************************************************************
 status: at the beginning
 刚开始开发中
 *****************************************************************/

class HMenu:public CCSprite
{
public:
	static HMenu* create()
	{
		HMenu *pRet=new HMenu();
		if (pRet != NULL&&pRet->init())
        {
           pRet->autorelease();
		   return pRet;
		}
		else
		{
			delete pRet;
			pRet=NULL;
			return NULL;
		}
	}
	
	static HMenu* createWithPath(const char* path);
	
	bool init()
	{
		if(!CCSprite::init())
		{
			return false;
		}
		return true;
	}

	 virtual bool initWithFile(const char *pszFilename);

};

class HMenuManager:public CCNode
{
public:
	CREATE_FUNC(HMenuManager);
	virtual bool init();
	void setmenu(CCPoint click);

private:
	HMenu* mainMenu;
	HMenu* objects;
	HMenu* skills;
	HMenu* equipments;
	HMenu* beClosed;
	
};
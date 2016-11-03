#include"HTexts.h"
#define H_ABSOLUTE(x)\
if((x)<=0)\
	x=-x;

	
HMenu* HMenu::createWithPath(const char*path)
{
	
		HMenu *pRet=new HMenu();
		if (pRet != NULL&&pRet->initWithFile(path))
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

bool HMenu::initWithFile(const char *pszFilename)
{
	if(!CCSprite::initWithFile(pszFilename)){
		return false;
	}
	setPosition(ccp(200,200));
	setScale(0.7);
	setVisible(false);
	return true;

}


bool HMenuManager::init()
{
	if(!CCNode::init()){
		return false;
	}
	mainMenu=HMenu::createWithPath("MainMenu.png");
	skills=HMenu::createWithPath("skills.png");
	equipments=HMenu::createWithPath("equipments.png");
	objects=HMenu::createWithPath("objects.png");
	auto ini=[this](HMenu* menu){
		this->addChild(menu,30);};
	ini(mainMenu);
	ini(skills);
	ini(equipments);
	ini(objects);
	beClosed=mainMenu;
	//beClosed->setVisible(true);
	//mainMenu->setVisible(true);
}

void HMenuManager::setmenu(CCPoint click)
{
	auto judgePos=[this,click](CCPoint position,HMenu*menu)->int{
	float pX=position.x;
	float pY=position.y;
	float cX=click.x;
	float cY=click.y;
	float dX=(cX-pX);
	float dY=(cY-pY);
	H_ABSOLUTE(dX);
	H_ABSOLUTE(dY);
	
	
	if(dX<=60&&dY<=15)
	{
		beClosed->setVisible(false);
		menu->setVisible(true);
		beClosed=menu;
		return 1;
	}
	return 0;
	};
		//CCPoint position=ccp(50,330);
	if(judgePos(ccp(50,330),mainMenu)) return;
	if(judgePos(ccp(50,315),objects))  return;
	if(judgePos(ccp(50,300),equipments))return;

	
}
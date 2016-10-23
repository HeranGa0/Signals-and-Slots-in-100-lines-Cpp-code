#ifndef _H_NPC_TEXTS_H_
#define _H_NPC_TEXTS_H_

#include"cocos2d.h"
using namespace cocos2d;
#define $ inline void

#define NEW_CHARACTOR_TEXTS(first)\
	class first:public trial\
{\
public:\
	inline void setRTextsArray();\
	CCArray* sendTextsArray(){\
	setRTextsArray();\
	return parent;}\
}

#define SETTEXT setRTextsArray()
#define ADD_NEW setSubTextsArray

class trial
{
public:
	trial()
	{
		parent=CCArray::create();
		parent->retain();
	}
	virtual CCArray* sendTextsArray()
	{
		return parent;
	}
	
	inline void setRTextsArray()
	{
		int ad=0;
		int b=2;
	}
	void setSubTextsArray(const char* first, ...)
	{   CCArray* sub=CCArray::create();
	    sub->retain();
        va_list cvar;  
		va_start (cvar, first);
		CCLabelTTF *text1 = CCLabelTTF::create(first, "A Damn Mess.ttf", 26,  
                                          CCSize(800,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		text1->retain();
		sub->addObject(text1);
		while(1)
		{
			const char* ref=va_arg(cvar,const char*);
			if(!ref)
			{
				va_end(cvar);
				break;
			}
			
			CCLabelTTF *text = CCLabelTTF::create(ref, "A Damn Mess.ttf", 26,  
                                          CCSize(800,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter); 
		    text->retain();
		    sub->addObject(text);
		}
		parent->addObject(sub);
	}
	virtual ~trial(){};

protected:
	CCArray* parent;
};

//example of how to use text-setting
NEW_CHARACTOR_TEXTS(Maidd);
$ Maidd::SETTEXT{
	ADD_NEW("Example of cocos2d-RPG-Template @ Heran Gao",NULL);
	ADD_NEW("is there anything I can help with?",NULL);
}


#endif//_H_NPC_TEXTS_H_












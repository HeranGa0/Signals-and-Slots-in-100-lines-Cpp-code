#ifndef _H_NPC_TEXTS_H_
#define _H_NPC_TEXTS_H_

#include"cocos2d.h"
using namespace cocos2d;

// "$" represents "inline void", which is more convenient to express.
#define $ inline void

//the macro that creates new NPC texts.
#define NEW_CHARACTOR_TEXTS(first)\
	class first:public trial\
{\
public:\
	inline void setRTextsArray();\
	CCArray* sendTextsArray(){\
	setRTextsArray();\
	return parent;}\
	virtual const char* returnName(){\
	const char*reg=#first;\
	return reg;}\
}

// More convenient to call fucntions
#define SETTEXT setRTextsArray()
#define ADD_NEW setSubTextsArray

// Base class of NPCText
class trial
{
public:
	trial(){
		parent=CCArray::create();
		parent->retain();
	}
	virtual CCArray* sendTextsArray(){
		return parent;
	}
	
	inline void setRTextsArray(){}
	
	//variable arguments function to set contents
	void setSubTextsArray(const char* first, ...){  
		CCArray* sub=CCArray::create();
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

	// return the name of the NPC
	virtual const char* returnName(){
		const char* reg="BaseClass";
		return reg;
	}
	
	virtual ~trial(){};

protected:
	CCArray* parent;
};

//example of how to use text-setting to create new NPC texts
//Character's texts 1:
NEW_CHARACTOR_TEXTS(Maid);
$ Maid::SETTEXT{
	ADD_NEW("Hi I am a pretty maid",NULL);
	ADD_NEW("Want to ask me out?",NULL);
}

//Character's texts 2:
NEW_CHARACTOR_TEXTS(pet);
$ pet::SETTEXT{
	ADD_NEW("I am a poor peppy",NULL); // add new sentences
	ADD_NEW("Stop bulling me!",NULL);
	ADD_NEW(" What's up bro",NULL);
}

#endif//_H_NPC_TEXTS_H_












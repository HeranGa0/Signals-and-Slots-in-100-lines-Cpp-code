

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"HCharactors.h"

/** class HelloWorld define
* this is the base class for all gameLayers
*/
class HelloWorld : public cocos2d::Layer
{
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    // a selector callback
    void menuCloseCallback(Ref* sender);

	
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

protected:
   /**
	* Keep the mainCharactor on the screenCenter
	*  @param Vec2 ScreenCenter The point you set for screenCenter
	*  @return the point which the layer setPosition on
	*/
	Vec2 setViewPosition(Vec2 ScreenCenter);
private:

	MainCharactor* mainCharactor;
	HTMXManager* mapManager;
	/** @brief The point which HelloWorld setPosition on */
	Vec2 view;
	/** @brief map height-screen height */
	float mH;
	/** @brief map width-screen width */
	float mW;
	/** @brief updating lambda function  */
	std::function<void(float)> lUpdate = [this](float m) {
		setViewPosition(Vec2(200, 200));
	};

   /**
	* Set lUpdate on
	*  @param bool ifOn true for on, false for off
	*/
	inline void setlUpdateOn(bool ifOn)
	{
		if (ifOn) {
			schedule(lUpdate, "setViewPosition");
		}
		else {
			unschedule("setViewPosition");
		}
	}
	
};

#endif // __HELLOWORLD_SCENE_H__

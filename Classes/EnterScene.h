#ifndef __ENTERSCENE_SCENE_H__
#define __ENTERSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
using namespace cocos2d::ui;


class Enter: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Enter);

	static int GameType;//对战模式,人人为0，人机为1
private:
	void startGameTouch(Ref *pSender, Widget::TouchEventType type);
	void startAITouch(Ref *pSender, Widget::TouchEventType type);
	void quitGameTouch(Ref *pSender, Widget::TouchEventType type);
	Layout* root;
	Button* startGame_btn;
	Button* AIstart_btn;
	Button* quitGame_btn;
};

#endif // __ENTERSCENE_SCENE_H__

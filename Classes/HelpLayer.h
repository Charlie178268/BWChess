#ifndef __HELPLAYER_SCENE_H__
#define __HELPLAYER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
using namespace cocos2d::ui;


class Help : public cocos2d::Layer
{
public:

	virtual bool init();

	CREATE_FUNC(Help);
private:
	void closeTouch(Ref *pSender, Widget::TouchEventType type);
	void closeAnimation(Node* pSender);//¹Ø±Õ²ãµÄ¶¯»­
	Layout* root;
	Button* close_btn;
};

#endif // __HELPLAYER_SCENE_H__


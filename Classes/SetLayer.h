#ifndef __SETLAYER_SCENE_H__
#define __SETLAYER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d::ui;


class SetLayer: public cocos2d::Layer
{
public:
	
	virtual bool init();

	CREATE_FUNC(SetLayer);
private:
	void closeTouch(Ref *pSender, Widget::TouchEventType type);
	void closeAnimation(Node* pSender);
	void closeBgMusic(Ref* pSender, CheckBoxEventType type);//�رձ�������
	void closeSound(Ref* pSender, CheckBoxEventType type);//�ر���Ч
	void sliderCallback(Ref* sender, SliderEventType type);//��������
	
	Slider* volume_slider;
	Layout* root;
	Button* close_btn;
	CheckBox* selectMusic1_box;
	CheckBox* selectSound1_box;
};



#endif // __SETLAYER_SCENE_H__


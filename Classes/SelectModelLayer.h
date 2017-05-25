#ifndef __SELECTMODELLAYER_SCENE_H__
#define __SELECTMODELLAYER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
#include "ChessScene.h"
#include "ChessLogic.h"
//#include "EnterScene.h"
using namespace cocos2d::ui;
USING_NS_CC;

class SelectModelLayer: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SelectModelLayer);
	
private:
	void haveSetTouch(Ref *pSender, Widget::TouchEventType type);
	void selectNew(Ref* pSender, CheckBoxEventType type);
	void selectSave(Ref* pSender, CheckBoxEventType type);
	void selectWhite(Ref* pSender, CheckBoxEventType type);
	void selectBlack(Ref* pSender, CheckBoxEventType type);

	CheckBox* selectNew_box;//选择新开游戏
	CheckBox* selectSave_box;//读取记录
	CheckBox* selectWhite_box;//白子
	CheckBox* selectBlack_box;//黑子
	LabelTTF *label;//无记录文件提示框
	Layout* root;
	Button* haveSet_btn;
};

#endif // __SELECTMODELLAYER_SCENE_H__


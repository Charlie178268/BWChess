#include "SetLayer.h"
#include "ChessScene.h"

using namespace CocosDenshion;

USING_NS_CC;

bool SetLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//CCLOG("%d\n", Chess::isSoundPlay);

	auto rootNode = CSLoader::createNode("layer/setLayer.csb");
	root = (Layout*)rootNode->getChildByName("set_pannel");//获取rootNode的第一层元素						
	root->setScale(0);//缩放为0 

	close_btn = (Button*)Helper::seekWidgetByName(root, "close_btn");
	selectMusic1_box = (CheckBox*)Helper::seekWidgetByName(root, "selectMusic1_box");
	selectSound1_box = (CheckBox*)Helper::seekWidgetByName(root, "selectSound1_box");
	volume_slider = (Slider*)Helper::seekWidgetByName(root, "volume_slider");
	
	selectSound1_box->setSelectedState(Chess::isSoundPlay);
	selectMusic1_box->setSelectedState(Chess::isMusicPlay);
	volume_slider->setPercent(Chess::bgVol*100.0);

	close_btn->addTouchEventListener(CC_CALLBACK_2(SetLayer::closeTouch, this));

	//音乐的开关
	selectMusic1_box->addEventListenerCheckBox(this, checkboxselectedeventselector( SetLayer::closeBgMusic) );
	selectSound1_box->addEventListenerCheckBox(this, checkboxselectedeventselector( SetLayer::closeSound) );
	volume_slider->addEventListenerSlider(this, sliderpercentchangedselector(SetLayer::sliderCallback));
	this->addChild(rootNode);
	root->runAction(ScaleTo::create(0.2, 1.0));//播放出现的动画

	return true;
}

//触摸监听
void SetLayer::closeTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto seq = Sequence::create(ScaleTo::create(0.2, 0), CallFuncN::create( CC_CALLBACK_1(SetLayer::closeAnimation, this)), NULL);
		root->runAction(seq);
		break;
	}
}

void SetLayer::closeAnimation(Node* pSender)
{
	this->removeFromParentAndCleanup(true);
}

void SetLayer::closeBgMusic(Ref* pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::isMusicPlay = true;
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); //选中时响应
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		Chess::isMusicPlay = false;
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//未选中时响应
		break;
	default:
		break;
	}
}

void SetLayer::closeSound(Ref* pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::isSoundPlay = true;
		//CCLOG("%d\n", Chess::isSoundPlay);
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		Chess::isSoundPlay = false;//未选中时响应
		//CCLOG("%d\n", Chess::isSoundPlay);
		break;
	default:
		break;
	}
}

void SetLayer::sliderCallback(Ref* sender, SliderEventType type)
{
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		float pece1 = volume_slider->getPercent();
		Chess::bgVol = pece1/ 100.0;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Chess::bgVol);//手机上测试有用
		CCLOG("%lf", pece1);
		break;
	}
}
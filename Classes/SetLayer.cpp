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
	root = (Layout*)rootNode->getChildByName("set_pannel");//��ȡrootNode�ĵ�һ��Ԫ��						
	root->setScale(0);//����Ϊ0 

	close_btn = (Button*)Helper::seekWidgetByName(root, "close_btn");
	selectMusic1_box = (CheckBox*)Helper::seekWidgetByName(root, "selectMusic1_box");
	selectSound1_box = (CheckBox*)Helper::seekWidgetByName(root, "selectSound1_box");
	volume_slider = (Slider*)Helper::seekWidgetByName(root, "volume_slider");
	
	selectSound1_box->setSelectedState(Chess::isSoundPlay);
	selectMusic1_box->setSelectedState(Chess::isMusicPlay);
	volume_slider->setPercent(Chess::bgVol*100.0);

	close_btn->addTouchEventListener(CC_CALLBACK_2(SetLayer::closeTouch, this));

	//���ֵĿ���
	selectMusic1_box->addEventListenerCheckBox(this, checkboxselectedeventselector( SetLayer::closeBgMusic) );
	selectSound1_box->addEventListenerCheckBox(this, checkboxselectedeventselector( SetLayer::closeSound) );
	volume_slider->addEventListenerSlider(this, sliderpercentchangedselector(SetLayer::sliderCallback));
	this->addChild(rootNode);
	root->runAction(ScaleTo::create(0.2, 1.0));//���ų��ֵĶ���

	return true;
}

//��������
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
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); //ѡ��ʱ��Ӧ
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		Chess::isMusicPlay = false;
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//δѡ��ʱ��Ӧ
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
		Chess::isSoundPlay = false;//δѡ��ʱ��Ӧ
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
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Chess::bgVol);//�ֻ��ϲ�������
		CCLOG("%lf", pece1);
		break;
	}
}
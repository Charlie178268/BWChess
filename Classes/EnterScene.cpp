#include "EnterScene.h"
#include "SelectModelLayer.h"
USING_NS_CC;

int Enter::GameType = 0;
Scene* Enter::createScene()
{

	auto scene = Scene::create();

	auto layer = Enter::create();

	scene->addChild(layer);

	return scene;
}

bool Enter::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("scene/MainScene.csb");
	root = (Layout*)rootNode->getChildByName("mainSc_panal");//获取rootNode的第一层元素						

	startGame_btn = (Button*)Helper::seekWidgetByName(root, "start_btn");//获取开始按钮
	AIstart_btn = (Button*)Helper::seekWidgetByName(root, "AIstart_btn");
	quitGame_btn = (Button*)Helper::seekWidgetByName(root, "quit_btn");//获取退出按钮
 	startGame_btn->addTouchEventListener(CC_CALLBACK_2(Enter::startGameTouch, this));//开始监听函数
	AIstart_btn->addTouchEventListener(CC_CALLBACK_2(Enter::startAITouch, this));
	quitGame_btn->addTouchEventListener(CC_CALLBACK_2(Enter::quitGameTouch, this));//退出监听函数

	this->addChild(rootNode);

	return true;
}
//触摸监听
void Enter::startGameTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		GameType = 0;
		auto director = Director::getInstance();
		auto scene = SelectModelLayer::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);
		break;
	}
}
void Enter::quitGameTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
		break;
	}
	
}

void Enter::startAITouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		//人机对战模式
		auto director = Director::getInstance();
		auto scene = SelectModelLayer::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);
		GameType = 1;
		break;
	}

}
#include "HelpLayer.h"
USING_NS_CC;

bool Help::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("layer/helpLayer.csb");
	root = (Layout*)rootNode->getChildByName("help_pannel");//获取rootNode的第一层元素	
	root->setScale(0);

	close_btn = (Button*)Helper::seekWidgetByName(root, "close_btn");
	close_btn->addTouchEventListener(CC_CALLBACK_2(Help::closeTouch, this));

	this->addChild(rootNode);
	root->runAction(ScaleTo::create(0.2, 1.0));

	return true;
}

//触摸监听
void Help::closeTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto seq = Sequence::create(ScaleTo::create(0.2, 0), CallFuncN::create(CC_CALLBACK_1(Help::closeAnimation, this)), NULL);//动作序列
		root->runAction(seq);
		break;
	}
}

void Help::closeAnimation(Node* pSender)
{
	this->removeFromParentAndCleanup(true);
}
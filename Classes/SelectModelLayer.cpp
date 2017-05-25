#include "SelectModelLayer.h"
#include "string"
USING_NS_CC;
Scene* SelectModelLayer::createScene()
{

	auto scene = Scene::create();

	auto layer = SelectModelLayer::create();

	scene->addChild(layer);

	return scene;
}

bool SelectModelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("scene/initScene.csb");
	root = (Layout*)rootNode->getChildByName("start_panel");//��ȡrootNode�ĵ�һ��Ԫ��						

	selectNew_box = (CheckBox*)Helper::seekWidgetByName(root, "selectNew_box");
	selectSave_box = (CheckBox*)Helper::seekWidgetByName(root, "selectSave_box");
	selectBlack_box = (CheckBox*)Helper::seekWidgetByName(root, "selectBlack_box");
	selectWhite_box = (CheckBox*)Helper::seekWidgetByName(root, "selectWhite_box");
 

	haveSet_btn = (Button*)Helper::seekWidgetByName(root, "haveSet_btn");
	haveSet_btn->addTouchEventListener(CC_CALLBACK_2(SelectModelLayer::haveSetTouch, this));
	selectNew_box->addEventListenerCheckBox(this, checkboxselectedeventselector(SelectModelLayer::selectNew));
	selectSave_box->addEventListenerCheckBox(this, checkboxselectedeventselector(SelectModelLayer::selectSave));
	selectBlack_box->addEventListenerCheckBox(this, checkboxselectedeventselector(SelectModelLayer::selectBlack));
	selectWhite_box->addEventListenerCheckBox(this, checkboxselectedeventselector(SelectModelLayer::selectWhite));

	this->addChild(rootNode);

	return true;
}

//��������
void SelectModelLayer::haveSetTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		//�����ʼ��
		if (Chess::model == 1)//��ȡ����
		{
			auto fu = FileUtils::getInstance();
			CCLOG("%s", fu->getWritablePath().c_str());
			std::string pth = fu->getWritablePath().c_str();//��ȡ�ĵ�ַ��const����
			std::string pt = "data.txt";
			std::string path1 = pth + pt;//Ϊ�˷�ֹ���Զ�ת��
			if (!fu->isFileExist(path1))//������
			{
				if (!label) {
					label = LabelTTF::create("No MemoryFile!", "����", 40);
					label->setColor(Color3B(255, 0, 0));
					label->setPosition(500, 180);
					addChild(label, 1);//����һ��text����ʾ�޴浵
				}
			}
			else
			{
				//�л�����
				auto director = Director::getInstance();
				auto scene = Chess::createScene();
				auto transition = TransitionCrossFade::create(1.0f, scene);
				director->replaceScene(transition);
			}
		}
		else {
				//�л�����
				auto director = Director::getInstance();
				auto scene = Chess::createScene();
				auto transition = TransitionCrossFade::create(1.0f, scene);
				director->replaceScene(transition);
			}
			break;
	}
}

//ѡ���¿���Ϸ
void SelectModelLayer::selectNew(Ref *pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::model = 0;
		if (label) {
			removeChild(label);
			label = NULL;
		}
		//����ѡ��״̬
		selectSave_box->setSelectedState(false);
		selectNew_box->setSelectedState(true);
		selectWhite_box->setSelectedState(true);
		selectBlack_box->setSelectedState(false);
		selectBlack_box->setEnabled(true);
		selectWhite_box->setEnabled(false);
		selectNew_box->setEnabled(false);
		selectSave_box->setEnabled(true);

		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		//selectSave_box->setSelectedState(true);
		//selectBlack_box->setEnabled(false);
		//selectWhite_box->setEnabled(false);
		break;
	default:
		break;
	}
}
//ѡ���ȡ����
void SelectModelLayer::selectSave(Ref *pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::model = 1;

		selectSave_box->setSelectedState(true);
		selectNew_box->setSelectedState(false);
		selectBlack_box->setEnabled(false);
		selectWhite_box->setEnabled(false);
		selectSave_box->setEnabled(false);
		selectNew_box->setEnabled(true);
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		break;
	default:
		break;
	}
}
//ѡ�����
void SelectModelLayer::selectBlack(Ref *pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::turn = false;

		selectBlack_box->setSelectedState(true);
		selectWhite_box->setSelectedState(false);
		selectBlack_box->setEnabled(false);
		selectWhite_box->setEnabled(true);
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		break;
	default:
		break;
	}
}
//ѡ�����
void SelectModelLayer::selectWhite(Ref *pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		Chess::turn = true;
		selectWhite_box->setSelectedState(true);
		selectBlack_box->setSelectedState(false);
		selectWhite_box->setEnabled(false);
		selectBlack_box->setEnabled(true);
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		//selectSave_box->setSelectedState(true);
		//selectBlack_box->setEnabled(false);
		//selectWhite_box->setEnabled(false);
		break;
	default:
		break;
	}
}
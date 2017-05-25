#include "ChessScene.h"
#include "SetLayer.h"
#include "HelpLayer.h"
#include "SelectModelLayer.h"
#include "iostream"
#include "SimpleAudioEngine.h"
#include "EnterScene.h" 
using namespace CocosDenshion;

USING_NS_CC;

bool Chess::isSoundPlay = true;
bool Chess::isMusicPlay = true;
float Chess::bgVol = 1.0;
int Chess::model = 1;
int Chess::chessColor = 1;
bool Chess::turn = true;
int canPlay = 0;
int can1 = 0;
Animation* animation;/*翻转的动画*/
int dir[8][2] = { { -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 } };
int step;
typedef struct {
	int px;
	int py;
}rePoint;

typedef struct {
	bool tn;
	int lastChess[10][10];
}allBoard;
rePoint AIdrop;
rePoint reverseArr[100];
rePoint canChessArr[100];
allBoard board[100];
int SaveArr[10][10];
int valueArr[10][10] = {
{ 100, -5, 10,  5,  5, 10, -5,100 },
{ -5,-45,  1,  1,  1,  1,-45, -5 },
{ 10,  1,  3,  2,  2,  3,  1, 10 },
{ 5,  1,  2,  1,  1,  2,  1,  5 },
{ 5,  1,  2,  1,  1,  2,  1,  5 },
{ 10,  1,  3,  2,  2,  3,  1, 10 },
{ -5,-45,  1,  1,  1,  1,-45, -5 },
{ 100, -5, 10,  5,  5, 10, -5,100 }
};
Scene* Chess::createScene()
{

	auto scene = Scene::create();

	auto layer = Chess::create();

	scene->addChild(layer);

	return scene;
}

bool Chess::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto rootNode = CSLoader::createNode("scene/ChessScene.csb");
	root = (Layout*)rootNode->getChildByName("chess_panel");						

	returnMenu_btn = (Button*)Helper::seekWidgetByName(root, "return_btn");	
	help_btn = (Button*)Helper::seekWidgetByName(root, "help_btn");
	set_btn = (Button*)Helper::seekWidgetByName(root, "set_btn");
	reback_btn = (Button*)Helper::seekWidgetByName(root, "reback_btn");
	restart_btn = (Button*)Helper::seekWidgetByName(root, "restart_btn");
	save_btn = (Button*)Helper::seekWidgetByName(root, "save_btn");
	reback_btn->setEnabled(true);
	save_btn->setEnabled(false);
	restart_btn->setEnabled(false);

	clock1 = (Sprite*)Helper::seekWidgetByName(root, "clock1");
	clock2 = (Sprite*)Helper::seekWidgetByName(root, "clock2");
	wcount_text = (Text*)Helper::seekWidgetByName(root, "wcount_text");
	bcount_text = (Text*)Helper::seekWidgetByName(root, "bcount_text");
	tips_text = (Text*)Helper::seekWidgetByName(root, "tips_text");

	returnMenu_btn->addTouchEventListener(CC_CALLBACK_2(Chess::returnMenuTouch, this));
	save_btn->addTouchEventListener(CC_CALLBACK_2(Chess::saveGame, this));
	restart_btn->addTouchEventListener(CC_CALLBACK_2(Chess::restartGame, this));
	reback_btn->addTouchEventListener(CC_CALLBACK_2(Chess::reback, this));
	help_btn->addTouchEventListener(CC_CALLBACK_2(Chess::helpTouch, this));
	set_btn->addTouchEventListener(CC_CALLBACK_2(Chess::setTouch, this));

	this->addChild(rootNode, 0);

		
	for (int i = 0; i < 100; i++) {
		reverseArr[i].px = -1;
		reverseArr[i].py = -1;
	}
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++) {
			pos[i][j] = 0;
		}
	}

	
	for (int i = 0; i < 100; i++) {
		canChessArr[i].px = -1;
		canChessArr[i].py = -1;
	}

		
	wTotal = 2;
	bTotal = 2;
	num11 = 0;
	step = 4;
	chess_init();

	return true;
}


void Chess::returnMenuTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = Enter::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);
		break;
	}
}

void Chess::helpTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:	
		auto helpLayer = Help::create();
		this->addChild(helpLayer);
		
		break;
	}
}

void Chess::setTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:		
		auto setLayer = SetLayer::create();
		this->addChild(setLayer);
		break;
	}
}


void Chess::chess_init()
{
	if (model == 0){
		dropChess(5, 4);
		dropChess(5, 5);
		dropChess(4, 5);
		dropChess(4, 4);
	for (int i = 0; i < 100; i++)
		canChessArr[i].px = -1;
	}
	else {		
		readData();
		buildChess();
		restart_btn->setEnabled(true);
		save_btn->setEnabled(true);
		//save_btn->addTouchEventListener(CC_CALLBACK_2(Chess::saveGame, this));
		//restart_btn->addTouchEventListener(CC_CALLBACK_2(Chess::restartGame, this));
		//reback_btn->addTouchEventListener(CC_CALLBACK_2(Chess::reback, this));
	}
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(Chess::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Chess::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, set_btn);
}

void Chess::dropChess(int posx, int posy)
{
	num11++;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pos[i][j] == 3) {
				pos[i][j] = 0;
			}
		}
	}
	for (auto noteVec: posNoteVec)
	{
		if (noteVec != NULL)
			removeChild(noteVec);
	}
	

	int chessColor;
	if (turn) {
		chess_vec[posx][posy] = Sprite::create("chess_10.png");
		chessColor = 1;
	}
	else {
		chess_vec[posx][posy] = Sprite::create("chess_0.png");
		chessColor = -1;
	}
	chess_vec[posx][posy]->setAnchorPoint(Vec2(0, 0));
	chess_vec[posx][posy]->setPositionX(325 + posx * 60);
	chess_vec[posx][posy]->setPositionY(52 + posy * 62);
	chess_vec[posx][posy]->setScale(1.3);

	pos[posx][posy] = chessColor;
	addChild(chess_vec[posx][posy]);
	turn = !turn;	
	reverseChessSearch(posx, posy, false);

	//CCLOG("%d", turn);
	if (chess_scan(turn) || num11<=4) {		
		addPosPic();
		canPlay = 0;
	}
	else
	{
		turn = !turn;
		canPlay++;
		tips_text->setText("No Chess can drop!\nExchange turn!");
		if (model == 2 && turn == false) {
			this->scheduleOnce(schedule_selector(Chess::Move), 2.0f);	
		}
	}	

	if (step > 4) {
		reback_btn->setEnabled(true);
		restart_btn->setEnabled(true);
		save_btn->setEnabled(true);
	}
	
}

	bool Chess::onTouchBegan(Touch* touch, Event  *event)
{
	if (isReversing) {
		return false;
	}
	std::string sss;
	auto loc = touch->getLocation();
	int xx = (loc.x - 327) / 60;
	int yy = (loc.y - 42) / 62;
	if (pos[xx][yy] != 3) {
		tips_text->setText("Please drop again!");
	
		if (isSoundPlay) {
			SimpleAudioEngine::getInstance()->playEffect("sound/lose.wav", false);		
		}
	}
	else {
		//CCLOG("baocun step= %d", step-4);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				board[step-4].lastChess[i][j] = pos[i][j];
			}
		}
		board[step - 4].tn = turn;
		step++;
		
		if (Enter::GameType == 0) {
			dropChess(xx, yy);
		}
		else		
		{
			dropChess(xx, yy);
		
			this->scheduleOnce(schedule_selector(Chess::Move), 2.0f);		
		}

		if (turn) sss = "White ";
		else sss = "Black ";
		tips_text->setText(sss+"Drop");
		if (isSoundPlay)
			SimpleAudioEngine::getInstance()->playEffect("sound/drop.wav", false);
		CountNumber();
	}
	
	countResult();

	
	return true;
}
void Chess::readData()
{
	auto fu = FileUtils::getInstance();
	FILE *f = fopen(fu->fullPathFromRelativeFile("data.txt", fu->getWritablePath()).c_str(), "r");

	for (int i=0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fscanf(f, "%d", &pos[i][j]);
		}
	}
	fscanf(f, "%d", &turn);
	fclose(f);
	
}

void Chess::saveGame(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:	
		auto fu = FileUtils::getInstance();
		FILE *f = fopen(fu->fullPathFromRelativeFile("data.txt", fu->getWritablePath()).c_str(), "w");
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
			{
				fprintf(f, "%d ", pos[i][j]);			}
			fprintf(f, "\n");
		}
		
		fprintf(f, "%d", turn);
		fclose(f);        
		tips_text->setString("Save Succeed!");	
		break;
	}
}

void Chess::onTouchEnded(Touch* touch, Event  *event)
{

	
	//CCLOG("%d %d", xx, yy);
}

bool Chess::chess_scan(bool turn)
{
	bool flag = false;
	int i, j, c;
	int t = 0;
	if (turn) c = -1;
	else c = 1;

	can1 = 0;


	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{

			if (pos[i][j] == c)
			{
				if (searchCanChess(i, j, c))
					flag = true;
			}
		}
	}
	return flag;
}

bool Chess::searchCanChess(int ii, int jj, int c)
{
	int a, b, i, j;
	
	bool canCh = false;
	int flag11 = 0;
	
	int m = 0;
	for (; m < 8; m++)
	{
		i = ii + dir[m][0];
		j = jj + dir[m][1];
		if (pos[i][j] == 0)
		{
			for (int n = 0; n < 8; n++)
			{
				a = i;
				b = j;
				a += dir[n][0];
				b += dir[n][1];
				flag11 = 0;
				while (a >= 0 && a < 10 && b >= 0 && b < 10 && pos[a][b] == c)
				{
					flag11 = 1;
					if (a < i) a--;
					if (a > i) a++;
					if (b > j) b++;
					if (b < j) b--;
				}
				if (a >= 0 && a < 10 && b >= 0 && b < 10 && pos[a][b] == -c && flag11)
				{
					canCh = true;
					if (i >= 0 && j >= 0 && i < 10 && j < 10) {
						//pos[i][9]=3
						pos[i][j] = 3;				
						canChessArr[can1].px = i;
						canChessArr[can1].py = j;
						//CCLOG("canChessArr[%d].px=%d py=%d", can1, i, j);
						can1++;
					}
				}
			}
		}
	}

	return canCh;
}

void Chess::addPosPic()
{

	for (int posx = 0; posx < 10; posx++)
	{
		for (int posy = 0; posy < 10; posy++)
		{
			if (pos[posx][posy] == 3) {
				Sprite* notePic = Sprite::create("ChessmanFocus1.png");
				notePic->setAnchorPoint(Vec2(0, 0));
				notePic->setPositionX(327 + posx * 60);
				notePic->setPositionY(54 + posy * 62);
				notePic->setScale(1.3);

				posNoteVec.pushBack(notePic);
				addChild(notePic, 1);
			}
		}
	}
}


void Chess::reverseChessSearch(int i, int j, bool testModel)
{
	int m, n;
	int a, b;
	int p = 0;
	int c = pos[i][j];
	for (int q = 0; q < 8; q++)
	{
		a = i;
		b = j;
		a += dir[q][0];
		b += dir[q][1];
		while (a >= 0 && a < 10 && b >= 0 && b < 10 && pos[a][b] == -c)
		{
			if (a < i) a--;
			if (a > i) a++;
			if (b > j) b++;
			if (b < j) b--;
		}
		if (a >= 0 && a < 10 && b >= 0 && b < 10 && pos[a][b] == c)
		{
			m = i;
			n = j;
			while (m != a || n != b)
			{
				if (m > a) m--;
				if (m < a) m++;
				if (n > b) n--;
				if (n < b) n++;
				if (m != a || n != b) {
					reverseArr[p].px = m;
					reverseArr[p].py = n;
					p++;
				}
			}
		}
	}
	if (!testModel)
		reverseChess();
}

void Chess::TurnIsReversing(float t) {
	isReversing = false;
}

Sprite* newChess;
void Chess::reverseChess()
{
	if (num11 > 4) {
		isReversing = true;
	}
	int i, m , n;
	for (i = 0; i < 100; i++) {
		if (reverseArr[i].px >= 0) {
			m = reverseArr[i].px;
			n = reverseArr[i].py;
			pos[m][n] = -pos[m][n];
			removeChild(chess_vec[m][n]);
			
			char str[100] = { 0 };
			auto cache = SpriteFrameCache::getInstance();
			cache->addSpriteFramesWithFile("chess.plist");
			
			resultAni = Sprite::createWithSpriteFrameName("chess_0.png"); 
            resultAni->setAnchorPoint(Vec2(0, 0));
			this->addChild(resultAni, 1);
			resultAni->setPosition(Vec2(325 + m * 60, 52 + n * 62));
			/*播放动画*/
			Vector<SpriteFrame *> frames(10);
            if (pos[m][n] == 1){
			for (int i = 0; i<= 10; i++)
			{
				if (pos[m][n] == 1) {
					sprintf(str, "chess_%d.png", i);
				}
				else if (pos[m][n] == -1) {
					sprintf(str, "chess_%d.png", i);
				}
				auto frame1 = cache->getSpriteFrameByName(str);
				frames.pushBack(frame1);
            }}else{
                for (int i = 10; i>= 0; i--)
                {
                    if (pos[m][n] == 1) {
                        sprintf(str, "chess_%d.png", i);
                    }
                    else if (pos[m][n] == -1) {
                        sprintf(str, "chess_%d.png", i);
                    }
                    auto frame1 = cache->getSpriteFrameByName(str);
                    frames.pushBack(frame1);
                }
            }

			animation = Animation::createWithSpriteFrames(frames, 0.2);
			//auto move1 = MoveTo::create(1.5f, Point(100*0.9, 100*0.5));
			//auto squence = Sequence::create(Animate::create(animation),
			//	CallFunc::create(this, callfunc_selector(Chess::TurnIsReversing)),
			//	NULL);
			//actor->runAction(squence);
			//resultAni->runAction(squence);
			resultAni->runAction(Animate::create(animation));
			scheduleOnce(schedule_selector(Chess::TurnIsReversing), 1.0f);/*1秒后执行函数*/
            
            scheduleOnce(schedule_selector(Chess::stopTime), 2.0f);
            stop1 = m;
            stop2 = n;
            stop3 = i;
		}
	}
}

void Chess::stopTime(float t)
{
    this->removeChild(resultAni);
    int m = stop1;
    int n = stop2;
    int i = stop3;
    if (pos[m][n] == 1) {
        chess_vec[m][n] = Sprite::create("chess_10.png");
    }
    else {
        chess_vec[m][n] = Sprite::create("chess_0.png");
    }
    chess_vec[m][n]->setAnchorPoint(Vec2(0, 0));
    chess_vec[m][n]->setPositionX(325 + m * 60);
    chess_vec[m][n]->setPositionY(52 + n * 62);
    chess_vec[m][n]->setScale(1.3);
    
    addChild(chess_vec[m][n]);
    reverseArr[i].px = -1;
    reverseArr[i].py = -1;
}

void Chess::CountNumber()
{
	int i, j;
	wTotal =  bTotal = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (pos[i][j] == 1)
			{
				wTotal++;
			}
			else if (pos[i][j] == -1)
			{
				bTotal++;
			}
		}
	}
	
	std::string str1 = Value(wTotal).asString();
	std::string str2 = Value(bTotal).asString();
	wcount_text->setText(str1);
	bcount_text->setText(str2);
}



void Chess::countResult()
{
	if (wTotal + bTotal == 100 || canPlay >= 2) {
		if (wTotal < bTotal) {
			winPlay(1);
			tips_text->setText("White Win!");
		}
		else if (wTotal > bTotal){
			winPlay(-1);	
			tips_text->setText("Black Win!");
		}
		else
			winPlay(0);	
					  
		_eventDispatcher->removeEventListener(listener);		
		reback_btn->setEnabled(false);
	}
		
}


void Chess::winPlay(int r)
{
	char str[100] = { 0 };
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("result.plist");
	resultAni = Sprite::createWithSpriteFrameName("ResultAll_0.png"); 
	this->addChild(resultAni, 1);
	resultAni->setPosition(Vec2(630, 400));

	Vector<SpriteFrame *> frames(10);
	for (int i = 0; i< 10; i++)
	{
		if (r == 0) {
			sprintf(str, "ResultAll_%d.png", i);
		}
		else if (r == -1) {
			sprintf(str, "ResultWhite_%d.png", i);
		}
		else
		{
			sprintf(str, "ResultBlack_%d.png", i);
		}
		auto frame1 = cache->getSpriteFrameByName(str);
		frames.pushBack(frame1);
	}

	auto animation = Animation::createWithSpriteFrames(frames, 0.2);

	resultAni->runAction(Animate::create(animation));
	
}

void Chess::restartGame(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = SelectModelLayer::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(transition);
		break;
	}
}

void Chess::reback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:	
		if (step > 4) {
			step--;
		}
		else {
			tips_text->setText("you can't reback again!");
			reback_btn->setEnabled(false);
			return;
		}

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				pos[i][j] = board[step - 4].lastChess[i][j];
			}
		}
		turn = board[step - 4].tn;
		buildChess();
	}
}

void Chess::buildChess()
{
	int sum1 = 0;
	int	sum2 = 0;

	for (auto noteVec : posNoteVec)
	{
		if (noteVec != NULL) {
			removeChild(noteVec);
			noteVec = NULL;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (chess_vec[i][j])
			{
				this->removeChild(chess_vec[i][j]);
				chess_vec[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (pos[i][j] == 1) {
				sum1++;
				chess_vec[i][j] = Sprite::create("chess_10.png");
				chess_vec[i][j]->setAnchorPoint(Vec2(0, 0));
				chess_vec[i][j]->setPositionX(325 + i * 60);
				chess_vec[i][j]->setPositionY(52 + j * 62);
				chess_vec[i][j]->setScale(1.3);
				this->addChild(chess_vec[i][j]);
			}
			else if (pos[i][j] == -1) {
				sum2++;
				chess_vec[i][j] = Sprite::create("chess_0.png");
				chess_vec[i][j]->setAnchorPoint(Vec2(0, 0));
				chess_vec[i][j]->setPositionX(325 + i * 60);
				chess_vec[i][j]->setPositionY(52 + j * 62);
				chess_vec[i][j]->setScale(1.3);
				this->addChild(chess_vec[i][j]);
			}
		}
	}


	addPosPic();
	std::string sss;
	if (turn) sss = "White ";
	else sss = "Black ";
	tips_text->setText(sss + "Drop");
	wTotal = sum1;
	bTotal = sum2;
	std::string str1 = Value(wTotal).asString();
	std::string str2 = Value(bTotal).asString();
	wcount_text->setText(str1);
	bcount_text->setText(str2);
}


void Chess::AIdropChess()
{
	AIsearch(3, turn);


	if (pos[AIdrop.px][AIdrop.py] == 1 || pos[AIdrop.px][AIdrop.py] == -1)
	{
		chess_scan(turn);
		AIdrop.px = canChessArr[0].px;
		AIdrop.py = canChessArr[0].py;
		for (int i = 0; canChessArr[i].px != -1; i++)
		{
			canChessArr[i].px = -1;
			canChessArr[i].py = -1;
		}
	}
	
	dropChess(AIdrop.px, AIdrop.py);
}


int Chess::AIsearch(int depth, bool turn)
{
	int value, bestValue;
	int copyArr[10][10];
	if (depth <= 0) 	
	{
		return Evaluate(pos, turn);
	}
	if (!turn) { bestValue = -10000; }
	else
		bestValue = 10000;

	chess_scan(turn);

	int i, j;
	int ii, jj;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			copyArr[i][j] = pos[i][j];

	for (i = 0; canChessArr[i].px != -1; i++)
	{
		
		int xx = canChessArr[i].px;
		int yy = canChessArr[i].py;
		canChessArr[i].px = -1;
		canChessArr[i].py = -1;
		pos[xx][yy] = turn ? 1 : -1;

		reverseChessSearch(xx, yy, true);
		pos[xx][yy] = -pos[xx][yy];

		for (int p = 0; reverseArr[p].px != -1; p++)
		{
			pos[reverseArr[p].px][reverseArr[p].py] = -pos[reverseArr[p].px][reverseArr[p].py];
			reverseArr[p].px = -1;
			reverseArr[p].py = -1;
		}

		value = AIsearch(depth - 1, !turn);		
		
		for (ii = 0; ii < 10; ii++)
			for (jj = 0; jj < 10; jj++)
				pos[ii][jj] = copyArr[ii][jj];
		if (!turn)
		{
			if (value > bestValue) {
				bestValue = value;
				if (depth == 3) {
					AIdrop.px = xx;
					AIdrop.py = yy;
				}
			}
		}
		else {			
			if (value < bestValue) {
				bestValue = value;
			}
		}

	}

	return bestValue;
}

int Chess::Evaluate(int image[10][10], bool turn)
{
	int bestValue = 0;
	int c;
	if (turn) {
		c = 1;
	}
	else
	{
		c = -1;
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (image[i][j] == c)
			{
				bestValue += valueArr[i][j];
			}
			else if(image[i][j] == -c) {
				bestValue -= valueArr[i][j];
			}
		}
	}
	return bestValue;
}

void Chess::Move(float dt) {

	AIdropChess(); 
}
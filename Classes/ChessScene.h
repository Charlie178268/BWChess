#ifndef __CHESSSCENE_SCENE_H__
#define __CHESSSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
#include "ChessLogic.h"
#include "SelectModelLayer.h"
#include "EnterScene.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class Chess : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Chess);
    void chess_init();

	static bool isMusicPlay;//判断能否播放背景音乐
	static bool isSoundPlay;//判断能否播放音效
	static float bgVol;//设置音量大小0-1
	static int model;//选择模式，0是新开游戏，1是新开游戏
	static int chessColor;//选择先手棋子颜色,1是白棋，2是黑棋
	
	
	Sprite* chess_vec[10][10];//存棋子的数组
    int pos[10][10];//存坐标的数组
	
	Vector<Sprite*> posNoteVec;
	static bool turn;//下棋的顺序
	bool isReversing = false;
private:
	void returnMenuTouch(Ref *pSender, Widget::TouchEventType type);
	void helpTouch(Ref *pSender, Widget::TouchEventType type);
	void setTouch(Ref *pSender, Widget::TouchEventType type);
	
	
    void dropChess(int posx, int posy);
	void addPosPic();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool chess_scan(bool turn);//扫描能下棋的地方
	bool searchCanChess(int i, int j, int c);
	void reverseChessSearch(int i, int j, bool testModel);//把i,j到a,b之间的棋子下标用数组存放，方便落子之后的翻转
	void reverseChess();//翻转棋子
	void CountNumber();
	void winPlay(int r);
	void countResult();//判断胜负
	void readData();//读取数据
	void saveGame(Ref *pSender, Widget::TouchEventType type);//保存棋局
	void restartGame(Ref *pSender, Widget::TouchEventType type);//重新开始
	void reback(Ref *pSender, Widget::TouchEventType type);//悔棋
	void buildChess();//重建棋盘
    void stopTime(float t);
	void TurnIsReversing(float t);/*改变正在翻转棋子变量*/


	//人机对战函数
	void Move(float dt);
	void AIdropChess();//AI落子
	int AIsearch(int depth, bool turn);//搜索AI最佳落子坐标，返回落子的得分
	int Evaluate(int image[10][10], bool turn);//估值函数

	Layout* root; 
	Button* help_btn;
	Button* set_btn;
	Button* returnMenu_btn;
	Button* reback_btn;
	Button* restart_btn;
	Button* save_btn;
	EventListenerTouchOneByOne* listener;
	Sprite* clock1;//玩家一的计时器
	Sprite* clock2;//玩家二的计时器
	Text* wcount_text;//白子的数目显示
	Text* bcount_text;//黑子的数目显示
	Text* tips_text;//提示框
	Sprite* resultAni;

	int wTotal;//白棋数目
	int bTotal;
	int num11;//下子总数
    int stop1;
    int stop2;
    int stop3;
};

#endif // __CHESSSCENE_SCENE_H__


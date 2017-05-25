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

	static bool isMusicPlay;//�ж��ܷ񲥷ű�������
	static bool isSoundPlay;//�ж��ܷ񲥷���Ч
	static float bgVol;//����������С0-1
	static int model;//ѡ��ģʽ��0���¿���Ϸ��1���¿���Ϸ
	static int chessColor;//ѡ������������ɫ,1�ǰ��壬2�Ǻ���
	
	
	Sprite* chess_vec[10][10];//�����ӵ�����
    int pos[10][10];//�����������
	
	Vector<Sprite*> posNoteVec;
	static bool turn;//�����˳��
	bool isReversing = false;
private:
	void returnMenuTouch(Ref *pSender, Widget::TouchEventType type);
	void helpTouch(Ref *pSender, Widget::TouchEventType type);
	void setTouch(Ref *pSender, Widget::TouchEventType type);
	
	
    void dropChess(int posx, int posy);
	void addPosPic();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool chess_scan(bool turn);//ɨ��������ĵط�
	bool searchCanChess(int i, int j, int c);
	void reverseChessSearch(int i, int j, bool testModel);//��i,j��a,b֮��������±��������ţ���������֮��ķ�ת
	void reverseChess();//��ת����
	void CountNumber();
	void winPlay(int r);
	void countResult();//�ж�ʤ��
	void readData();//��ȡ����
	void saveGame(Ref *pSender, Widget::TouchEventType type);//�������
	void restartGame(Ref *pSender, Widget::TouchEventType type);//���¿�ʼ
	void reback(Ref *pSender, Widget::TouchEventType type);//����
	void buildChess();//�ؽ�����
    void stopTime(float t);
	void TurnIsReversing(float t);/*�ı����ڷ�ת���ӱ���*/


	//�˻���ս����
	void Move(float dt);
	void AIdropChess();//AI����
	int AIsearch(int depth, bool turn);//����AI����������꣬�������ӵĵ÷�
	int Evaluate(int image[10][10], bool turn);//��ֵ����

	Layout* root; 
	Button* help_btn;
	Button* set_btn;
	Button* returnMenu_btn;
	Button* reback_btn;
	Button* restart_btn;
	Button* save_btn;
	EventListenerTouchOneByOne* listener;
	Sprite* clock1;//���һ�ļ�ʱ��
	Sprite* clock2;//��Ҷ��ļ�ʱ��
	Text* wcount_text;//���ӵ���Ŀ��ʾ
	Text* bcount_text;//���ӵ���Ŀ��ʾ
	Text* tips_text;//��ʾ��
	Sprite* resultAni;

	int wTotal;//������Ŀ
	int bTotal;
	int num11;//��������
    int stop1;
    int stop2;
    int stop3;
};

#endif // __CHESSSCENE_SCENE_H__


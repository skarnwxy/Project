#pragma once
#include "GameMenuPanel.h"
#include "GameMenuPanel2.h"
#include "GameMenuBackground.h"

#include "TankEntry.h" // ���
#include "Player.h" // ��ҵ���Ϊ����
#include "Wall.h" // ǽ
#include "Bullet.h" // �ӵ�
#include "Bot.h" // ������
#include "GameMap.h" // ��ͼ

#include "KeyMenuPlayer01.h" // 
#include "KeyMenuPlayer02.h"

// ��ǰ��Ϸ�����Ľ׶�
enum EGameType {
	EGameTypeMenu = 0,          // ѡ��׶�
	EGameTypeOne2BotMenu,       // �˻���ս�˵��׶�
	EGameTypeOne2Bot,			// �˻���ս
	EGameTypeOne2BotEnd,        // �˻���ս����
	EGameTypeOne2OneMenu,       // ˫�˴�ս�˵��׶�
	EGameTypeOne2One,           // ˫�˴�ս
	EGameTypeOne2OneEnd,        // ˫�˴�ս����
	EGameTypeCount,             // ���߸��׶�
};

class CGame
{
private:
	// ����
	HWND m_hWnd;

	// ��1����������Ϸ��ʼ������-----------------------------
	// �٣�������Ϸ����
	// �ڣ���ʼ����ͼ
	// �ۣ�����λ��
	bool GameInit();
	bool GameInitMenu();				// ��Ϸ��ʼ����ѡ��׶�
	bool GameInitOne2BotMenu();			// ��Ϸ��ʼ�����˻���ս�˵��׶�
	bool GameInitOne2Bot();				// ��Ϸ��ʼ�����˻���ս
	bool GameInitOne2BotEnd();			// ��Ϸ��ʼ�����˻���ս����
	bool GameInitOne2OneMenu();			// ��Ϸ��ʼ����˫�˴�ս�˵��׶�
	bool GameInitOne2One();				// ��Ϸ��ʼ����˫�˴�ս
	bool GameInitOne2OneEnd();			// ��Ϸ��ʼ����˫�˴�ս����

	// ��������������ָ��������
	bool (CGame::*m_initFunc[EGameTypeCount])() = {
		&CGame::GameInitMenu,			// ѡ��׶�
		&CGame::GameInitOne2BotMenu,	// �˻���ս������ʾ
		&CGame::GameInitOne2Bot,		// �˻���ս
		&CGame::GameInitOne2BotEnd,		// �˻���ս����
		&CGame::GameInitOne2OneMenu,	// ˫�˴�ս������ʾ
		&CGame::GameInitOne2One,		// ˫�˴�ս
		&CGame::GameInitOne2OneEnd,		// ˫�˴�ս����
	};

	// ��2����������Ϸ�߼�������-----------------------------
	// �٣�ά���ӵ�״̬
	// �ڣ�ά��������AI���Զ��ƶ����Զ������ӵ�
	// �ۣ�ά�����̹�˵�״̬
	void GameRunLogic();
	void GameRunLogicOnMenu();			// ��Ϸ�߼�����ѡ��׶�
	void GameRunLogicOnOne2BotMenu();	// ��Ϸ�߼������˻���ս�˵��׶�
	void GameRunLogicOnOne2Bot();		// ��Ϸ�߼������˻���ս
	void GameRunLogicOnOne2BotEnd();	// ��Ϸ�߼������˻���ս����
	void GameRunLogicOnOne2OneMenu();	// ��Ϸ�߼�����˫�˴�ս�˵��׶�
	void GameRunLogicOnOne2One();		// ��Ϸ�߼�����˫�˴�ս
	void GameRunLogicOnOne2OneEnd();	// ��Ϸ�߼�����˫�˴�ս����

	// ��������������ָ��������
	void (CGame::*m_logicFunc[EGameTypeCount])() = {
		&CGame::GameRunLogicOnMenu,			// ѡ��׶�
		&CGame::GameRunLogicOnOne2BotMenu,	// �˻���ս������ʾ
		&CGame::GameRunLogicOnOne2Bot,		// �˻���ս
		&CGame::GameRunLogicOnOne2BotEnd,	// �˻���ս����
		&CGame::GameRunLogicOnOne2OneMenu,	// ˫�˴�ս������ʾ
		&CGame::GameRunLogicOnOne2One,		// ˫�˴�ս
		&CGame::GameRunLogicOnOne2OneEnd,	// ˫�˴�ս����
	};

	// ��3������Ϸ��ͼ�������ӻ滭��Ϸ�еĶ���-----------------------------
	void GameRunDraw();
	void GameRunDrawOnMenu(Graphics &gh);			// ��Ϸ�߼�����ѡ��׶�
	void GameRunDrawOnOne2BotMeun(Graphics &gh);	// ��Ϸ�߼������˻���ս�˵��׶�
	void GameRunDrawOnOne2Bot(Graphics &gh);		// ��Ϸ�߼������˻���ս
	void GameRunDrawOnOne2BotEnd(Graphics &gh);		// ��Ϸ�߼������˻���ս����
	void GameRunDrawOnOne2OneMenu(Graphics &gh);	// ��Ϸ�߼�����˫�˴�ս�˵��׶�
	void GameRunDrawOnOne2One(Graphics &gh);		// ��Ϸ�߼�����˫�˴�ս
	void GameRunDrawOnOne2OneEnd(Graphics &gh);		// ��Ϸ�߼�����˫�˴�ս����

	// ��������������ָ��������
	void (CGame::*m_DrawFunc[EGameTypeCount])(Graphics &) = {
		&CGame::GameRunDrawOnMenu,			// ѡ��׶�
		&CGame::GameRunDrawOnOne2BotMeun,	// �˻���ս������ʾ
		&CGame::GameRunDrawOnOne2Bot,		// �˻���ս
		&CGame::GameRunDrawOnOne2BotEnd,	// �˻���ս����
		&CGame::GameRunDrawOnOne2OneMenu,	// ˫�˴�ս������ʾ
		&CGame::GameRunDrawOnOne2One,		// ˫�˴�ս
		&CGame::GameRunDrawOnOne2OneEnd,	// ˫�˴�ս����
	};

	// ��4��--------------------------------------------------------
	// !!!�������������������ƶ��ӵ���ά���ӵ����й켣�������Զ�Ѱ·���Ƽ������Ϸ֡��
	void RemoveTimeoutBullets();	// �Ƴ���ʱ�ӵ�������Ӧ��̹��װ��
	void ProcessHitBullets();		// ά���ӵ������м���ײ����
	void AI();						// ά�����Ե��Զ�Ѱ·����
	void DrawFps(Graphics &gh);		// ���fps

	// ��5��˽�г�Ա����-----------------------------------------------
	int m_fps{ 0 };						// ��¼��Ϸÿ�����֡
	EGameType m_eStep{ EGameTypeMenu }; // ��ǰ�Ľ׶Σ��˵�ѡ��Ľ׶�
	CPlayer m_player01;					// ��Ҷ���1
	CPlayer m_player02;					// ��Ҷ���2
	CBot m_bot;							// �����ˣ��˻���սʱ�õ�
	std::list<CBullet> m_lstBullets;	// �ӵ�
	CGameMap m_map{ 10, 10, 780, 580 }; // ��ͼ����
	CGameMenuPanel m_menuSelect;		// ��ʼ�˵�
	CGameMenuBackground m_menu;			// ��ʼ�˵�����ͼ
	CGameMenuPanel2 m_menuBackup;		// ���ز˵�
	CKeyMenuPlayer01 m_keymenu01;		// ��ʾ�����Ĳ˵�
	CKeyMenuPlayer02 m_keymenu02;		

	/*//-----------------------------
	// !!!��Ϸ��ͼ����
	// ����滭��Ϸ�еĶ���
	void GameRunDraw();
	// !!!��Ϸ�߼�����
	// (1)ά���ӵ�״̬
	// (2)ά��������AI���Զ��ƶ����Զ������ӵ�
	// (3)ά�����̹�˵�״̬
	void GameFirstRunLogic();
	void GameSecondRunLogic();

	// !!!����滭��Ϸ�еĶ���
	CGameMenuPanel m_menuSelect;
	CGameMenuBackground m_menu;

	// ���fps
	void DrawFps(Graphics &gh);
	// ��¼��Ϸÿ�����֡
	int m_fps{ 0 };

	//---------------------------------
	// ����̹������ӵ���
	// ��Ҷ���1
	//srand((int)time(0)); // ���������������
	CPlayer m_player01{rand()%800, rand()%600, _T("tank_player1.png")};
	// ��Ҷ���2
	CPlayer m_player02{rand()%800, rand()%600, _T("tank_player2.png")};
	// �����ˣ��˻���սʱ�õ�
	CBot m_bot{300, 200, _T("tank_bot.png")};
	// �ӵ�
	std::list<CBullet> m_lstBullets;

	//---------------------------------
	// ��ͼ����
	CGameMap m_map{10, 10, 780, 580};

	//---------------------------------
	// ��ʼ��̹�˵�λ�ã���̹�˵�λ�÷��ڿյ���
	bool GameInitOne2Bot(); // ��Ϸ��ʼ�����˻���ս*/
public:
	//���캯��
	CGame();
	~CGame();

	// ����������ڵľ��
	void SetHandle(HWND hWnd); 
	// ������Ϸ֡
	bool EnterFrame(DWORD deTime); 

	// !!!�����Ӧ����
	// ��������ƶ��¼�
	void OnMouseMove(UINT nFlags, CPoint point);
	// �������̧���¼�
	void OnLButtonUp(UINT nFlags, CPoint point); 

	// ���õ�ǰ��Ϸ�����Ľ׶Σ������ݲ����ʼ��
	void SetStep(/*CGame::*/EGameType step);

};


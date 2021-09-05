#pragma once
#include "GameMenuPanel.h"
#include "GameMenuPanel2.h"
#include "GameMenuBackground.h"

#include "TankEntry.h" // 入口
#include "Player.h" // 玩家的行为特征
#include "Wall.h" // 墙
#include "Bullet.h" // 子弹
#include "Bot.h" // 机器人
#include "GameMap.h" // 地图

#include "KeyMenuPlayer01.h" // 
#include "KeyMenuPlayer02.h"

// 当前游戏所处的阶段
enum EGameType {
	EGameTypeMenu = 0,          // 选择阶段
	EGameTypeOne2BotMenu,       // 人机大战菜单阶段
	EGameTypeOne2Bot,			// 人机大战
	EGameTypeOne2BotEnd,        // 人机大战结束
	EGameTypeOne2OneMenu,       // 双人大战菜单阶段
	EGameTypeOne2One,           // 双人大战
	EGameTypeOne2OneEnd,        // 双人大战结束
	EGameTypeCount,             // 有七个阶段
};

class CGame
{
private:
	// 窗口
	HWND m_hWnd;

	// （1）：声明游戏初始化方法-----------------------------
	// ①：生成游戏对象
	// ②：初始化地图
	// ③：对象位置
	bool GameInit();
	bool GameInitMenu();				// 游戏初始化：选择阶段
	bool GameInitOne2BotMenu();			// 游戏初始化：人机大战菜单阶段
	bool GameInitOne2Bot();				// 游戏初始化：人机大战
	bool GameInitOne2BotEnd();			// 游戏初始化：人机大战结束
	bool GameInitOne2OneMenu();			// 游戏初始化：双人大战菜单阶段
	bool GameInitOne2One();				// 游戏初始化：双人大战
	bool GameInitOne2OneEnd();			// 游戏初始化：双人大战结束

	// 将上述方法放入指针数组中
	bool (CGame::*m_initFunc[EGameTypeCount])() = {
		&CGame::GameInitMenu,			// 选择阶段
		&CGame::GameInitOne2BotMenu,	// 人机大战键盘提示
		&CGame::GameInitOne2Bot,		// 人机大战
		&CGame::GameInitOne2BotEnd,		// 人机大战结束
		&CGame::GameInitOne2OneMenu,	// 双人大战键盘提示
		&CGame::GameInitOne2One,		// 双人大战
		&CGame::GameInitOne2OneEnd,		// 双人大战结束
	};

	// （2）：声明游戏逻辑处理方法-----------------------------
	// ①：维护子弹状态
	// ②：维护机器人AI的自动移动，自动发射子弹
	// ③：维护玩家坦克的状态
	void GameRunLogic();
	void GameRunLogicOnMenu();			// 游戏逻辑处理：选择阶段
	void GameRunLogicOnOne2BotMenu();	// 游戏逻辑处理：人机大战菜单阶段
	void GameRunLogicOnOne2Bot();		// 游戏逻辑处理：人机大战
	void GameRunLogicOnOne2BotEnd();	// 游戏逻辑处理：人机大战结束
	void GameRunLogicOnOne2OneMenu();	// 游戏逻辑处理：双人大战菜单阶段
	void GameRunLogicOnOne2One();		// 游戏逻辑处理：双人大战
	void GameRunLogicOnOne2OneEnd();	// 游戏逻辑处理：双人大战结束

	// 将上述方法放入指针数组中
	void (CGame::*m_logicFunc[EGameTypeCount])() = {
		&CGame::GameRunLogicOnMenu,			// 选择阶段
		&CGame::GameRunLogicOnOne2BotMenu,	// 人机大战键盘提示
		&CGame::GameRunLogicOnOne2Bot,		// 人机大战
		&CGame::GameRunLogicOnOne2BotEnd,	// 人机大战结束
		&CGame::GameRunLogicOnOne2OneMenu,	// 双人大战键盘提示
		&CGame::GameRunLogicOnOne2One,		// 双人大战
		&CGame::GameRunLogicOnOne2OneEnd,	// 双人大战结束
	};

	// （3）：游戏绘图处理，复杂绘画游戏中的对象-----------------------------
	void GameRunDraw();
	void GameRunDrawOnMenu(Graphics &gh);			// 游戏逻辑处理：选择阶段
	void GameRunDrawOnOne2BotMeun(Graphics &gh);	// 游戏逻辑处理：人机大战菜单阶段
	void GameRunDrawOnOne2Bot(Graphics &gh);		// 游戏逻辑处理：人机大战
	void GameRunDrawOnOne2BotEnd(Graphics &gh);		// 游戏逻辑处理：人机大战结束
	void GameRunDrawOnOne2OneMenu(Graphics &gh);	// 游戏逻辑处理：双人大战菜单阶段
	void GameRunDrawOnOne2One(Graphics &gh);		// 游戏逻辑处理：双人大战
	void GameRunDrawOnOne2OneEnd(Graphics &gh);		// 游戏逻辑处理：双人大战结束

	// 将上述方法放入指针数组中
	void (CGame::*m_DrawFunc[EGameTypeCount])(Graphics &) = {
		&CGame::GameRunDrawOnMenu,			// 选择阶段
		&CGame::GameRunDrawOnOne2BotMeun,	// 人机大战键盘提示
		&CGame::GameRunDrawOnOne2Bot,		// 人机大战
		&CGame::GameRunDrawOnOne2BotEnd,	// 人机大战结束
		&CGame::GameRunDrawOnOne2OneMenu,	// 双人大战键盘提示
		&CGame::GameRunDrawOnOne2One,		// 双人大战
		&CGame::GameRunDrawOnOne2OneEnd,	// 双人大战结束
	};

	// （4）--------------------------------------------------------
	// !!!声明辅助方法，包括移动子弹、维护子弹运行轨迹、电脑自动寻路共计即输出游戏帧数
	void RemoveTimeoutBullets();	// 移除超时子弹并给对应的坦克装弹
	void ProcessHitBullets();		// 维护子弹的运行及碰撞处理
	void AI();						// 维护电脑的自动寻路攻击
	void DrawFps(Graphics &gh);		// 输出fps

	// （5）私有成员变量-----------------------------------------------
	int m_fps{ 0 };						// 记录游戏每秒多少帧
	EGameType m_eStep{ EGameTypeMenu }; // 当前的阶段：菜单选择的阶段
	CPlayer m_player01;					// 玩家对象1
	CPlayer m_player02;					// 玩家对象2
	CBot m_bot;							// 机器人，人机大战时用到
	std::list<CBullet> m_lstBullets;	// 子弹
	CGameMap m_map{ 10, 10, 780, 580 }; // 地图对象
	CGameMenuPanel m_menuSelect;		// 开始菜单
	CGameMenuBackground m_menu;			// 开始菜单背景图
	CGameMenuPanel2 m_menuBackup;		// 返回菜单
	CKeyMenuPlayer01 m_keymenu01;		// 提示按键的菜单
	CKeyMenuPlayer02 m_keymenu02;		

	/*//-----------------------------
	// !!!游戏绘图处理
	// 负责绘画游戏中的对象
	void GameRunDraw();
	// !!!游戏逻辑处理
	// (1)维护子弹状态
	// (2)维护机器人AI的自动移动，自动发射子弹
	// (3)维护玩家坦克的状态
	void GameFirstRunLogic();
	void GameSecondRunLogic();

	// !!!负责绘画游戏中的对象
	CGameMenuPanel m_menuSelect;
	CGameMenuBackground m_menu;

	// 输出fps
	void DrawFps(Graphics &gh);
	// 记录游戏每秒多少帧
	int m_fps{ 0 };

	//---------------------------------
	// 声明坦克类和子弹类
	// 玩家对象1
	//srand((int)time(0)); // 生成随机数的种子
	CPlayer m_player01{rand()%800, rand()%600, _T("tank_player1.png")};
	// 玩家对象2
	CPlayer m_player02{rand()%800, rand()%600, _T("tank_player2.png")};
	// 机器人，人机大战时用到
	CBot m_bot{300, 200, _T("tank_bot.png")};
	// 子弹
	std::list<CBullet> m_lstBullets;

	//---------------------------------
	// 地图对象
	CGameMap m_map{10, 10, 780, 580};

	//---------------------------------
	// 初始化坦克的位置，将坦克的位置放在空地上
	bool GameInitOne2Bot(); // 游戏初始化：人机大战*/
public:
	//构造函数
	CGame();
	~CGame();

	// 设置输出窗口的句柄
	void SetHandle(HWND hWnd); 
	// 进入游戏帧
	bool EnterFrame(DWORD deTime); 

	// !!!鼠标响应函数
	// 处理鼠标移动事件
	void OnMouseMove(UINT nFlags, CPoint point);
	// 处理左键抬起事件
	void OnLButtonUp(UINT nFlags, CPoint point); 

	// 设置当前游戏所处的阶段，并根据步骤初始化
	void SetStep(/*CGame::*/EGameType step);

};


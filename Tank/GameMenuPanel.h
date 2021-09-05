#pragma once
#include <tuple>
#include <vector>
#include "GameEntry.h"

using namespace std;
class CGame;

class CGameMenuPanel :public CGameEntryMoveable
{
public:
	// 成员变量
	CGame* m_pParent{ nullptr };
	RectF m_rect{ 0, 0, 800, 600 }; // 画自己的范围
	Image* m_imgBackground; // 背景图
	struct {
		vector<tuple<Image*, RectF>>vImgInfoPtr;
		int index;
	}m_menuItems[2];

public:
	CGameMenuPanel();
	~CGameMenuPanel();

	// 添加菜单项
	void AddMenu();
	// 存放一个CGame类的指针
	void SetParent(CGame* g);
	// 画自己
	virtual void Draw(Graphics &gh)const;
	// 处理鼠标移动事件
	void OnMouseMove(UINT nFlags, CPoint point);
	// 处理鼠标左键抬起事件
	void OnLButtonUp(UINT nFlags, CPoint point);
};


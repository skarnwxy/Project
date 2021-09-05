#pragma once
#include <tuple>
#include <vector>
#include "GameEntry.h"

using namespace std;
class CGame;

class CGameMenuPanel :public CGameEntryMoveable
{
public:
	// ��Ա����
	CGame* m_pParent{ nullptr };
	RectF m_rect{ 0, 0, 800, 600 }; // ���Լ��ķ�Χ
	Image* m_imgBackground; // ����ͼ
	struct {
		vector<tuple<Image*, RectF>>vImgInfoPtr;
		int index;
	}m_menuItems[2];

public:
	CGameMenuPanel();
	~CGameMenuPanel();

	// ��Ӳ˵���
	void AddMenu();
	// ���һ��CGame���ָ��
	void SetParent(CGame* g);
	// ���Լ�
	virtual void Draw(Graphics &gh)const;
	// ��������ƶ��¼�
	void OnMouseMove(UINT nFlags, CPoint point);
	// ����������̧���¼�
	void OnLButtonUp(UINT nFlags, CPoint point);
};


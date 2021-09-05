#pragma once
#include "GameEntry.h"

class CGame;
class CGameMenuBackground :public CGameEntryMoveable
{
public:
	CGameMenuBackground();
	~CGameMenuBackground();
	
	void AddBackground();
	void SetParent(CGame *g);
	virtual void Draw(Graphics &gh) const;

	CGame* m_pParent{nullptr};
	RectF m_rect{0,0,800,600};
	Image* m_imagBackground;
};


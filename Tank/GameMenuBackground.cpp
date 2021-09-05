#include "pch.h"
#include "GameMenuBackground.h"
#include "Game.h"

CGameMenuBackground::CGameMenuBackground() {
	/*GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);*/

	m_imagBackground = Image::FromFile(_T("menu_background.png"));
}

CGameMenuBackground::~CGameMenuBackground() {
	delete m_imagBackground; m_imagBackground = NULL;
}

// ÃÌº”±≥æ∞
void CGameMenuBackground::AddBackground() {
	// º”‘ÿ±≥æ∞Õº∆¨
	//m_imagBackground = Image::FromFile(_T("menu_background.png"));
}
void CGameMenuBackground::SetParent(CGame *g) {
	m_pParent = g;
}

void CGameMenuBackground::Draw(Graphics &gh) const{
	gh.DrawImage(m_imagBackground, m_rect);
}

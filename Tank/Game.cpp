#include "pch.h"
#include "Game.h"
//#include <algorithm>

#define KEYDOWN(vk) (GetAsyncKeyState(vk)& 0x8000)

CGame::CGame() {
	//GameInitOne2Bot(); // ��ʼ���˻���ս��Ϸ
	m_menuSelect.m_pParent = this;		// ���ò˵�ѡ����ָ��ǰ����
	m_menuBackup.m_pParent = this;		// ���ò˵�������ָ��ǰ����
}

CGame::~CGame() {

}

// --------------ʵ��Ϊ����ṩ�ķ���-------------------
// �٣�����������ڵľ��
void CGame::SetHandle(HWND hWnd) {
	m_hWnd = hWnd;
}
// �ڣ���ȥ��Ϸ֡
bool CGame::EnterFrame(DWORD deTime) {
	// !!!�����߼�������
	GameRunLogic();

	// !!!���û�ͼ����
	GameRunDraw();

	return false;
}
// �ۣ���������ƶ��¼�
void CGame::OnMouseMove(UINT nFlags, CPoint point) {
	// ѡ��׶�
	if (m_eStep == EGameTypeMenu) {
		m_menuSelect.OnMouseMove(nFlags, point);		// ѡ����Ϸ������
	}
	else {
		m_menuBackup.OnMouseMove(nFlags, point);		// �������˵�
	}
}
// �ܣ��������̧���¼�
void CGame::OnLButtonUp(UINT nFlags, CPoint point) {
	// ѡ��׶�
	if (m_eStep == EGameTypeMenu) {
		m_menuSelect.OnLButtonUp(nFlags, point);		// ѡ����Ϸ����
	}
	else {
		m_menuSelect.OnLButtonUp(nFlags, point);		// �������˵�
	}
}
// �ݣ����õ�ǰ��Ϸ�����Ľ׶Σ����ݲ����ʼ��
void CGame::SetStep(EGameType step) {
	m_eStep = step;
	GameInit();											// ���ó�ʼ������
}

// -------------ʵ�ֳ�ʼ������----------------
// ������Ϸ���󡢳�ʼ����ͼ�Ͷ����λ��
// �٣���ʼ��
bool CGame::GameInit() {
	srand(GetTickCount());								// ��ʼ�������������
	return (this->*m_initFunc[m_eStep])();				// ���ݲ�ͬ�׶ε��ò�ͬ�Ĵ�����
}
// �ڣ���Ϸ��ʼ����ѡ��׶�
bool CGame::GameInitMenu() {
	return true;
}
// �ۣ���Ϸ��ʼ�����˻���ս�˵��׶�
bool CGame::GameInitOne2BotMenu() {
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	PointF pt;
	pt.X = rc.left + (rc.right - rc.left) / 2.0f;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;

	m_keymenu01.SetCenterPoint(pt);						// �����˻���սKeyMenuλ��Ϊ��Ļ���м�
	m_keymenu01.SetStop(false);							// ����"��"ֹͣ���Ŷ���

	return true;
}
// �ܣ���Ϸ��ʼ�����˻���ս
bool CGame::GameInitOne2Bot() {
	for ( ; ; ) {
		m_map.LoadMap(); // �����ͼ
		// ���һ
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));	 // �������һλ��
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {			 // ������ҵ�ͼ�еĿյ�
				AfxMessageBox(_T("����player01λ��ʧ��"));			 // ��ʾ����λ��ʧ��
			}
			else {
				// �������һ�����ĵ㣬�����һ���ڵ�ͼ���ӵ����м�λ��
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		// ������ս�����Կ��Ƶ�̹�ˣ�
		{
			m_bot = CBot(0, 0, _T("tank_bot.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("����botλ��ʧ��"));
			}
			else {
				m_bot.SetCenterPoint(ptCenter);
			}

		}
		// �ӵ�
		m_lstBullets.clear();

		// �ж��Ƿ�Ϸ�
		{
			// ��ȡ�����˺����һ���ڵ�λ��
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				AfxMessageBox(_T("��ȡ̹��λ�÷�������"));
				break;
				//goto __Init_End;
			}
			// �ж����һ�ͻ������Ƿ���ͨ�������ͨ���޷�������Ϸ
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty()) {
				break;
				//goto __Init_End;
			}
		}
	}
//__Init_End:
	return true;
}
// �ݣ���Ϸ��ʼ�����˻���ս����
bool CGame::GameInitOne2BotEnd() {
	return true;
}
// �ޣ���Ϸ��ʼ����˫�˴�ս�˵��׶�
bool CGame::GameInitOne2OneMenu() {
	// ����������ҵ�KeyMenuλ�ã���Ļ���м�
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	PointF pt;
	pt.X = rc.left + m_keymenu01.GetRect().Width / 2.0f + 100;
	pt.Y = rc.top + (rc.bottom - rc.top)/2.0f;
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);

	pt.X = rc.left + m_keymenu02.GetRect().Width / 2.0f + 100;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;
	m_keymenu02.SetCenterPoint(pt);
	m_keymenu02.SetStop(false);

	return true;
}
// �ߣ���Ϸ��ʼ����˫�˴�ս
bool CGame::GameInitOne2One() {
	for (; ; ) {
		m_map.LoadMap();
		// ���һ
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("����player01λ��ʧ��"));	
			}
			else {
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		// ������ս�����Կ��Ƶ�̹�ˣ�
		{
			m_player02 = CPlayer(0, 0, _T("tank_player2.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("����player02λ��ʧ��"));
			}
			else {
				m_player02.SetCenterPoint(ptCenter);
			}
		}
		// �ӵ�
		m_lstBullets.clear();

		// �ж��Ƿ�Ϸ�
		{
			// ��ȡ���һ����Ҷ����ڵ�λ��
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_player02, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				AfxMessageBox(_T("��ȡ̹��λ�÷�������"));
				break;
			}
			// �ж����һ����Ҷ�����ͨ�������ͨ���޷�������Ϸ
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty()) {
				break;
			}
		}
	}
	return true;
}
// �ࣺ��Ϸ��ʼ����˫�˴�ս����
bool CGame::GameInitOne2OneEnd() {
	return true;
}

// -------------ʵ����Ϸ�߼�������----------------
// �٣��߼�����
void  CGame::GameRunLogic() {
	// ���ݲ�ͬ�Ľ׶ε��ò�ͬ�Ĵ�����
	(this->*m_logicFunc[m_eStep])();
}
// �ڣ���Ϸ�߼�����ѡ��׶�
void CGame::GameRunLogicOnMenu() {
	// ʲôҲ��������û�п�ʼ��Ϸ
}
// �ۣ���Ϸ�߼������˻���ս�˵��׶�
void CGame::GameRunLogicOnOne2BotMenu() {
	// �������M������ֹͣ����״̬
	if (KEYDOWN('M')) {
		m_keymenu01.SetStop();
	}
	// 
	if (m_keymenu01.GetStop()) {
		SetStep(EGameTypeOne2Bot);
	}
}
// �ܣ���Ϸ�߼������˻���ս
void CGame::GameRunLogicOnOne2Bot() {
	// ״̬ά�����Ƴ��б�����Ч���ӵ���������Ӧ��̹�������ӵ�
	RemoveTimeoutBullets();

	// ����ӵ��Ƿ����̹�ˣ�����̹��Ҫ��̹�˱�ը
	for (auto &blt : m_lstBullets) {
		if (m_bot.IsHitted(blt)) {			// ���л�����
			m_bot.Bomb();					// �����˱�ը
			m_eStep = EGameTypeOne2BotEnd;  // ��Ϸ����
			blt.SetActive(false);			// ʹ�ӵ�������Ч
		}
		if (m_player01.IsHitted(blt)) {			// �������һ
			m_player01.Bomb();					// ���һ��ը
			m_eStep = EGameTypeOne2BotEnd;  // ��Ϸ����
			blt.SetActive(false);			// ʹ�ӵ�������Ч
		}
		break;
	}

	// �ӵ��˶�ά��
	ProcessHitBullets();

	// ʹ�������Զ��������
	AI();

	// ��������
	{
		// ���������
		if (KEYDOWN(VK_LEFT)) {
			m_player01.RotateLeft(); // �������ת
		}
		// �����ҷ����
		if (KEYDOWN(VK_RIGHT)) {
			m_player01.RotateRight(); // �������ת

		}
		// �����Ϸ����
		if (KEYDOWN(VK_UP)) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player01.Forward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// �����·���
		if (KEYDOWN(VK_DOWN)) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player01, false)) {
					m_player01.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player01.Backward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// ����M��
		if (KEYDOWN('M')) {
			CBullet blt;
			if (m_player01.Fire(blt)) { // ����
				m_lstBullets.push_back(blt); // ���뵽��ͼ�б�
			}
		}

		// ����I���������˲���
		if (KEYDOWN('I')){
			// �����˺����һ���ڵ�λ��
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				return;
			}
			// ��������һ������
			float fDirNext = 0;
			if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
				return;
			}
			// ��ȡ������̹�˵����ĵ�
			PointF ptTankCenter = m_bot.GetCenterPoint();
			PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
			RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

			// �ж�̹���Ƿ��Ѿ��ߵ����ĵ�λ��
			if (!rc.Contains(ptAreaCenter)) {
				m_bot.Forward();
				return;
			}
			else {
				m_bot.SetDirection(fDirNext);			// ���û����˵ķ���
				m_bot.Forward();
			}
		}
	}
}
// ��Ϸ�߼������˻���ս����
void CGame::GameRunLogicOnOne2BotEnd() {
	//  ��������

	// ״̬ά��
	RemoveTimeoutBullets();

	// �ж��ӵ��Ƿ�ײ��ǽ��
	ProcessHitBullets();
}
// ��Ϸ�߼�����˫�˴�ս�˵��׶�
void CGame::GameRunLogicOnOne2OneMenu() {
	// �������M������ֹͣ����״̬
	if (KEYDOWN('M')) {
		m_keymenu01.SetStop();
	}
	if (KEYDOWN('Q')) {
		m_keymenu02.SetStop();
	}
	// ����������ˣ�����ʽ��ʼ��Ϸ
	if (m_keymenu01.GetStop() && m_keymenu02.GetStop()) {
		SetStep(EGameTypeOne2One);
	}
}
// ��Ϸ�߼�����˫�˴�ս
void CGame::GameRunLogicOnOne2One() {
	// ��������
	{
		// ���һ--------------------------------------------
		// ���������
		if (KEYDOWN(VK_LEFT)) {
			m_player01.RotateLeft(); // �������ת
		}
		// �����ҷ����
		if (KEYDOWN(VK_RIGHT)) {
			m_player01.RotateRight(); // �������ת

		}
		// �����Ϸ����
		if (KEYDOWN(VK_UP)) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player01.Forward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// �����·���
		if (KEYDOWN(VK_DOWN)) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player01, false)) {
					m_player01.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player01.Backward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// ����M��
		if (KEYDOWN('M')) {
			CBullet blt;
			if (m_player01.Fire(blt)) { // ����
				m_lstBullets.push_back(blt); // ���뵽��ͼ�б�
			}
		}

		// ��Ҷ�------------------------------------
		// ���������
		if (KEYDOWN('S')) {
			m_player02.RotateLeft(); // �������ת
		}
		// �����ҷ����
		if (KEYDOWN('F')) {
			m_player02.RotateRight(); // �������ת

		}
		// �����Ϸ����
		if (KEYDOWN('E')) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player02, true)) {
					m_player02.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player02.Forward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// �����·���
		if (KEYDOWN('D')) {
			// ̹����ײ���
			{
				if (m_map.IsHitTheWall(m_player02, false)) {
					m_player02.ChangeDirection(true); // ײǽ�󣬸ı䷽��
				}
				else {
					m_player02.Backward(); // �����ǰ�ߣ� ���û��ײǽ������ǰ��
				}
			}
		}
		// ����M��
		if (KEYDOWN('Q')) {
			CBullet blt;
			if (m_player02.Fire(blt)) { // ����
				m_lstBullets.push_back(blt); // ���뵽��ͼ�б�
			}
		}
		if (KEYDOWN('Z')) {
			if (m_map.IsCanKillTarget(m_player01, m_player02)) {
				AfxMessageBox(_T("���Դ�"));
			}
		}
	}

	// ״̬ά��
	// �Ƴ��б�����Ч���ӵ���������Ӧ��̹�������ӵ�
	RemoveTimeoutBullets();

	// ����ӵ��Ƿ����̹�ˣ�����̹��Ҫ��̹�˱�ը
	for (auto &blt : m_lstBullets) {
		if (!blt.IsActive()) {
			continue;
		}
		if (m_player01.IsHitted(blt)) {			// ���л����һ
			m_player01.Bomb();					// ���һ��ը
			m_eStep = EGameTypeOne2OneEnd;  // ��Ϸ����
			blt.SetActive(false);			// ʹ�ӵ�������Ч
		}
		if (m_player02.IsHitted(blt)) {		// ������Ҷ�
			m_player02.Bomb();				// ��Ҷ���ը
			m_eStep = EGameTypeOne2OneEnd;  // ��Ϸ����
			blt.SetActive(false);			// ʹ�ӵ�������Ч
		}
	}

	// �ӵ��˶�ά��
	ProcessHitBullets();
}
// ��Ϸ�߼�����˫�˴�ս����
void CGame::GameRunLogicOnOne2OneEnd() {
	// ��������

	// �Ƴ��ӵ�
	RemoveTimeoutBullets();
	// �ӵ�ײǽ����
	ProcessHitBullets();
}

// -------------ʵ����Ϸ��ͼ������----------------
// ��Ϸ��ͼ
void CGame::GameRunDraw() {
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC *dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory; // ˫�����ͼ��
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc()); // ���챳��
	gh.Clear(Color::White); // �������
	gh.ResetClip();

	// �����ڴ�
	(this->*m_DrawFunc[m_eStep])(gh);
	// ���Ƶ���Ļ
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hdc);
	return;
}
// ѡ��׶�
void CGame::GameRunDrawOnMenu(Graphics &gh) {
	m_menuSelect.Draw(gh);
}
// �˻���ս���˵��׶�
void CGame::GameRunDrawOnOne2BotMeun(Graphics &gh) {
	// ������
	m_menu.Draw(gh);
	// ���˵�
	m_keymenu01.Draw(gh);
}
// �˻���ս
void CGame::GameRunDrawOnOne2Bot(Graphics &gh) {
	// ���˵�
	m_menuBackup.Draw(gh);
	// ��ǽ
	m_map.Draw(gh);

	// �����һ
	m_player01.Draw(gh);
	m_bot.Draw(gh);

	for (auto b:m_lstBullets) {
		b.Draw(gh);
	}

	// �����FPS
	DrawFps(gh);
}
// �˻���ս����
void CGame::GameRunDrawOnOne2BotEnd(Graphics &gh) {
	// �˵�
	m_menuBackup.Draw(gh);
	// ǽ
	m_map.Draw(gh);
	// ���
	m_player01.Draw(gh);
	// �����ˣ����Կ��Ƶ�̹�ˣ�
	m_bot.Draw(gh);

	// �����FPS
	DrawFps(gh);

	// �ж���Ϸ�������
	if (m_player01.IsBombEnd() || m_bot.IsBombEnd()) { 
		// ����Ϊ�˵�״̬
		m_eStep = EGameTypeMenu;
	}
}
// ˫�˴�ս���˵��׶�
void CGame::GameRunDrawOnOne2OneMenu(Graphics &gh) {
	// �˵�����
	m_menu.Draw(gh);
	// ����1
	m_keymenu01.Draw(gh);
	// ����2
	m_keymenu02.Draw(gh);
}
// ˫�˴�ս
void CGame::GameRunDrawOnOne2One(Graphics &gh) {
	// �˵�
	m_menuBackup.Draw(gh);
	// ǽ
	m_map.Draw(gh);
	// ���һ
	m_player01.Draw(gh);
	// ��Ҷ�
	m_player02.Draw(gh);

	// �����Ѿ�������ӵ�
	for (auto b:m_lstBullets) {
		b.Draw(gh);
	}

	// �����FPS
	DrawFps(gh);
}
// ˫�˴�ս����
void CGame::GameRunDrawOnOne2OneEnd(Graphics &gh) {
	// �˵�
	m_menuBackup.Draw(gh);
	// ǽ
	m_map.Draw(gh);
	// ���һ
	m_player01.Draw(gh);
	// ��Ҷ�
	m_player02.Draw(gh);

	// �����Ѿ�������ӵ�
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}

	// �����FPS
	DrawFps(gh);

	// �ж���Ϸ�������
	if (m_player01.IsBombEnd() || m_player02.IsBombEnd()) {
		m_eStep = EGameTypeMenu;
	}
}

// --------------ʵ�ָ�������-------------------
// ��fps
void CGame::DrawFps(Graphics &gh) {
	static int fps = 0;
	m_fps++;

	static DWORD dwLast = GetTickCount();	// ��¼�ϴ����е�ʱ��
	if (GetTickCount() - dwLast >= 1000) {
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();			// ��¼����ʱ��
	}

	// ���fps
	{
		CString s;
		s.Format(_T("FPS: %d"), fps);
		SolidBrush brush(Color(0x00, 0x00, 0xFF));

		Gdiplus::Font font(_T("����"), 10.0);
		CRect rc;
		::GetClientRect(m_hWnd, &rc);
		PointF origin(static_cast<float>(rc.right - 100), static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}
// �Ƴ���ʱ�ӵ���������Ӧ��̹��װ��
void CGame::RemoveTimeoutBullets() {
	// ������ҷ���
	auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(), [](CBullet &blt)->bool {return blt.IsTimeout(); });
	// ���ӵ��Ƴ���������Ӧ��̹�������ӵ�
	for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
		// ����Ϊ��Ч
		it->SetActive(false);
		// ����Ӧ��̹�������ӵ�
		it->GetOwner()->AddBullet(*it);
	}
	// �ӱ���ɾ���ӵ�
	m_lstBullets.erase(itRemove, m_lstBullets.end());
}
// �ӵ��˶���ά����ײǽ����
void CGame::ProcessHitBullets() {
	// �ӵ��Ƿ�ײ��ǽ�����ײ���ˣ��ı䷽��
	for (auto &blt : m_lstBullets) {
		// ����ײǽ�������ײǽ���ĺ����л�ı��ӵ�����
		m_map.HitWallProcess(blt);
		// �ӵ�����ǰ��
		blt.Move();
	}
}
// ά�����Ե��Զ�Ѱ·����
void CGame::AI() {
	// �����˶�״̬ά��
	static CGameTimer acTimer(-1, 150);
	if (acTimer.IsTimeval()) {
		// �����˺����һ���ڵ�λ��
		int startX, startY, targetX, targetY;
		if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		// ��������һ������
		float fDirNext = 0;
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
			return;
		}
		// ��ȡ������̹�˵����ĵ�
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		// �ж�̹���Ƿ��Ѿ��ߵ����ĵ�λ��
		if (!rc.Contains(ptAreaCenter)) {
			m_bot.Forward();						// û�е������ĵ㣬�����ǰ��
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);			// ���û����˵ķ���
			
			float dir;
			// �ж��Ƿ���Դ����һ
			if (m_map.IsCanKillTarget(m_bot, m_player01, &dir)) {
				CBullet blt;
				// �����˿�����������
				if (m_bot.Fire(blt)) {
					m_lstBullets.push_back(blt);
				}
				return;
			}
			m_bot.Forward();
		}
	}
}
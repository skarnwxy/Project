#include "pch.h"
#include "Game.h"
//#include <algorithm>

#define KEYDOWN(vk) (GetAsyncKeyState(vk)& 0x8000)

CGame::CGame() {
	//GameInitOne2Bot(); // 初始化人机大战游戏
	m_menuSelect.m_pParent = this;		// 设置菜单选择项指向当前对象
	m_menuBackup.m_pParent = this;		// 设置菜单背景项指向当前对象
}

CGame::~CGame() {

}

// --------------实现为外界提供的方法-------------------
// ①：设置输出窗口的句柄
void CGame::SetHandle(HWND hWnd) {
	m_hWnd = hWnd;
}
// ②：进去游戏帧
bool CGame::EnterFrame(DWORD deTime) {
	// !!!调用逻辑处理函数
	GameRunLogic();

	// !!!调用绘图函数
	GameRunDraw();

	return false;
}
// ③：处理鼠标移动事件
void CGame::OnMouseMove(UINT nFlags, CPoint point) {
	// 选择阶段
	if (m_eStep == EGameTypeMenu) {
		m_menuSelect.OnMouseMove(nFlags, point);		// 选择游戏的类型
	}
	else {
		m_menuBackup.OnMouseMove(nFlags, point);		// 返回主菜单
	}
}
// ④：处理左键抬起事件
void CGame::OnLButtonUp(UINT nFlags, CPoint point) {
	// 选择阶段
	if (m_eStep == EGameTypeMenu) {
		m_menuSelect.OnLButtonUp(nFlags, point);		// 选择游戏类型
	}
	else {
		m_menuSelect.OnLButtonUp(nFlags, point);		// 返回主菜单
	}
}
// ⑤：设置当前游戏所处的阶段，根据步骤初始化
void CGame::SetStep(EGameType step) {
	m_eStep = step;
	GameInit();											// 调用初始化函数
}

// -------------实现初始化方法----------------
// 生成游戏对象、初始化地图和对象的位置
// ①：初始化
bool CGame::GameInit() {
	srand(GetTickCount());								// 初始化随机数生成器
	return (this->*m_initFunc[m_eStep])();				// 根据不同阶段调用不同的处理方法
}
// ②：游戏初始化：选择阶段
bool CGame::GameInitMenu() {
	return true;
}
// ③：游戏初始化：人机大战菜单阶段
bool CGame::GameInitOne2BotMenu() {
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	PointF pt;
	pt.X = rc.left + (rc.right - rc.left) / 2.0f;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;

	m_keymenu01.SetCenterPoint(pt);						// 设置人机大战KeyMenu位置为屏幕正中间
	m_keymenu01.SetStop(false);							// 设置"不"停止播放动画

	return true;
}
// ④：游戏初始化：人机大战
bool CGame::GameInitOne2Bot() {
	for ( ; ; ) {
		m_map.LoadMap(); // 载入地图
		// 玩家一
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));	 // 构造玩家一位置
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {			 // 随机查找地图中的空地
				AfxMessageBox(_T("调整player01位置失败"));			 // 提示调整位置失败
			}
			else {
				// 设置玩家一的中心点，让玩家一处于地图格子的正中间位置
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		// 机器大战（电脑控制的坦克）
		{
			m_bot = CBot(0, 0, _T("tank_bot.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整bot位置失败"));
			}
			else {
				m_bot.SetCenterPoint(ptCenter);
			}

		}
		// 子弹
		m_lstBullets.clear();

		// 判断是否合法
		{
			// 获取机器人和玩家一所在的位置
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				AfxMessageBox(_T("获取坦克位置发生错误"));
				break;
				//goto __Init_End;
			}
			// 判断玩家一和机器人是否连通，如果连通则无法进入游戏
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
// ⑤：游戏初始化：人机大战结束
bool CGame::GameInitOne2BotEnd() {
	return true;
}
// ⑥：游戏初始化：双人大战菜单阶段
bool CGame::GameInitOne2OneMenu() {
	// 设置两个玩家的KeyMenu位置：屏幕正中间
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
// ⑦：游戏初始化：双人大战
bool CGame::GameInitOne2One() {
	for (; ; ) {
		m_map.LoadMap();
		// 玩家一
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整player01位置失败"));	
			}
			else {
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		// 机器大战（电脑控制的坦克）
		{
			m_player02 = CPlayer(0, 0, _T("tank_player2.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整player02位置失败"));
			}
			else {
				m_player02.SetCenterPoint(ptCenter);
			}
		}
		// 子弹
		m_lstBullets.clear();

		// 判断是否合法
		{
			// 获取玩家一和玩家二所在的位置
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_player02, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				AfxMessageBox(_T("获取坦克位置发生错误"));
				break;
			}
			// 判断玩家一和玩家二否连通，如果连通则无法进入游戏
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty()) {
				break;
			}
		}
	}
	return true;
}
// ⑧：游戏初始化：双人大战结束
bool CGame::GameInitOne2OneEnd() {
	return true;
}

// -------------实现游戏逻辑处理方法----------------
// ①：逻辑处理
void  CGame::GameRunLogic() {
	// 根据不同的阶段调用不同的处理方法
	(this->*m_logicFunc[m_eStep])();
}
// ②：游戏逻辑处理：选择阶段
void CGame::GameRunLogicOnMenu() {
	// 什么也不做，还没有开始游戏
}
// ③：游戏逻辑处理：人机大战菜单阶段
void CGame::GameRunLogicOnOne2BotMenu() {
	// 如果按下M健，则停止动画状态
	if (KEYDOWN('M')) {
		m_keymenu01.SetStop();
	}
	// 
	if (m_keymenu01.GetStop()) {
		SetStep(EGameTypeOne2Bot);
	}
}
// ④：游戏逻辑处理：人机大战
void CGame::GameRunLogicOnOne2Bot() {
	// 状态维护，移除列表中无效的子弹，并给响应的坦克增加子弹
	RemoveTimeoutBullets();

	// 检查子弹是否击中坦克，击中坦克要是坦克爆炸
	for (auto &blt : m_lstBullets) {
		if (m_bot.IsHitted(blt)) {			// 击中机器人
			m_bot.Bomb();					// 机器人爆炸
			m_eStep = EGameTypeOne2BotEnd;  // 游戏结束
			blt.SetActive(false);			// 使子弹不再有效
		}
		if (m_player01.IsHitted(blt)) {			// 击中玩家一
			m_player01.Bomb();					// 玩家一爆炸
			m_eStep = EGameTypeOne2BotEnd;  // 游戏结束
			blt.SetActive(false);			// 使子弹不再有效
		}
		break;
	}

	// 子弹运动维护
	ProcessHitBullets();

	// 使机器人自动攻击玩家
	AI();

	// 按键处理
	{
		// 按下左方向键
		if (KEYDOWN(VK_LEFT)) {
			m_player01.RotateLeft(); // 玩家向左转
		}
		// 按下右方向键
		if (KEYDOWN(VK_RIGHT)) {
			m_player01.RotateRight(); // 玩家向右转

		}
		// 按下上方向键
		if (KEYDOWN(VK_UP)) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player01.Forward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下下方键
		if (KEYDOWN(VK_DOWN)) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player01, false)) {
					m_player01.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player01.Backward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下M键
		if (KEYDOWN('M')) {
			CBullet blt;
			if (m_player01.Fire(blt)) { // 开火
				m_lstBullets.push_back(blt); // 加入到地图列表
			}
		}

		// 按下I健，机器人步进
		if (KEYDOWN('I')){
			// 机器人和玩家一所在的位置
			int startX, startY, targetX, targetY;
			if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
				return;
			}
			// 机器人下一步方向
			float fDirNext = 0;
			if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
				return;
			}
			// 获取机器人坦克的中心点
			PointF ptTankCenter = m_bot.GetCenterPoint();
			PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
			RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

			// 判断坦克是否已经走到中心点位置
			if (!rc.Contains(ptAreaCenter)) {
				m_bot.Forward();
				return;
			}
			else {
				m_bot.SetDirection(fDirNext);			// 设置机器人的方向
				m_bot.Forward();
			}
		}
	}
}
// 游戏逻辑处理：人机大战结束
void CGame::GameRunLogicOnOne2BotEnd() {
	//  按键处理

	// 状态维护
	RemoveTimeoutBullets();

	// 判断子弹是否撞在墙上
	ProcessHitBullets();
}
// 游戏逻辑处理：双人大战菜单阶段
void CGame::GameRunLogicOnOne2OneMenu() {
	// 如果按下M健，则停止动画状态
	if (KEYDOWN('M')) {
		m_keymenu01.SetStop();
	}
	if (KEYDOWN('Q')) {
		m_keymenu02.SetStop();
	}
	// 如果都按下了，则正式开始游戏
	if (m_keymenu01.GetStop() && m_keymenu02.GetStop()) {
		SetStep(EGameTypeOne2One);
	}
}
// 游戏逻辑处理：双人大战
void CGame::GameRunLogicOnOne2One() {
	// 按键处理
	{
		// 玩家一--------------------------------------------
		// 按下左方向键
		if (KEYDOWN(VK_LEFT)) {
			m_player01.RotateLeft(); // 玩家向左转
		}
		// 按下右方向键
		if (KEYDOWN(VK_RIGHT)) {
			m_player01.RotateRight(); // 玩家向右转

		}
		// 按下上方向键
		if (KEYDOWN(VK_UP)) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player01.Forward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下下方键
		if (KEYDOWN(VK_DOWN)) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player01, false)) {
					m_player01.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player01.Backward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下M键
		if (KEYDOWN('M')) {
			CBullet blt;
			if (m_player01.Fire(blt)) { // 开火
				m_lstBullets.push_back(blt); // 加入到地图列表
			}
		}

		// 玩家二------------------------------------
		// 按下左方向键
		if (KEYDOWN('S')) {
			m_player02.RotateLeft(); // 玩家向左转
		}
		// 按下右方向键
		if (KEYDOWN('F')) {
			m_player02.RotateRight(); // 玩家向右转

		}
		// 按下上方向键
		if (KEYDOWN('E')) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player02, true)) {
					m_player02.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player02.Forward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下下方键
		if (KEYDOWN('D')) {
			// 坦克碰撞检测
			{
				if (m_map.IsHitTheWall(m_player02, false)) {
					m_player02.ChangeDirection(true); // 撞墙后，改变方向
				}
				else {
					m_player02.Backward(); // 玩家向前走， 如果没有撞墙，继续前进
				}
			}
		}
		// 按下M键
		if (KEYDOWN('Q')) {
			CBullet blt;
			if (m_player02.Fire(blt)) { // 开火
				m_lstBullets.push_back(blt); // 加入到地图列表
			}
		}
		if (KEYDOWN('Z')) {
			if (m_map.IsCanKillTarget(m_player01, m_player02)) {
				AfxMessageBox(_T("可以打到"));
			}
		}
	}

	// 状态维护
	// 移除列表中无效的子弹，并给响应的坦克增加子弹
	RemoveTimeoutBullets();

	// 检查子弹是否击中坦克，击中坦克要是坦克爆炸
	for (auto &blt : m_lstBullets) {
		if (!blt.IsActive()) {
			continue;
		}
		if (m_player01.IsHitted(blt)) {			// 击中机玩家一
			m_player01.Bomb();					// 玩家一爆炸
			m_eStep = EGameTypeOne2OneEnd;  // 游戏结束
			blt.SetActive(false);			// 使子弹不再有效
		}
		if (m_player02.IsHitted(blt)) {		// 击中玩家二
			m_player02.Bomb();				// 玩家二爆炸
			m_eStep = EGameTypeOne2OneEnd;  // 游戏结束
			blt.SetActive(false);			// 使子弹不再有效
		}
	}

	// 子弹运动维护
	ProcessHitBullets();
}
// 游戏逻辑处理：双人大战结束
void CGame::GameRunLogicOnOne2OneEnd() {
	// 按键处理

	// 移除子弹
	RemoveTimeoutBullets();
	// 子弹撞墙处理
	ProcessHitBullets();
}

// -------------实现游戏绘图处理方法----------------
// 游戏绘图
void CGame::GameRunDraw() {
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC *dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory; // 双缓冲绘图用
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc()); // 构造背景
	gh.Clear(Color::White); // 清除背景
	gh.ResetClip();

	// 画入内存
	(this->*m_DrawFunc[m_eStep])(gh);
	// 复制到屏幕
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hdc);
	return;
}
// 选择阶段
void CGame::GameRunDrawOnMenu(Graphics &gh) {
	m_menuSelect.Draw(gh);
}
// 人机大战：菜单阶段
void CGame::GameRunDrawOnOne2BotMeun(Graphics &gh) {
	// 画背景
	m_menu.Draw(gh);
	// 画菜单
	m_keymenu01.Draw(gh);
}
// 人机大战
void CGame::GameRunDrawOnOne2Bot(Graphics &gh) {
	// 画菜单
	m_menuBackup.Draw(gh);
	// 画墙
	m_map.Draw(gh);

	// 画玩家一
	m_player01.Draw(gh);
	m_bot.Draw(gh);

	for (auto b:m_lstBullets) {
		b.Draw(gh);
	}

	// 输出：FPS
	DrawFps(gh);
}
// 人机大战结束
void CGame::GameRunDrawOnOne2BotEnd(Graphics &gh) {
	// 菜单
	m_menuBackup.Draw(gh);
	// 墙
	m_map.Draw(gh);
	// 玩家
	m_player01.Draw(gh);
	// 机器人（电脑控制的坦克）
	m_bot.Draw(gh);

	// 输出：FPS
	DrawFps(gh);

	// 判断游戏整体结束
	if (m_player01.IsBombEnd() || m_bot.IsBombEnd()) { 
		// 设置为菜单状态
		m_eStep = EGameTypeMenu;
	}
}
// 双人大战：菜单阶段
void CGame::GameRunDrawOnOne2OneMenu(Graphics &gh) {
	// 菜单背景
	m_menu.Draw(gh);
	// 单项1
	m_keymenu01.Draw(gh);
	// 单项2
	m_keymenu02.Draw(gh);
}
// 双人大战
void CGame::GameRunDrawOnOne2One(Graphics &gh) {
	// 菜单
	m_menuBackup.Draw(gh);
	// 墙
	m_map.Draw(gh);
	// 玩家一
	m_player01.Draw(gh);
	// 玩家二
	m_player02.Draw(gh);

	// 画出已经发射的子弹
	for (auto b:m_lstBullets) {
		b.Draw(gh);
	}

	// 输出：FPS
	DrawFps(gh);
}
// 双人大战结束
void CGame::GameRunDrawOnOne2OneEnd(Graphics &gh) {
	// 菜单
	m_menuBackup.Draw(gh);
	// 墙
	m_map.Draw(gh);
	// 玩家一
	m_player01.Draw(gh);
	// 玩家二
	m_player02.Draw(gh);

	// 画出已经发射的子弹
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}

	// 输出：FPS
	DrawFps(gh);

	// 判断游戏整体结束
	if (m_player01.IsBombEnd() || m_player02.IsBombEnd()) {
		m_eStep = EGameTypeMenu;
	}
}

// --------------实现辅助方法-------------------
// 画fps
void CGame::DrawFps(Graphics &gh) {
	static int fps = 0;
	m_fps++;

	static DWORD dwLast = GetTickCount();	// 记录上次运行的时间
	if (GetTickCount() - dwLast >= 1000) {
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();			// 记录本次时间
	}

	// 输出fps
	{
		CString s;
		s.Format(_T("FPS: %d"), fps);
		SolidBrush brush(Color(0x00, 0x00, 0xFF));

		Gdiplus::Font font(_T("宋体"), 10.0);
		CRect rc;
		::GetClientRect(m_hWnd, &rc);
		PointF origin(static_cast<float>(rc.right - 100), static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}
// 移除超时子弹，并给对应的坦克装弹
void CGame::RemoveTimeoutBullets() {
	// 定义查找方法
	auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(), [](CBullet &blt)->bool {return blt.IsTimeout(); });
	// 把子弹移除，并给对应的坦克增加子弹
	for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
		// 设置为无效
		it->SetActive(false);
		// 给对应的坦克增加子弹
		it->GetOwner()->AddBullet(*it);
	}
	// 从本地删除子弹
	m_lstBullets.erase(itRemove, m_lstBullets.end());
}
// 子弹运动的维护：撞墙拐弯
void CGame::ProcessHitBullets() {
	// 子弹是否撞上墙：如果撞上了，改变方向
	for (auto &blt : m_lstBullets) {
		// 进行撞墙处理，如果撞墙，改函数中会改变子弹方向
		m_map.HitWallProcess(blt);
		// 子弹继续前进
		blt.Move();
	}
}
// 维护电脑的自动寻路攻击
void CGame::AI() {
	// 电脑运动状态维护
	static CGameTimer acTimer(-1, 150);
	if (acTimer.IsTimeval()) {
		// 机器人和玩家一所在的位置
		int startX, startY, targetX, targetY;
		if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		// 机器人下一步方向
		float fDirNext = 0;
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
			return;
		}
		// 获取机器人坦克的中心点
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		// 判断坦克是否已经走到中心点位置
		if (!rc.Contains(ptAreaCenter)) {
			m_bot.Forward();						// 没有到达中心点，则继续前进
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);			// 设置机器人的方向
			
			float dir;
			// 判断是否可以打开玩家一
			if (m_map.IsCanKillTarget(m_bot, m_player01, &dir)) {
				CBullet blt;
				// 机器人开发主动进攻
				if (m_bot.Fire(blt)) {
					m_lstBullets.push_back(blt);
				}
				return;
			}
			m_bot.Forward();
		}
	}
}
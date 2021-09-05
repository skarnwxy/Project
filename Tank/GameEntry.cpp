// CPP文件
#include "pch.h"
#include "GameEntry.h"

//复制构造函数
CGameEntryMoveable::CGameEntryMoveable(const CGameEntryMoveable &rhs) {
	if (this != &rhs) {
		this->m_bActive = rhs.m_bActive;
		this->m_rect = rhs.m_rect;
		this->m_fSpeed = rhs.m_fSpeed;
		this->m_direction = rhs.m_direction;
		this->m_directionTurn = rhs.m_directionTurn;
	}
}
// 重载赋值运算
CGameEntryMoveable &CGameEntryMoveable::operator=(const CGameEntryMoveable &rhs) {
	if (this != &rhs) {
		this->m_bActive = rhs.m_bActive;
		this->m_rect = rhs.m_rect;
		this->m_fSpeed = rhs.m_fSpeed;
		this->m_direction = rhs.m_direction;
		this->m_directionTurn = rhs.m_directionTurn;
	}
	return *this;
}


//------------------------------------------------
//可移动物体的共同属性
// 右转
void CGameEntryMoveable::RotateRight() {
	m_direction += m_directionTurn;
	if (m_direction >= 360) {
		m_direction -= 360;
	}

}
// 左转
void CGameEntryMoveable::RotateLeft() {
	m_direction -= m_directionTurn;
	if (m_direction < 0) {
		m_direction = static_cast<float>(360 - m_directionTurn);
	}
}
// 前移
void CGameEntryMoveable::Forward() {
	m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));

}
// 后移
void CGameEntryMoveable::Backward() {
	m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	m_rect.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
}
// 获取水平方向的速度分量
float CGameEntryMoveable::GetXSpeed() const {
	return static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
}
// 获取竖直方向的速度分量
float CGameEntryMoveable::GetYSpeed() const {
	return static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));

}
// 下一步前进位置
RectF CGameEntryMoveable::ForwardNextRect() const {
	RectF rc = m_rect;
	rc.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return rc;
}
// 下一步后退的位置
RectF CGameEntryMoveable::BackwardNextRect() const {
	RectF rc = m_rect;
	rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return rc;
}

//获取头部位置：图片为矩形：头部位置就是角度为0时
//距离中心点为半径（对角线/2）,重置在X轴上的位置
PointF CGameEntryMoveable::GetHeadPos() const {
	PointF ptCenter = GetCenterPoint();
	PointF ptHead = ptCenter;
	float fRadius = std::sqrt(std::pow(m_rect.Width/2, 2) + std::pow(m_rect.Height/2, 2));

	ptHead.X += fRadius * sin(GetDirectionArc());
	ptHead.Y -= fRadius * sin(GetDirectionArc());
	return ptHead;
}
// 获取中心点
PointF CGameEntryMoveable::GetCenterPoint() const {
	PointF center = PointF(m_rect.X + m_rect.Width / 2, m_rect.Y + m_rect.Height / 2);
	return center;
}
// 设置中心点
void CGameEntryMoveable::SetCenterPoint(const PointF &ptCenter) {
	PointF cen = GetCenterPoint();
	cen.X = ptCenter.X - cen.X;
	cen.Y = ptCenter.Y - cen.Y;
	m_rect.Offset(cen);
}

// 属性存取器
// 设置角度：单位为"a*PI"
void CGameEntryMoveable::SetDirectionArc(float dir) {
	m_direction = dir*180.0f / PI;
}
// 设置角度（单位是："度"）
void CGameEntryMoveable::SetDirection(float dir) {
	m_direction = dir;
}
// 获取当前的角度（单位是"a*PI"）
float CGameEntryMoveable::GetDirectionArc() const {
	return PI * m_direction / 180.0f;
}
// 获取当前的角度（单位是"度"）
float CGameEntryMoveable::GetDirection() const {
	return m_direction;
}

// 设置每次旋转的角度
void CGameEntryMoveable::SetDirectionTurnArc(float dir) {
	m_directionTurn = PI * dir / 180.0f;
}
// 设置每次旋转的角度
void CGameEntryMoveable::SetDirectionTurn(float dir) {
	m_directionTurn = dir;
}
// 获取当前的角度（单位是"PI"）
float CGameEntryMoveable::GetDirectionTurnArc() const {
	return PI * m_directionTurn / 180.0f;
}
// 获取当前的弧度
float CGameEntryMoveable::GetDirectionTurn() const {
	return m_direction;
}

// 是否是有效的
bool CGameEntryMoveable::IsActive() const {
	return m_bActive;
}
void CGameEntryMoveable::SetActive(bool bActive) {
	m_bActive = bActive;
}

// 占用范围
void CGameEntryMoveable::SetRect(const RectF rect) {
	m_rect = rect;
}
RectF CGameEntryMoveable::GetRect() const {
	return m_rect;
}

// 移动速度
void CGameEntryMoveable::SetSpeed(float speed) {
	m_fSpeed = speed;
}
float CGameEntryMoveable::GetSpeed() const {
	return m_fSpeed;
}

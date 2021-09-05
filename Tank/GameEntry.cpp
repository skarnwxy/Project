// CPP�ļ�
#include "pch.h"
#include "GameEntry.h"

//���ƹ��캯��
CGameEntryMoveable::CGameEntryMoveable(const CGameEntryMoveable &rhs) {
	if (this != &rhs) {
		this->m_bActive = rhs.m_bActive;
		this->m_rect = rhs.m_rect;
		this->m_fSpeed = rhs.m_fSpeed;
		this->m_direction = rhs.m_direction;
		this->m_directionTurn = rhs.m_directionTurn;
	}
}
// ���ظ�ֵ����
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
//���ƶ�����Ĺ�ͬ����
// ��ת
void CGameEntryMoveable::RotateRight() {
	m_direction += m_directionTurn;
	if (m_direction >= 360) {
		m_direction -= 360;
	}

}
// ��ת
void CGameEntryMoveable::RotateLeft() {
	m_direction -= m_directionTurn;
	if (m_direction < 0) {
		m_direction = static_cast<float>(360 - m_directionTurn);
	}
}
// ǰ��
void CGameEntryMoveable::Forward() {
	m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));

}
// ����
void CGameEntryMoveable::Backward() {
	m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	m_rect.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
}
// ��ȡˮƽ������ٶȷ���
float CGameEntryMoveable::GetXSpeed() const {
	return static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
}
// ��ȡ��ֱ������ٶȷ���
float CGameEntryMoveable::GetYSpeed() const {
	return static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));

}
// ��һ��ǰ��λ��
RectF CGameEntryMoveable::ForwardNextRect() const {
	RectF rc = m_rect;
	rc.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return rc;
}
// ��һ�����˵�λ��
RectF CGameEntryMoveable::BackwardNextRect() const {
	RectF rc = m_rect;
	rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	return rc;
}

//��ȡͷ��λ�ã�ͼƬΪ���Σ�ͷ��λ�þ��ǽǶ�Ϊ0ʱ
//�������ĵ�Ϊ�뾶���Խ���/2��,������X���ϵ�λ��
PointF CGameEntryMoveable::GetHeadPos() const {
	PointF ptCenter = GetCenterPoint();
	PointF ptHead = ptCenter;
	float fRadius = std::sqrt(std::pow(m_rect.Width/2, 2) + std::pow(m_rect.Height/2, 2));

	ptHead.X += fRadius * sin(GetDirectionArc());
	ptHead.Y -= fRadius * sin(GetDirectionArc());
	return ptHead;
}
// ��ȡ���ĵ�
PointF CGameEntryMoveable::GetCenterPoint() const {
	PointF center = PointF(m_rect.X + m_rect.Width / 2, m_rect.Y + m_rect.Height / 2);
	return center;
}
// �������ĵ�
void CGameEntryMoveable::SetCenterPoint(const PointF &ptCenter) {
	PointF cen = GetCenterPoint();
	cen.X = ptCenter.X - cen.X;
	cen.Y = ptCenter.Y - cen.Y;
	m_rect.Offset(cen);
}

// ���Դ�ȡ��
// ���ýǶȣ���λΪ"a*PI"
void CGameEntryMoveable::SetDirectionArc(float dir) {
	m_direction = dir*180.0f / PI;
}
// ���ýǶȣ���λ�ǣ�"��"��
void CGameEntryMoveable::SetDirection(float dir) {
	m_direction = dir;
}
// ��ȡ��ǰ�ĽǶȣ���λ��"a*PI"��
float CGameEntryMoveable::GetDirectionArc() const {
	return PI * m_direction / 180.0f;
}
// ��ȡ��ǰ�ĽǶȣ���λ��"��"��
float CGameEntryMoveable::GetDirection() const {
	return m_direction;
}

// ����ÿ����ת�ĽǶ�
void CGameEntryMoveable::SetDirectionTurnArc(float dir) {
	m_directionTurn = PI * dir / 180.0f;
}
// ����ÿ����ת�ĽǶ�
void CGameEntryMoveable::SetDirectionTurn(float dir) {
	m_directionTurn = dir;
}
// ��ȡ��ǰ�ĽǶȣ���λ��"PI"��
float CGameEntryMoveable::GetDirectionTurnArc() const {
	return PI * m_directionTurn / 180.0f;
}
// ��ȡ��ǰ�Ļ���
float CGameEntryMoveable::GetDirectionTurn() const {
	return m_direction;
}

// �Ƿ�����Ч��
bool CGameEntryMoveable::IsActive() const {
	return m_bActive;
}
void CGameEntryMoveable::SetActive(bool bActive) {
	m_bActive = bActive;
}

// ռ�÷�Χ
void CGameEntryMoveable::SetRect(const RectF rect) {
	m_rect = rect;
}
RectF CGameEntryMoveable::GetRect() const {
	return m_rect;
}

// �ƶ��ٶ�
void CGameEntryMoveable::SetSpeed(float speed) {
	m_fSpeed = speed;
}
float CGameEntryMoveable::GetSpeed() const {
	return m_fSpeed;
}

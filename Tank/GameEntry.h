#pragma once
#include <gdiplus.h>
#include <math.h>
#include <cmath>

// ���Դ�ȡ��
//#define PI (3.1415926f)

// ��Ϸ�п��ƶ�����
class CGameEntry {
public:
	CGameEntry() {} // ���캯���������¶���ʱ����
	virtual ~CGameEntry() {};

	virtual void Draw(Gdiplus::Graphics &gh) const = 0; // ���ڻ����Լ��Ĵ��麯��
};

// ���ƶ��Ķ���
class CGameEntryMoveable : public CGameEntry {
private:
	bool m_bActive{false}; // �ж��Ƿ���Ч
	RectF m_rect{ 0, 0, 100, 100}; // ռ�õ�����
	float m_fSpeed{ 10 }; // �ƶ��ٶ�
	float m_direction{ 0 }; // ��ǰ�ĽǶ�
	float m_directionTurn{ 5 }; // ÿ����ת�ĽǶ�

public:
	CGameEntryMoveable() {}
	virtual ~CGameEntryMoveable() {}

	//���ƹ��캯��
	CGameEntryMoveable(const CGameEntryMoveable &rhs);
	// ���ظ�ֵ����
	CGameEntryMoveable &operator=(const CGameEntryMoveable &rhs);
	// ��ͼ����
	virtual void Draw(Gdiplus::Graphics &gh) const = 0;

	//------------------------------------------------
	//���ƶ�����Ĺ�ͬ����
	// ��ת
	virtual void RotateRight();
	// ��ת
	virtual void RotateLeft();
	// ǰ��
	virtual void Forward();
	// ����
	virtual void Backward();
	// ��ȡˮƽ������ٶȷ���
	virtual float GetXSpeed() const;
	// ��ȡ��ֱ������ٶȷ���
	virtual float GetYSpeed() const;
	// ��һ��ǰ��λ��
	virtual RectF ForwardNextRect() const;
	// ��һ�����˵�λ��
	virtual RectF BackwardNextRect() const;

	//��ȡͷ��λ�ã�ͼƬΪ���Σ�ͷ��λ�þ��ǽǶ�Ϊ0ʱ
	//�������ĵ�Ϊ�뾶���Խ���/2��,������X���ϵ�λ��
	virtual PointF GetHeadPos() const;
	// ��ȡ���ĵ�
	virtual PointF GetCenterPoint() const;
	// �������ĵ�
	virtual void SetCenterPoint(const PointF &ptCenter);

	// ���ýǶȣ���λΪ"a*PI"
	virtual void SetDirectionArc(float dir);
	// ���ýǶȣ���λ�ǣ�"��"��
	virtual void SetDirection(float dir);
	// ��ȡ��ǰ�ĽǶȣ���λ��"a*PI"��
	virtual float GetDirectionArc() const;
	// ��ȡ��ǰ�ĽǶȣ���λ��"��"��
	virtual float GetDirection() const;

	// ����ÿ����ת�ĽǶ�
	virtual void SetDirectionTurnArc(float dir);
	// ����ÿ����ת�ĽǶ�
	virtual void SetDirectionTurn(float dir);
	// ��ȡ��ǰ�ĽǶȣ���λ��"PI"��
	virtual float GetDirectionTurnArc() const;
	// ��ȡ��ǰ�Ļ���
	virtual float GetDirectionTurn() const;
	
	// �Ƿ�����Ч��
	virtual bool IsActive() const;
	virtual void SetActive(bool bActive);

	// ռ�÷�Χ
	virtual void SetRect(const RectF rect);
	virtual RectF GetRect() const;

	// �ƶ��ٶ�
	virtual void SetSpeed(float speed);
	virtual float GetSpeed() const;
};
#pragma once
#include <gdiplus.h>
#include <math.h>
#include <cmath>

// 属性存取器
//#define PI (3.1415926f)

// 游戏中可移动对象
class CGameEntry {
public:
	CGameEntry() {} // 构造函数：产生新对象时调用
	virtual ~CGameEntry() {};

	virtual void Draw(Gdiplus::Graphics &gh) const = 0; // 用于绘制自己的纯虚函数
};

// 可移动的对象
class CGameEntryMoveable : public CGameEntry {
private:
	bool m_bActive{false}; // 判断是否有效
	RectF m_rect{ 0, 0, 100, 100}; // 占用的区域
	float m_fSpeed{ 10 }; // 移动速度
	float m_direction{ 0 }; // 当前的角度
	float m_directionTurn{ 5 }; // 每次旋转的角度

public:
	CGameEntryMoveable() {}
	virtual ~CGameEntryMoveable() {}

	//复制构造函数
	CGameEntryMoveable(const CGameEntryMoveable &rhs);
	// 重载赋值运算
	CGameEntryMoveable &operator=(const CGameEntryMoveable &rhs);
	// 绘图方法
	virtual void Draw(Gdiplus::Graphics &gh) const = 0;

	//------------------------------------------------
	//可移动物体的共同属性
	// 右转
	virtual void RotateRight();
	// 左转
	virtual void RotateLeft();
	// 前移
	virtual void Forward();
	// 后移
	virtual void Backward();
	// 获取水平方向的速度分量
	virtual float GetXSpeed() const;
	// 获取竖直方向的速度分量
	virtual float GetYSpeed() const;
	// 下一步前进位置
	virtual RectF ForwardNextRect() const;
	// 下一步后退的位置
	virtual RectF BackwardNextRect() const;

	//获取头部位置：图片为矩形：头部位置就是角度为0时
	//距离中心点为半径（对角线/2）,重置在X轴上的位置
	virtual PointF GetHeadPos() const;
	// 获取中心点
	virtual PointF GetCenterPoint() const;
	// 设置中心点
	virtual void SetCenterPoint(const PointF &ptCenter);

	// 设置角度：单位为"a*PI"
	virtual void SetDirectionArc(float dir);
	// 设置角度（单位是："度"）
	virtual void SetDirection(float dir);
	// 获取当前的角度（单位是"a*PI"）
	virtual float GetDirectionArc() const;
	// 获取当前的角度（单位是"度"）
	virtual float GetDirection() const;

	// 设置每次旋转的角度
	virtual void SetDirectionTurnArc(float dir);
	// 设置每次旋转的角度
	virtual void SetDirectionTurn(float dir);
	// 获取当前的角度（单位是"PI"）
	virtual float GetDirectionTurnArc() const;
	// 获取当前的弧度
	virtual float GetDirectionTurn() const;
	
	// 是否是有效的
	virtual bool IsActive() const;
	virtual void SetActive(bool bActive);

	// 占用范围
	virtual void SetRect(const RectF rect);
	virtual RectF GetRect() const;

	// 移动速度
	virtual void SetSpeed(float speed);
	virtual float GetSpeed() const;
};
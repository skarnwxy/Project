
// TankView.h: CTankView 类的接口
//

#pragma once


class CTankView : public CView
{
protected: // 仅从序列化创建
	CTankView() noexcept;
	DECLARE_DYNCREATE(CTankView)

// 特性
public:
	CTankDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CTankView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TankView.cpp 中的调试版本
inline CTankDoc* CTankView::GetDocument() const
   { return reinterpret_cast<CTankDoc*>(m_pDocument); }
#endif


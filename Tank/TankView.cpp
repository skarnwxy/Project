
// TankView.cpp: CTankView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Tank.h"
#endif

#include "TankDoc.h"
#include "TankView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTankView

IMPLEMENT_DYNCREATE(CTankView, CView)

BEGIN_MESSAGE_MAP(CTankView, CView)
END_MESSAGE_MAP()

// CTankView 构造/析构

CTankView::CTankView() noexcept
{
	// TODO: 在此处添加构造代码

}

CTankView::~CTankView()
{
}

BOOL CTankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTankView 绘图

void CTankView::OnDraw(CDC* /*pDC*/)
{
	CTankDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTankView 诊断

#ifdef _DEBUG
void CTankView::AssertValid() const
{
	CView::AssertValid();
}

void CTankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTankDoc* CTankView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTankDoc)));
	return (CTankDoc*)m_pDocument;
}
#endif //_DEBUG


// CTankView 消息处理程序

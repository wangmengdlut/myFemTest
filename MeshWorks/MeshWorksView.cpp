// MeshWorksView.cpp : implementation of the CMeshWorksView class
//

#include "stdafx.h"
#include "MeshWorks.h"

#include "Mainfrm.h"
#include "MeshWorksDoc.h"
#include "MeshWorksView.h"
#include "DlgCrossSection.h"

#include "..\GLKernel\GLKernelView.h"
#include "..\GLKernel\CameraTool.h"
#include "..\InteractiveTools\SelectBoardTool.h"

#include "..\MeshEntities\QMeshPatch.h"
#include "..\MeshEntities\QMeshFace.h"
#include "..\MeshEntities\QMeshEdge.h"
#include "..\MeshEntities\QMeshNode.h"
#include "..\MeshEntities\QBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeshWorksView

IMPLEMENT_DYNCREATE(CMeshWorksView, CView)

BEGIN_MESSAGE_MAP(CMeshWorksView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_ISOMETRIC, &CMeshWorksView::OnViewIsometric)
	ON_COMMAND(ID_VIEW_BACKISOMETRIC, &CMeshWorksView::OnViewBackisometric)
	ON_COMMAND(ID_VIEW_FRONT, &CMeshWorksView::OnViewFront)
	ON_COMMAND(ID_VIEW_BACK, &CMeshWorksView::OnViewBack)
	ON_COMMAND(ID_VIEW_TOP, &CMeshWorksView::OnViewTop)
	ON_COMMAND(ID_VIEW_BOTTOM, &CMeshWorksView::OnViewBottom)
	ON_COMMAND(ID_VIEW_LEFT, &CMeshWorksView::OnViewLeft)
	ON_COMMAND(ID_VIEW_RIGHT, &CMeshWorksView::OnViewRight)
	ON_COMMAND(ID_VIEW_ORBIT, &CMeshWorksView::OnViewOrbit)
	ON_COMMAND(ID_VIEW_ZOOMWINDOW, &CMeshWorksView::OnViewZoomwindow)
	ON_COMMAND(ID_VIEW_DYNAMICZOOM, &CMeshWorksView::OnViewDynamiczoom)
	ON_COMMAND(ID_VIEW_ZOOMIN, &CMeshWorksView::OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &CMeshWorksView::OnViewZoomout)
	ON_COMMAND(ID_VIEW_ZOOMALL, &CMeshWorksView::OnViewZoomall)
	ON_COMMAND(ID_VIEW_GLOBALAXIS, &CMeshWorksView::OnViewGlobalaxis)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_VIEW_POLYCOUNT, &CMeshWorksView::OnViewPolycount)
	ON_COMMAND(ID_VIEW_SHADING, &CMeshWorksView::OnViewShading)
	ON_COMMAND(ID_VIEW_PROFILE, &CMeshWorksView::OnViewProfile)
	ON_COMMAND(ID_VIEW_MESH, &CMeshWorksView::OnViewMesh)
	ON_COMMAND(ID_VIEW_NODE, &CMeshWorksView::OnViewNode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHADING, &CMeshWorksView::OnUpdateViewShading)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROFILE, &CMeshWorksView::OnUpdateViewProfile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MESH, &CMeshWorksView::OnUpdateViewMesh)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NODE, &CMeshWorksView::OnUpdateViewNode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GLOBALAXIS, &CMeshWorksView::OnUpdateViewGlobalaxis)
	ON_COMMAND(ID_VIEW_SEED, &CMeshWorksView::OnViewSeed)
	ON_COMMAND(ID_VIEW_NORMAL, &CMeshWorksView::OnViewNormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMAL, &CMeshWorksView::OnUpdateViewNormal)
	ON_COMMAND(ID_VIEW_LIGHT, &CMeshWorksView::OnViewLight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIGHT, &CMeshWorksView::OnUpdateViewLight)
	ON_COMMAND(ID_VIEW_CROSS, &CMeshWorksView::OnViewCrossSectionVolume)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CROSS, &CMeshWorksView::OnUpdateViewCrossSectionVolume)
	ON_COMMAND(ID_SHADING_FACENORMAL, &CMeshWorksView::OnShadingFacenormal)
	ON_COMMAND(ID_SHADING_NODENORMAL, &CMeshWorksView::OnShadingNodenormal)
	ON_UPDATE_COMMAND_UI(ID_SHADING_FACENORMAL, &CMeshWorksView::OnUpdateShadingFacenormal)
	ON_UPDATE_COMMAND_UI(ID_SHADING_NODENORMAL, &CMeshWorksView::OnUpdateShadingNodenormal)
END_MESSAGE_MAP()

// CMeshWorksView construction/destruction

CMeshWorksView::CMeshWorksView()
{
	// TODO: add construction code here
	m_GLKernelView = new CGLKernelView(this);
	m_GLKernelView->SetMesh(FALSE);

	CrossSectionControl=NULL;
}

CMeshWorksView::~CMeshWorksView()
{
	delete m_GLKernelView;
}

BOOL CMeshWorksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return m_GLKernelView->PreCreateWindow(cs);
	//return CView::PreCreateWindow(cs);
}

// CMeshWorksView drawing


void CMeshWorksView::OnDraw(CDC* pDC)
{
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_GLKernelView->OnDraw(pDC);

	if (!(m_GLKernelView->GetCurrentTool()))
		m_GLKernelView->set_tool(new CameraTool(m_GLKernelView, ORBITPAN));
}


// CMeshWorksView diagnostics

#ifdef _DEBUG
void CMeshWorksView::AssertValid() const
{
	CView::AssertValid();
}

void CMeshWorksView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMeshWorksDoc* CMeshWorksView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMeshWorksDoc)));
	return (CMeshWorksDoc*)m_pDocument;
}
#endif //_DEBUG


// CMeshWorksView message handlers

int CMeshWorksView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return m_GLKernelView->OnCreate(lpCreateStruct);
}

void CMeshWorksView::OnDestroy()
{
	// TODO: Add your message handler code here

	m_GLKernelView->OnDestroy();
}

void CMeshWorksView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_GLKernelView->OnLButtonDown(nFlags, point);
}

void CMeshWorksView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_GLKernelView->OnLButtonUp(nFlags, point);
}

void CMeshWorksView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your message handler code here and/or call default
	m_GLKernelView->OnMouseMove(nFlags, point);

	CString str;
    CMainFrame* pFrame = (CMainFrame*)(AfxGetMainWnd());

	{
		// panel 1 displays the X-coordinate
		// panel 2 displays the Y-coordinate
		// panel 3 displays the Z-coordinate
        double wx,wy,wz;
        m_GLKernelView->screen_to_wcl(point.x, point.y, wx, wy, wz);
		str.Format("X: %6.2f", (float)(wx/pDoc->m_unitScale));
        (pFrame->m_wndStatusBar).SetPaneText(1, str);
		str.Format("Y: %6.2f", (float)(wy/pDoc->m_unitScale));
        (pFrame->m_wndStatusBar).SetPaneText(2, str);
		str.Format("Z: %6.2f", (float)(wz/pDoc->m_unitScale));
        (pFrame->m_wndStatusBar).SetPaneText(3, str); 
	}
}

void CMeshWorksView::OnSize(UINT nType, int cx, int cy)
{
	// TODO: Add your message handler code here

	m_GLKernelView->OnSize(nType, cx, cy);
	
}

void CMeshWorksView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_ESCAPE) // ESC
	{
		m_GLKernelView->clear_tools();
		m_GLKernelView->set_tool(new CameraTool(m_GLKernelView, ORBITPAN));
		return;
	}
	
	m_GLKernelView->OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMeshWorksView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_GLKernelView->OnRButtonDown(nFlags, point);
}

void CMeshWorksView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_GLKernelView->OnRButtonUp(nFlags, point);
}

void CMeshWorksView::OnViewIsometric()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_ISOMETRICVIEW);
}

void CMeshWorksView::OnViewBackisometric()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_BACKISOMETRICVIEW);
}

void CMeshWorksView::OnViewFront()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_FRONTVIEW);
}

void CMeshWorksView::OnViewBack()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_BACKVIEW);
}

void CMeshWorksView::OnViewTop()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_TOPVIEW);
}

void CMeshWorksView::OnViewBottom()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_BOTTOMVIEW);
}

void CMeshWorksView::OnViewLeft()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_LEFTVIEW);
}

void CMeshWorksView::OnViewRight()
{
	// TODO: Add your command handler code here

	m_GLKernelView->SetViewDirection(VD_RIGHTVIEW);
}

void CMeshWorksView::OnViewOrbit()
{
	// TODO: Add your command handler code here

	if (CrossSectionControl){
		delete CrossSectionControl;
		CrossSectionControl=NULL;
	}

	m_GLKernelView->clear_tools();
	m_GLKernelView->set_tool(new CameraTool(m_GLKernelView, ORBITPAN));
}

void CMeshWorksView::OnViewZoomwindow()
{
	// TODO: Add your command handler code here
	m_GLKernelView->clear_tools();
	m_GLKernelView->set_tool(new CameraTool(m_GLKernelView, ZOOMWINDOW));
}

void CMeshWorksView::OnViewDynamiczoom()
{
	// TODO: Add your command handler code here
	m_GLKernelView->clear_tools();
	m_GLKernelView->set_tool(new CameraTool(m_GLKernelView, ZOOM));
}

void CMeshWorksView::OnViewZoomin()
{
	// TODO: Add your command handler code here
	m_GLKernelView->zoom(1.5);
}

void CMeshWorksView::OnViewZoomout()
{
	// TODO: Add your command handler code here
	m_GLKernelView->zoom(0.75);
}

void CMeshWorksView::OnViewZoomall()
{
	// TODO: Add your command handler code here
	m_GLKernelView->zoom_all_in_view();
}

void CMeshWorksView::OnViewGlobalaxis()
{
	// TODO: Add your command handler code here
	m_GLKernelView->SetAxisDisplay(!(m_GLKernelView->GetAxisDisplay()));
	m_GLKernelView->refresh();
}

BOOL CMeshWorksView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (zDelta >= 0)
		m_GLKernelView->zoom(1.5);
	else m_GLKernelView->zoom(0.75);

	return nFlags;
}

void CMeshWorksView::OnViewPolycount()
{
	// TODO: Add your command handler code here
	//m_GLKernelView->draw_text_2d(0, 0, "ffdsfsdf");
}

void CMeshWorksView::OnViewShading()
{
	// TODO: Add your command handler code here
	m_GLKernelView->SetShading(!m_GLKernelView->GetShading());
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnViewProfile()
{
	// TODO: Add your command handler code here
	m_GLKernelView->SetProfile(!m_GLKernelView->GetProfile());
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnViewMesh()
{
	// TODO: Add your command handler code here
	m_GLKernelView->SetMesh(!m_GLKernelView->GetMesh());
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnViewNode()
{
	// TODO: Add your command handler code here
	//CMeshWorksDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//pDoc->m_NodeDisplay=!(pDoc->m_NodeDisplay);
	/*if (pDoc->m_NodeDisplay) {
		for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
			QMeshPatch *mesh=((QBody*)pDoc->m_meshList.GetNext(Pos))->GetMeshPatch();
			mesh->SetAttribFlag(3, TRUE);
		}
	}
	else {
		for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
			QMeshPatch *mesh=((QBody*)pDoc->m_meshList.GetNext(Pos))->GetMeshPatch();
			mesh->SetAttribFlag(3, FALSE);
		}
	}*/
	m_GLKernelView->SetNode(!m_GLKernelView->GetNode());
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnUpdateViewShading(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->GetShading()) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnUpdateViewProfile(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->GetProfile()) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnUpdateViewMesh(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->GetMesh()) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnUpdateViewNode(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->GetNode()) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnUpdateViewGlobalaxis(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_GLKernelView->GetAxisDisplay());
}

void CMeshWorksView::OnViewSeed()
{
	// TODO: Add your command handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_SeedDisplay = !(pDoc->m_SeedDisplay);
	if (pDoc->m_SeedDisplay) {
		for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
			QMeshPatch *mesh=((QBody*)pDoc->m_meshList.GetNext(Pos))->GetMeshPatch();
			mesh->SetAttribFlag(4, TRUE);
		}
	}
	else {
		for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
			QMeshPatch *mesh=((QBody*)pDoc->m_meshList.GetNext(Pos))->GetMeshPatch();
			mesh->SetAttribFlag(4, FALSE);
		}
	}
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnViewNormal()
{
	// TODO: Add your command handler code here
	m_GLKernelView->SetNodeNormal(!m_GLKernelView->GetNodeNormal());
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnUpdateViewNormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->GetNodeNormal()) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnViewLight()
{
	// TODO: Add your command handler code here
	m_GLKernelView->m_lightON = !m_GLKernelView->m_lightON;
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnUpdateViewLight(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_GLKernelView->m_lightON) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnViewCrossSectionVolume()
{
	// TODO: Add your command handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_GLKernelView->clear_tools();
	SelectBoardTool *sbt = new SelectBoardTool(this, ((QBody*)pDoc->m_meshList.GetHead())->GetMeshPatch());
	m_GLKernelView->set_tool(sbt);

	if (CrossSectionControl){
		delete CrossSectionControl;
		CrossSectionControl=NULL;
	}
	CrossSectionControl = new CDlgCrossSection(this, sbt);
	CrossSectionControl->Create(IDD_CROSSSECTIONVOLUME, this);
	CrossSectionControl->ShowWindow(SW_SHOW);
}

void CMeshWorksView::OnUpdateViewCrossSectionVolume(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_meshList.GetCount()>0 && (((QBody*)pDoc->m_meshList.GetHead())->GetMeshPatch())->isVolume)
		pCmdUI->Enable();
	else pCmdUI->Enable(0);
}

void CMeshWorksView::UpdateCrossSectionDialog(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z){
	if (!CrossSectionControl) return;
	CrossSectionControl->UpdateValues(min_x, max_x, min_y, max_y, min_z, max_z);
}
void CMeshWorksView::OnShadingFacenormal()
{
	// TODO: Add your command handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
		QBody *mesh=(QBody*)pDoc->m_meshList.GetNext(Pos);
		mesh->shadenormal=1;
	}
	
	m_GLKernelView->RedrawAll();
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnShadingNodenormal()
{
	// TODO: Add your command handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
		QBody *mesh=(QBody*)pDoc->m_meshList.GetNext(Pos);
		mesh->shadenormal=0;
	}
	
	m_GLKernelView->RedrawAll();
	m_GLKernelView->refresh();
}

void CMeshWorksView::OnUpdateShadingFacenormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int shade=0;
	for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
		QBody *mesh=(QBody*)pDoc->m_meshList.GetNext(Pos);
		shade=mesh->shadenormal;
		break;
	}

	if (shade==1) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CMeshWorksView::OnUpdateShadingNodenormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CMeshWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int shade=0;
	for(POSITION Pos=pDoc->m_meshList.GetHeadPosition();Pos!=NULL;) {
		QBody *mesh=(QBody*)pDoc->m_meshList.GetNext(Pos);
		shade=mesh->shadenormal;
		break;
	}

	if (shade==0) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

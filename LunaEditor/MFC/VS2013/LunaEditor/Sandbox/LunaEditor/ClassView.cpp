<!DOCTYPE html>
<html lang="en">
<head>
	<title>The PowerVR SDK Browser</title>
	<meta charset="UTF-8" />
	<link rel="stylesheet" type="text/css" href="style.css">
    <link rel="icon" type="image/png" href="./images/img-icon.png">
</head>

<body>
	<div id="GlobalHeaderContainer">
		<div id="GlobalHeader">
			<div class="logo">
				<a href="http://www.powervrinsider.com" target="_blank"><img src="./images/PVRlogo.png" width="40%" height="40%" /></a>
            </div>
			<div class="sitetitle">PowerVR SDK Browser</div>
		</div>
	</div>
	<div id="NavContainer">
		<nav>
			<div class="navlink">
				<a href="Home.html">Home</a>
			</div>
			<div class="navlink">
				<a href="GettingStarted.html">Getting Started</a>
			</div>
			<div class="navlink">
				<a href="Examples.html">Examples</a>
			</div>
			<div class="navlink">
				<a href="Framework.html">Framework</a>
			</div>
			<div class="navlink">
				<a href="Documentation.html">Documentation</a>
			</div>
			<div class="navlink">
				<a href="PowerVRTools.html">PowerVR Tools</a>
			</div>
			<div class="navlink">
				<a href="ReleaseNotes.html">Release Notes</a>
			</div>
			<div class="navlink">
				<a href="Contact.html" class="current">Contact Us</a>
			</div>
		</nav>
	</div>

    <div class="content">
        <h1>Contact Details</h1>
		<h3>Forum</h3>
		<p>For further support, please visit our <a href="http://forum.imgtec.com" target="_blank">forum</a>.</p>
		<h3>Support and Ticketing System</h3>
		<p>Alternatively, file a ticket in our <a href="https://pvrsupport.imgtec.com" target="_blank">support system</a>.</p>
		<h3>PowerVR Insider</h3>
		<p>To learn more about our PowerVR Graphics SDK and Insider programme, please visit our <a href="http://www.powervrinsider.com" target="_blank">community webpages</a>.</p>
		<h3>General Enquiries</h3>
		<p>For general enquiries, please visit our <a href="http://www.imgtec.com/about/contactus.asp" target="_blank">corporate website</a>.</p>
		<hr />
		<h3>Further Contact Info</h3>
		Imagination Technologies Ltd.<br />
		Home Park Estate<br />
		Kings Langley<br />
		Hertfordshire, WD4 8LZ<br />
		United Kingdom</p>
		<p>Tel: +44 (0)1923 260511</p>
		<p>Fax: +44 (0)1923 277463</p>
    </div>
	<br>
    <div id="FooterMainContainer">
		<div id="FooterContainer">
			<div class="footerlogo">
				<a href="http://www.imgtec.com" target="_blank"><img src="./images/img-footer-logo-grey.png" width="100%" height="100%" /></a>
			</div>
			<div class="copyright">&copy; Imagination Technologies Limited<br> All rights reserved</div>
		</div>
	</div>
</body>

</html>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 3, hClass);
	m_wndClassView.InsertItem(_T("InitInstance()"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("OnAppAbout()"), 3, 3, hClass);

	hClass = m_wndClassView.InsertItem(_T("CFakeAppDoc"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("CFakeAppDoc()"), 4, 4, hClass);
	m_wndClassView.InsertItem(_T("~CFakeAppDoc()"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("OnNewDocument()"), 3, 3, hClass);

	hClass = m_wndClassView.InsertItem(_T("CFakeAppView"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("CFakeAppView()"), 4, 4, hClass);
	m_wndClassView.InsertItem(_T("~CFakeAppView()"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("GetDocument()"), 3, 3, hClass);
	m_wndClassView.Expand(hClass, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("CFakeAppFrame"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("CFakeAppFrame()"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("~CFakeAppFrame()"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("m_wndMenuBar"), 6, 6, hClass);
	m_wndClassView.InsertItem(_T("m_wndToolBar"), 6, 6, hClass);
	m_wndClassView.InsertItem(_T("m_wndStatusBar"), 6, 6, hClass);

	hClass = m_wndClassView.InsertItem(_T("Globals"), 2, 2, hRoot);
	m_wndClassView.InsertItem(_T("theFakeApp"), 5, 5, hClass);
	m_wndClassView.Expand(hClass, TVE_EXPAND);
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CClassView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("添加成员函数..."));
}

void CClassView::OnClassAddMemberVariable()
{
	// TODO:  在此处添加命令处理程序代码
}

void CClassView::OnClassDefinition()
{
	// TODO:  在此处添加命令处理程序代码
}

void CClassView::OnClassProperties()
{
	// TODO:  在此处添加命令处理程序代码
}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("新建文件夹..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}

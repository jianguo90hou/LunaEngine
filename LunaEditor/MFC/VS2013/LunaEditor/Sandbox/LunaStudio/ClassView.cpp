�PNG

   IHDR   `   `   �w8   	pHYs    ��~�  SIDATx���j�@��S�4�S��Н+�PW���EA*�BA� E�"E�b�hu�E���u��G�8�Lr�̽�o�,��drs�9�Lr'��,d�t2�@ $   � �D �M��^�de#����}��-�5��~�*[���]:~^ ���BfM��ǽ� 4P�ۭ�����Dk p3]5,��ɫ���GO�>��;�5L�Y��i@�Jʷ����݇y��b��43�*Ț�o,P`�	¤���f���"&�B# e������*A�!+��!�I��U��>���(9+�2�߅�c �G ���1qG!Wd./&���:��}�oB�Ǭ K,���*�2א$ݵ>�뒹��}���%��/�7mQ�%�� ��ek�27��zp B7EJ�"s�,���}�{�ƅ�vCn�KB�u >��rJ�7�(9��ƍ� _�_ z�KA q�� Rd�*A�z�gt B��T�R���6�SŁQ��Sl�@�֞�
F	����GQ���]g� B�PO(�m�g� Be	+�u�9c�X�xL�������r���6b�T�A	@DZ��P5�\����&�.��}��~�!7F�c�p��*� ��3n�-�"��.ޔ�:�	@E���KUý�� D��&���jpieA[ �'��^2��fbW��X@ @ f��4  ��`���[0MD������ H@ $   � �d� lm���.�9s��/?�>�~������go6���gr��b�|�iޏƹ�!  �-��

�s�o���A�v܀�PtQ�C�����XP�~��ʲ�"���M�.Ę��A�\�f?���Ԯh� �,������l�pK��Y ��؛�j_�����UtMʂ
�(������z��,�,H�@�0�k�YM����j��*A�4ƍqC�}�	�U
�p/���
 �?�"�,�C,0 �5UeUP3���w[%��C�k��R�oq�+EX=���t���վ�Z � l��ԙ�\�3����Ҁ���w�ӗT6u�r��$   E� H`���g3�f�    IEND�B`�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               1, hRoot);
	m_wndClassView.InsertItem(_T("CFakeApp()"), 3, 3, hClass);
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
	//CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	//ASSERT_VALID(pWndTree);

	//if (pWnd != pWndTree)
	//{
	//	CDockablePane::OnContextMenu(pWnd, point);
	//	return;
	//}

	//if (point != CPoint(-1, -1))
	//{
	//	// ѡ���ѵ�������: 
	//	CPoint ptTree = point;
	//	pWndTree->ScreenToClient(&ptTree);

	//	UINT flags = 0;
	//	HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
	//	if (hTreeItem != NULL)
	//	{
	//		pWndTree->SelectItem(hTreeItem);
	//	}
	//}

	//pWndTree->SetFocus();
	//CMenu menu;
	//menu.LoadMenu(IDR_POPUP_SORT);

	//CMenu* pSumMenu = menu.GetSubMenu(0);

	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	//{
	//	CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

	//	if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
	//		return;

	//	((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
	//	UpdateDialogControls(this, FALSE);
	//}
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
	AfxMessageBox(_T("���ӳ�Ա����..."));
}

void CClassView::OnClassAddMemberVariable()
{
	// TODO:  �ڴ˴�����������������
}

void CClassView::OnClassDefinition()
{
	// TODO:  �ڴ˴�����������������
}

void CClassView::OnClassProperties()
{
	// TODO:  �ڴ˴�����������������
}

void CClassView::OnNewFolder()
{
	AfxMessageBox(_T("�½��ļ���..."));
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

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
	//m_ClassViewImages.DeleteImageList();

	//UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	//CBitmap bmp;
	//if (!bmp.LoadBitmap(uiBmpId))
	//{
	//	TRACE(_T("�޷�����λͼ:  %x\n"), uiBmpId);
	//	ASSERT(FALSE);
	//	return;
	//}

	//BITMAP bmpObj;
	//bmp.GetBitmap(&bmpObj);

	//UINT nFlags = ILC_MASK;

	//nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	//m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	//m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	//m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* ����*/);
}

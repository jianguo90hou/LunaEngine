INDX( 	 l�v�          (   @  �            ��            ^6    X F     �(     Orq4KW�e�q4KW�e�q4KW�e�q4KW�                        c b   �5    X F     �(     5���JW�����JW�����JW�����JW�                        c c   5    X F     �(     ��#IW��=�#IW��=�#IW��=�#IW�                        c e   �4    X F     �(     ���IW����IW����IW����IW�                        c f   5    X F     �(     h�j#IW���j#IW���j#IW���j#IW�                        d 0   �5    X F     �(     ���+KW�%9�KW�%9�KW�%9�KW�                        d 1   �4    X F     �(     �aIW���{KW���{KW���{KW�                        d 3   �4    X F     �(     i�bIW�i�bIW�i�bIW�i�bIW�                        d 4   L5    X F     �(     3�IW�*m�IW�*m�IW�*m�IW�                        d 5   �5    X F     �(     ����JW�����JW�����JW�����JW�                        d 6   �6    X F     �(     |QxKW�exKW�exKW�exKW�                       d 7   �4    X F     �(     �xEIW�����JW�����JW�����JW�                        d 8   B6    X F     �(     �%�3KW��9�3KW��9�3KW��9�3KW�                        d b   �5    X F     �(     J��JW�ӡ�JW�ӡ�JW�ӡ�JW�                        d d   �5    X F     �(     !��1KW��m1�KW��m1�KW��m1�KW�                        d e   �5    X F     �(     U)��JW�U)��JW�U)��JW�U)��JW�                        e 1   �5    X F     �(     Uj�JW���m4KW���m4KW���m4KW�                       e 3   �5    X F     �(     ZFY#KW�jmY#KW�jmY#KW�jmY#KW�                        e 4   �6    X F     �(     <�3wKW��ixKW��ixKW��ixKW�                        e 5   �5    X F     �(     ����JW�f
��JW�f
��JW�f
��JW�                        e 6   �4    X F     �(     ��?IW�'@IW�'@IW�'@IW�                        e 7   �4    X F     �(     e�IW�:�IW�:�IW�:�IW�                        e 8   N6    X F     �(     ��,4KW�I�,4KW�I�,4KW I�,4KW�                        e a   G6    X F     �(     �N*4KW��b*4KW��b*4KW��b*4KW�                        e b   �5    X F     �(     9W�JW��(W�JW��(W�JW��(W�JW�                        e d   �6    X F     �(     �q�KW��q�KW��q�KW��q�KW�                        e e   y5    X F     �(     �Ym�JW��Ym�JW��Ym�JW��Ym�JW�                        f 1   �4    X F     �(     di�IW��|�IW��|�IW��|�IW�                        f 3   �4    X F     �(     �!IW �j!IW��j!IW��j!IW�                        f 4   �5    X F     �(     r��JW��DxKW��DxKW��DxKW�                        f 5   �5    X F     �(     ;��JW��N��JW��N��JW��N��JW�                        f 8   �4    X F     �(     �C�IW���܏KW���܏KW���܏KW�                        f a   �6    X F     �(     �NxKW��NxKW��NxKW��NxKW�                        f b   �4    X F     �(     �IW�	IW�	IW�	IW�                        f d   G2    X F    �(     �\IW���� IW���� IW���� IW�                        f f                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       �������������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO:  �ڴ˴������������ UI �����������
}

void CPropertiesWnd::OnProperties2()
{
	// TODO:  �ڴ˴�����������������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO:  �ڴ˴������������ UI �����������
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("���"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("��ά���"), (_variant_t) false, _T("ָ�����ڵ����岻ʹ�ô��壬���ҿؼ���ʹ����ά�߿�")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߿�"), _T("�Ի������"), _T("����֮һ: ���ޡ�����ϸ�������ɵ�����С���򡰶Ի������"));
	pProp->AddOption(_T("��"));
	pProp->AddOption(_T("ϸ"));
	pProp->AddOption(_T("�ɵ�����С"));
	pProp->AddOption(_T("�Ի������"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T("����"), _T("ָ�����ڱ���������ʾ���ı�")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250l, _T("ָ�����ڵĸ߶�"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("����"), (_variant_t) 150l, _T("ָ�����ڵĿ���"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("����, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("����"));
	pProp = new CMFCPropertyGridProperty(_T("(����)"), _T("Ӧ�ó���"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("ͼ���ļ�(*.ico)|*.ico|�����ļ�(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("ָ������ͼ��")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ļ���"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("��νṹ"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("��һ���Ӽ�"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�ڶ����Ӽ�"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 1"), (_variant_t) _T("ֵ 1"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 2"), (_variant_t) _T("ֵ 2"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 3"), (_variant_t) _T("ֵ 3"), _T("��Ϊ˵��")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

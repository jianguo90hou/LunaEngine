aster\DockSample\Images\ClosedFolder.ICO"   ^D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\CSFile.ico#   aD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\CSProject.ico$   \D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\File.ico%   \D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\Form.ico&   ]D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\Mouse.bmp'   _D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\msenv22.ico(   [D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\New.ico)   \D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\Open.ico*   bD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\OpenFolder.ICO+   dD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\OutputWindow.ico,   fD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\PropertyWindow.ico-   aD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\Reference.ico.   bD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\References.ico/   hD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\SolutionExplorer.ico0   fD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\TaskListWindow.ico1   eD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\ToolboxWindow.ico2   _D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\Images\XmlFile.ico3   XD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\DockSample\license.txt4   :C:\Windows\Microsoft.NET\Framework\v2.0.50727\mscorlib.dll5   TC:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\v3.5\System.Core.dll6   =C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Data.dll7   8C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.dll8   @C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Drawing.dll9   FC:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Windows.Forms.dll:   <C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Xml.dll;   fD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\ThemeVS2003.dll<   kD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\ThemeVS2012Light.dll=   jD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\ThemeVS2013Blue.dll>   wD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\WeifenLuo.WinFormsUI.Docking.dll   �System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]]   _items_size_version  �System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089;

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("�������"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("������"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}

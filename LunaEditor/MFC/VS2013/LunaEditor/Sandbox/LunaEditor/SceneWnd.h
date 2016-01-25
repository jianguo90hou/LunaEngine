
#pragma once

//class SceneWndRenderer;
//#include "LunaEnginePCH.h"

class CSceneWnd : public CDockablePane
{
// ππ‘Ï
public:
	CSceneWnd();

	virtual ~CSceneWnd();
	void Update();

private:
	//SceneWndRenderer* m_pSceneWndRenderer;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	//IDirect3DSwapChain9* m_pSwapChain;
};


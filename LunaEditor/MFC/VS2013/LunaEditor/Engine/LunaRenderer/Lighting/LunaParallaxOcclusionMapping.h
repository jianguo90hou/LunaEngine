
#pragma once

#include "../DXUT11/DXUT.h"

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN           1
#define IDC_TOGGLEREF                  3
#define IDC_CHANGEDEVICE               4
#define IDC_HEIGHT_SCALE_SLIDER        5
#define IDC_HEIGHT_SCALE_STATIC        6
#define IDC_TOGGLE_SHADOWS             7
#define IDC_SELECT_TEXTURES_COMBOBOX   8
#define IDC_TOGGLE_SPECULAR            9
#define IDC_SPECULAR_EXPONENT_SLIDER   10
#define IDC_SPECULAR_EXPONENT_STATIC   11
#define IDC_MIN_NUM_SAMPLES_SLIDER     12
#define IDC_MIN_NUM_SAMPLES_STATIC     13
#define IDC_MAX_NUM_SAMPLES_SLIDER     14
#define IDC_MAX_NUM_SAMPLES_STATIC     15
#define IDC_TECHNIQUE_COMBO_BOX        16
#define IDC_RELOAD_BUTTON              20

//--------------------------------------------------------------------------------------
// Texture pair ids for use for this sample
//--------------------------------------------------------------------------------------
enum POM_TEXTURE_IDS
{
	POM_STONES = 0,
	POM_ROCKS,
	POM_WALL,
	POM_FOUR_BUMPS,
	POM_BUMPS,
	POM_DENTS,
	POM_SAINT
};

//--------------------------------------------------------------------------------------
// Id numbers for different rendering techniques used
//--------------------------------------------------------------------------------------
enum TECHNIQUE_IDS
{
	POM,           // Parallax occlusion mapping
	BUMPMAP,       // Bump mapping
	PM             // Parallax mapping with offset limiting
};

class LunaParallaxOcclusionMaping
{
public:
	LunaParallaxOcclusionMaping();
	~LunaParallaxOcclusionMaping();
	//--------------------------------------------------------------------------------------
	// Forward declarations 
	//--------------------------------------------------------------------------------------
	bool IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
	bool ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
	HRESULT OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,	void* pUserContext);
	HRESULT OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,	void* pUserContext);
	void OnFrameMove(double fTime, float fElapsedTime, void* pUserContext);
	void OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void KeyboardProc(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);
	void OnLostDevice(void* pUserContext);
	void OnDestroyDevice(void* pUserContext);

private:
	void InitApp();
	HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh);
	void RenderText(double fTime);
	void SetPOMTextures(int iTextureIndex);
private:

	//--------------------------------------------------------------------------------------
	IDirect3DDevice9*           g_pD3DDevice = NULL;       // A pointer to the current D3D device used for rendering

	ID3DXFont*                  g_pFont = NULL;        // Font for drawing text
	ID3DXSprite*                g_pSprite = NULL;        // Sprite for batching draw text calls
	bool                        g_bShowHelp = false;       // If true, it renders the UI control text
	CModelViewerCamera          g_Camera;                  // A model viewing camera
	ID3DXEffect*                g_pEffect = NULL;        // D3DX effect interface

	ID3DXMesh*                  g_pMesh = NULL;            // Mesh object

	IDirect3DTexture9**         g_pBaseTextures = NULL;    // Array of base map texture surfaces
	IDirect3DTexture9**         g_pNMHTextures = NULL;    // Array of normal / height map texture surfaces
	//       a height map in the alpha channel

	CDXUTDialogResourceManager  g_DialogResourceManager;   // manager for shared resources of dialogs
	CD3DSettingsDlg             g_SettingsDlg;             // Device settings dialog
	CDXUTDialog                 g_HUD;                     // manages the 3D UI
	CDXUTDialog                 g_SampleUI;                // dialog for sample specific controls
	D3DXMATRIXA16               g_mWorldFix;

	CDXUTDirectionWidget        g_LightControl;            // Scene light
	float                       g_fLightScale;             // Light brightness scale parameter


	//--------------------------------------------------------------------------------------
	// UI scalar parameters
	//--------------------------------------------------------------------------------------
	const float                 s_fLightScaleUIScale = 10.0f;
	const int                   s_iLightScaleSliderMin = 0;
	const int                   s_iLightScaleSliderMax = 20;

	int                         g_iHeightScaleSliderMin = 0;
	int                         g_iHeightScaleSliderMax = 100;
	float                       g_fHeightScaleUIScale = 100.0f;

	const int                   s_iSliderMin = 8;
	const int                   s_iSliderMax = 130;

	//--------------------------------------------------------------------------------------
	// Material properties parameters:
	//--------------------------------------------------------------------------------------
	D3DXCOLOR                   g_colorMtrlDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR                   g_colorMtrlAmbient(0.35f, 0.35f, 0.35f, 0);
	D3DXCOLOR                   g_colorMtrlSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	float                       g_fSpecularExponent(60.0f);        // Material's specular exponent
	float                       g_fBaseTextureRepeat(1.0f);        // The tiling factor for base and normal map textures

	bool                        g_bVisualizeLOD(false);            // Toggles visualization of level of detail colors
	bool                        g_bVisualizeMipLevel(false);       // Toggles visualization of mip level
	bool                        g_bDisplayShadows(true);           // Toggles display of self-occlusion based shadows
	bool                        g_bAddSpecular(true);              // Toggles rendering with specular or without
	bool                        g_bRenderPOM(true);                // Toggles whether using normal mapping or parallax occlusion mapping

	int                         g_nLODThreshold(3);                // The mip level id for transitioning between the full computation
	// for parallax occlusion mapping and the bump mapping computation
	int                         g_nMinSamples(8);                  // The minimum number of samples for sampling the height field profile
	int                         g_nMaxSamples(50);                 // The maximum number of samples for sampling the height field profile
	float                       g_fShadowSoftening(0.58f);         // Blurring factor for the soft shadows computation
	float                       g_fHeightScale;                    // This parameter controls the height map range for displacement mapping

	//--------------------------------------------------------------------------------------
	// Mesh file names for use
	//--------------------------------------------------------------------------------------
	WCHAR*                      g_strMeshFileName0 = TEXT("Disc.x");


};


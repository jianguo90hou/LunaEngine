
#pragma once

#include "../DXUT11/DXUT.h"

//--------------------------------------------------------------------------------------
// Defines, and constants
//--------------------------------------------------------------------------------------
#define ENVMAPSIZE 256
#define NUM_LIGHTS 4  // Currently, 4 is the only number of lights supported.
#define LIGHTMESH_RADIUS 0.2f
#define HELPTEXTCOLOR D3DXCOLOR( 0.0f, 1.0f, 0.3f, 1.0f )


//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN  1
#define IDC_TOGGLEREF         3
#define IDC_CHANGEDEVICE      4
#define IDC_CHANGEMESH        5
#define IDC_RESETPARAM        6
#define IDC_SLIDERLIGHTTEXT   7
#define IDC_SLIDERLIGHT       8
#define IDC_SLIDERREFLECTTEXT 9
#define IDC_SLIDERREFLECT     10
#define IDC_CHECKHDR          11

//--------------------------------------------------------------------------------------
struct ORBITDATA
{
	LPCTSTR tszXFile;  // X file
	D3DVECTOR vAxis;     // Axis of rotation
	float fRadius;   // Orbit radius
	float fSpeed;    // Orbit speed in radians per second
};


//--------------------------------------------------------------------------------------
// Encapsulate an object in the scene with its world transformation
// matrix.
//--------------------------------------------------------------------------------------
struct CObj
{
	D3DXMATRIXA16 m_mWorld;  // World transformation
	CDXUTXFileMesh m_Mesh;    // Mesh object

public:
	CObj()
	{
		D3DXMatrixIdentity(&m_mWorld);
	}
	~CObj()
	{
	}
	HRESULT WorldCenterAndScaleToRadius(float fRadius)
	{
		//
		// Compute the world transformation matrix
		// to center the mesh at origin in world space
		// and scale its size to the specified radius.
		//
		HRESULT hr;

		float fRadiusBound;
		D3DXVECTOR3 vCtr;
		if (FAILED(hr = ::ComputeBoundingSphere(m_Mesh, &vCtr, &fRadiusBound)))
			return hr;

		D3DXMatrixTranslation(&m_mWorld, -vCtr.x, -vCtr.y, -vCtr.z);
		D3DXMATRIXA16 mScale;
		D3DXMatrixScaling(&mScale, fRadius / fRadiusBound,
			fRadius / fRadiusBound,
			fRadius / fRadiusBound);
		D3DXMatrixMultiply(&m_mWorld, &m_mWorld, &mScale);

		return hr;
	}  // WorldCenterAndScaleToRadius
};


//--------------------------------------------------------------------------------------
// Encapsulate an orbiter object in the scene with related data
//--------------------------------------------------------------------------------------
class COrbiter : public CObj
{
public:
	D3DXVECTOR3 m_vAxis;       // orbit axis
	float m_fRadius;     // orbit radius
	float m_fSpeed;      // Speed, angle in radian per second

public:
	COrbiter() : m_vAxis(0.0f, 1.0f, 0.0f),
		m_fRadius(1.0f),
		m_fSpeed(D3DX_PI)
	{
	}
	void    SetOrbit(D3DXVECTOR3& vAxis, float fRadius, float fSpeed)
	{
		// Call this after m_mWorld is initialized
		m_vAxis = vAxis; m_fRadius = fRadius; m_fSpeed = fSpeed;
		D3DXVec3Normalize(&m_vAxis, &m_vAxis);

		// Translate by m_fRadius in -Y direction
		D3DXMATRIXA16 m;
		D3DXMatrixTranslation(&m, 0.0f, -m_fRadius, 0.0f);
		D3DXMatrixMultiply(&m_mWorld, &m_mWorld, &m);

		// Apply rotation from X axis to the orbit axis
		D3DXVECTOR3 vX(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vRot;
		D3DXVec3Cross(&vRot, &m_vAxis, &vX);  // Axis of rotation
		// If the cross product is 0, m_vAxis is on the X axis
		// So we either rotate 0 or PI.
		if (D3DXVec3LengthSq(&vRot) == 0)
		{
			if (m_vAxis.x < 0.0f)
				D3DXMatrixRotationY(&m, D3DX_PI); // PI
			else
				D3DXMatrixIdentity(&m);           // 0
		}
		else
		{
			float fAng = (float)acos(D3DXVec3Dot(&m_vAxis, &vX));  // Angle to rotate
			// Find out direction to rotate
			D3DXVECTOR3 vXxRot;  // X cross vRot
			D3DXVec3Cross(&vXxRot, &vX, &vRot);
			if (D3DXVec3Dot(&vXxRot, &m_vAxis) >= 0)
				fAng = -fAng;
			D3DXMatrixRotationAxis(&m, &vRot, fAng);
		}
		D3DXMatrixMultiply(&m_mWorld, &m_mWorld, &m);
	}

	void    Orbit(float fElapsedTime)
	{
		// Compute the orbit transformation and apply to m_mWorld
		D3DXMATRIXA16 m;

		D3DXMatrixRotationAxis(&m, &m_vAxis, m_fSpeed * fElapsedTime);
		D3DXMatrixMultiply(&m_mWorld, &m_mWorld, &m);
	}
};


//--------------------------------------------------------------------------------------
#pragma warning( disable : 4324 )
struct CLight
{
	D3DXVECTOR4 vPos;      // Position in world space
	D3DXVECTOR4 vMoveDir;  // Direction in which it moves
	float fMoveDist; // Maximum distance it can move
	D3DXMATRIXA16 mWorld;    // World transform matrix for the light before animation
	D3DXMATRIXA16 mWorking;  // Working matrix (world transform after animation)
};


//--------------------------------------------------------------------------------------
struct CTechniqueGroup
{
	D3DXHANDLE hRenderScene;
	D3DXHANDLE hRenderLight;
	D3DXHANDLE hRenderEnvMap;
};


class LunaHDRCubeMap
{
public:
	LunaHDRCubeMap();
	~LunaHDRCubeMap();

	//--------------------------------------------------------------------------------------
	// Forward declarations 
	//--------------------------------------------------------------------------------------
	bool IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed,	void* pUserContext);
	bool ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
	HRESULT OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void OnFrameMove(double fTime, float fElapsedTime, void* pUserContext);
	void OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void KeyboardProc(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);
	void OnLostDevice(void* pUserContext);
	void OnDestroyDevice(void* pUserContext);
private:
	void InitApp();
	HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, LPCWSTR wszName, CDXUTXFileMesh& Mesh);
	void RenderText();
	void ResetParameters();
	void RenderSceneIntoCubeMap(IDirect3DDevice9* pd3dDevice, double fTime);
	void RenderScene(IDirect3DDevice9* pd3dDevice, const D3DXMATRIX* pmView, const D3DXMATRIX* pmProj, CTechniqueGroup* pTechGroup, bool bRenderEnvMappedMesh, double fTime);
	void UpdateUiWithChanges();

	HRESULT ComputeBoundingSphere(CDXUTXFileMesh& Mesh, D3DXVECTOR3* pvCtr, float* pfRadius);

private:

	//--------------------------------------------------------------------------------------
	// Global variables
	//--------------------------------------------------------------------------------------
	ID3DXFont*                      g_pFont = NULL;            // Font for drawing text
	ID3DXSprite*                    g_pTextSprite = NULL;      // Sprite for batching draw text calls
	ID3DXEffect*                    g_pEffect = NULL;          // D3DX effect interface
	CModelViewerCamera              g_Camera;                  // A model viewing camera
	bool                            g_bShowHelp = true;        // If true, it renders the UI control text
	CDXUTDialogResourceManager      g_DialogResourceManager;   // manager for shared resources of dialogs
	CD3DSettingsDlg                 g_SettingsDlg;             // Device settings dialog
	CDXUTDialog                     g_HUD;                     // dialog for standard controls
	CLight g_aLights[NUM_LIGHTS];     // Parameters of light objects
	D3DXVECTOR4                     g_vLightIntensity;         // Light intensity
	CObj g_EnvMesh[NUM_MESHES];     // Mesh to receive environment mapping
	int                             g_nCurrMesh = 0;           // Index of the element in m_EnvMesÙÕù ¡c×ÿÿÿÿZÔï  C                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             Õ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
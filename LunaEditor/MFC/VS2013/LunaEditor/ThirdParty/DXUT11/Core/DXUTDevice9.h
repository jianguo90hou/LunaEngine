pe large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
typedef khronos_int32_t EGLint;

#endif /* __eglplatform_h */
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ufferFormat, pD3D9DeviceSettings->pp.Windowed ); }
    CD3D9EnumDeviceSettingsCombo*            GetDeviceSettingsCombo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL Windowed );  

    ~CD3D9Enumeration();

private:
    friend HRESULT WINAPI DXUTCreateD3D9Enumeration();

    // Use DXUTGetD3D9Enumeration() to access global instance
    CD3D9Enumeration();

    bool m_bHasEnumerated;
    IDirect3D9* m_pD3D;                                    
    LPDXUTCALLBACKISD3D9DEVICEACCEPTABLE m_IsD3D9DeviceAcceptableFunc;
    void* m_pIsD3D9DeviceAcceptableFuncUserContext;
    bool m_bRequirePostPixelShaderBlending;
    CGrowableArray<D3DFORMAT> m_DepthStencilPossibleList;
    CGrowableArray<D3DMULTISAMPLE_TYPE> m_MultiSampleTypeList;
    CGrowableArray<UINT> m_PresentIntervalList;

    bool m_bSoftwareVP;
    bool m_bHardwareVP;
    bool m_bPureHarewareVP;
    bool m_bMixedVP;

    UINT m_nMinWidth;
    UINT m_nMaxWidth;
    UINT m_nMinHeight;
    UINT m_nMaxHeight;
    UINT m_nRefreshMin;
    UINT m_nRefreshMax;
    UINT m_nMultisampleQualityMax;

    // Array of CD3D9EnumAdapterInfo* with unique AdapterOrdinals
    CGrowableArray<CD3D9EnumAdapterInfo*> m_AdapterInfoList;  

    HRESULT EnumerateDevices( CD3D9EnumAdapterInfo* pAdapterInfo, CGrowableArray<D3DFORMAT>* pAdapterFormatList );
    HRESULT EnumerateDeviceCombos( CD3D9EnumAdapterInfo* pAdapterInfo, CD3D9EnumDeviceInfo* pDeviceInfo, CGrowableArray<D3DFORMAT>* pAdapterFormatList );
    void BuildDepthStencilFormatList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
    void BuildMultiSampleTypeList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
    void BuildDSMSConflictList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
    void BuildPresentIntervalList( CD3D9EnumDeviceInfo* pDeviceInfo, CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
    void ClearAdapterInfoList();
};

CD3D9Enumeration*   WINAPI DXUTGetD3D9Enumeration( bool bForceEnumerate = false );


//--------------------------------------------------------------------------------------
// A class describing an adapter which contains a unique adapter ordinal 
// that is installed on the system
//--------------------------------------------------------------------------------------
class CD3D9EnumAdapterInfo
{
public:
    ~CD3D9EnumAdapterInfo();

    UINT AdapterOrdinal;
    D3DADAPTER_IDENTIFIER9 AdapterIdentifier;
    WCHAR   szUniqueDescription[256];

    CGrowableArray <D3DDISPLAYMODE> displayModeList; // Array of supported D3DDISPLAYMODEs
    CGrowableArray <CD3D9EnumDeviceInfo*> deviceInfoList; // Array of CD3D9EnumDeviceInfo* with unique supported DeviceTypes
};


//--------------------------------------------------------------------------------------
// A class describing a Direct3D device that contains a 
//       unique supported device type 
//--------------------------------------------------------------------------------------
class CD3D9EnumDeviceInfo
{
public:
    ~CD3D9EnumDeviceInfo();

    UINT AdapterOrdinal;
    D3DDEVTYPE DeviceType;
    D3DCAPS9 Caps;

    // List of CD3D9EnumDeviceSettingsCombo* with a unique set 
    // of AdapterFormat, BackBufferFormat, and Windowed
    CGrowableArray <CD3D9EnumDeviceSettingsCombo*> deviceSettingsComboList;
};


//--------------------------------------------------------------------------------------
// A struct describing device settings that contains a unique combination of 
// adapter format, back buffer format, and windowed that is compatible with a 
// particular Direct3D device and the app.
//--------------------------------------------------------------------------------------
struct CD3D9EnumDeviceSettingsCombo
{
    UINT AdapterOrdinal;
    D3DDEVTYPE DeviceType;
    D3DFORMAT AdapterFormat;
    D3DFORMAT BackBufferFormat;
    BOOL Windowed;

    CGrowableArray <D3DFORMAT> depthStencilFormatList; // List of D3DFORMATs
    CGrowableArray <D3DMULTISAMPLE_TYPE> multiSampleTypeList; // List of D3DMULTISAMPLE_TYPEs
    CGrowableArray <DWORD> multiSampleQualityList; // List of number of quality levels for each multisample type
    CGrowableArray <UINT> presentIntervalList; // List of D3DPRESENT flags
    CGrowableArray <CD3D9EnumDSMSConflict> DSMSConflictList; // List of CD3D9EnumDSMSConflict

    CD3D9EnumAdapterInfo* pAdapterInfo;
    CD3D9EnumDeviceInfo* pDeviceInfo;
};


//--------------------------------------------------------------------------------------
// A depth/stencil buffer format that is incompatible with a
// multisample type.
//--------------------------------------------------------------------------------------
struct CD3D9EnumDSMSConflict
{
    D3DFORMAT DSFormat;
    D3DMULTISAMPLE_TYPE MSType;
};



float   DXUTRankD3D9DeviceCombo( CD3D9EnumDeviceSettingsCombo* pDeviceSettingsCombo, 
                                DXUTD3D9DeviceSettings* pOptimalDeviceSettings, 
                                D3DDISPLAYMODE* pAdapterDesktopDisplayMode, 
                                int &bestModeIndex,
                                int &bestMSAAIndex                                
                                );


#endif

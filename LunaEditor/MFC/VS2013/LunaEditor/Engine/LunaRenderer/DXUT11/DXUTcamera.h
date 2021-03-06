#ifndef __eglplatform_h_
#define __eglplatform_h_

/*
** Copyright (c) 2007-2009 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Platform-specific types and definitions for egl.h
 * $Revision: 12306 $ on $Date: 2010-08-25 09:51:28 -0700 (Wed, 25 Aug 2010) $
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by sending them to the public Khronos Bugzilla (http://khronos.org/bugzilla)
 * by filing a bug against product "EGL" component "Registry".
 */

#include <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 *
 * Khronos STRONGLY RECOMMENDS that you use the default definitions
 * provided below, since these changes affect both binary and source
 * portability of applications using EGL running on different EGL
 * implementations.
 */

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

typedef HDC     EGLNativeDisplayType;
typedef HBITMAP EGLNativePixmapType;
typedef HWND    EGLNativeWindowType;

#elif defined(SUPPORT_X11)

/* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;


#elif defined(__ANDROID__) || defined(ANDROID)

#include <android/native_window.h>

struct egl_native_pixmap_t;

typedef struct ANativeWindow*           EGLNativeWindowType;
typedef struct egl_native_pixmap_t*     EGLNativePixmapType;
typedef void*                           EGLNativeDisplayType;

#else

#if defined(_WIN64) ||  __WORDSIZE == 64
typedef khronos_int64_t EGLNativeDisplayType;
#else
typedef int EGLNativeDisplayType;
#endif

typedef void *EGLNativeWindowType;
typedef void *EGLNativePixmapType;

#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral tyster\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PaneDiamond_HotspotIndex.png    ˘D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PaneDiamond_HotspotIndex_VS2012.png!   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PaneDiamond_Left.png"   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PaneDiamond_Right.png#   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PaneDiamond_Top.png$   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelBottom.png%   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelBottom_Active.png&   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelFill.png'   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelFill_Active.png(   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelLeft.png)   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelLeft_Active.png*   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelRight.png+   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelRight_Active.png,   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelTop.png-   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockIndicator_PanelTop_Active.png.   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockPane_AutoHide.png/   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockPane_Close.png0   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockPane_Dock.png1   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockPane_Option.png2   D:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\ThemeVS2005Multithreading\Resources\DockPane_OptionOverflow.png3   :C:\Windows\Microsoft.NET\Framework\v2.0.50727\mscorlib.dll4   =C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Data.dll5   8C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.dll6   @C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Drawing.dll7   FC:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Windows.Forms.dll8   <C:\Windows\Microsoft.NET\Framework\v2.0.50727\System.Xml.dll9   wD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\WeifenLuo.WinFormsUI.Docking.dll   System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]]   _items_size_version  ŻSystem.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]][]	:                 ;   .C:\Windows\Microsoft.NET\Framework\v2.0.50727\      <   Full      	:           	      	:           
             >   {CandidateAssemblyFiles}?   {HintPathFromItem}@   {TargetFrameworkDirectory}A   B{Registry:Software\Microsoft\.NETFramework,v2.0,AssemblyFoldersEx}B   {RawFileName}C   WD:\Project\LunaEditor\dockpanelsuite-master\dockpanelsuite-master\WinFormsUI\bin\Debug\      D   .C:\Windows\Microsoft.NET\Framework\v2.0.50727\       :           ­System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.Collections.Generic.List`1[[System.Collections.Generic.KeyValuePair`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]], mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089]]                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ŮŐů Ąc×˙˙˙˙E1Ę  4                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             Ő                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            9@@PBU_D3DSURFACE_DESC@@PAX@Z ?OnCycleFocus@CDXUTDialog@@AAE_N_N@Z ?OnD3D11CreateDevice@CD3DSettingsDlg@@QAEJPAUID3D11Device@@@Z ?OnD3D11CreateDevice@CDXUTDialogResourceManager@@QAEJPAUID3D11Device@@PAUID3D11DeviceContext@@@Z ?OnD3D11DestroyDevice@CD3DSettingsDlg@@QAEXXZ ?OnD3D11DestroyDevice@CDXUTDialogResourceManager@@QAEXXZ ?OnD3D11ReleasingSwapChain@CDXUTDialogResourceManager@@QAEXXZ ?OnD3D11ResizedSwapChain@CD3DSettingsDlg@@QAEJPAUID3D11Device@@PBUDXGI_SURFACE_DESC@@@Z ?OnD3D11ResizedSwapChain@CDXUTDialogResourceManager@@QAEJPAUID3D11Device@@PBUDXGI_SURFACE_DESC@@@Z ?OnD3D11ResolutionChanged@CD3DSettingsDlg@@IAEJXZ ?OnD3D9CreateDevice@CD3DSettingsDlg@@QAEJPAUIDirect3DDevice9@@@Z ?OnD3D9CreateDevice@CDXUTDialogResourceManager@@QAEJPAUIDirect3DDevice9@@@Z ?OnD3D9DestroyDevice@CD3DSettingsDlg@@QAEXXZ ?OnD3D9DestroyDevice@CDXUTDialogResourceManager@@QAEXXZ ?OnD3D9LostDevice@CD3DSettingsDlg@@QAEXXZ ?OnD3D9LostDevice@CDXUTDialogResourceManager@@QAEXXZ ?OnD3D9ResetDevice@CD3DSettingsDlg@@QAEJXZ ?OnD3D9ResetDevice@CDXUTDialogResourceManager@@QAEJXZ ?OnDebugDeviceChanged@CD3DSettingsDlg@@IAEJXZ ?OnDepthStencilBufferFormatChanged@CD3DSettingsDlg@@IAEJXZ ?OnDestroyDevice@LunaRenderer@@CGXPAX@Z ?OnDeviceClipChanged@CD3DSettingsDlg@@IAEJXZ ?OnDeviceTypeChanged@CD3DSettingsDlg@@IAEJXZ ?OnEvent@CD3DSettingsDlg@@IAEXIHPAVCDXUTControl@@@Z ?OnFeatureLevelChanged@CD3DSettingsDlg@@IAEJXZ ?OnFrameMove@LunaRenderer@@CGXNMPAX@Z ?OnFrameRender@LunaRenderer@@CGXPAUIDirect3DDevice9@@NMPAX@Z ?OnGUIEvent@LunaRenderer@@CGXIHPAVCDXUTControl@@PAX@Z ?OnLostDevice@LunaRenderer@@CGXPAX@Z ?OnMouseMove@CDXUTDialog@@AAEXUtagPOINT@@@Z ?OnMouseUp@CDXUTDialog@@AAEXUtagPOINT@@@Z ?OnMultisampleQualityChanged@CD3DSettingsDlg@@IAEJXZ ?OnMultisampleTypeChanged@CD3DSettingsDlg@@IAEJXZ ?OnPresentIntervalChanged@CD3DSettingsDlg@@IAEJXZ ?OnRefreshRateChanged@CD3DSettingsDlg@@IAEJXZ ?OnRender11@CD3DSettingsDlg@@QAEXM@Z ?OnRender11@CDXUTDialog@@AAEJM@Z ?OnRender9@CD3DSettingsDlg@@QAEXM@Z ?OnRender9@CDXUTDialog@@AAEJM@Z ?OnRender@CD3DSettingsDlg@@QAEXM@Z ?OnRender@CDXUTDialog@@QAEJM@Z ?OnResetDevice@LunaRenderer@@CGJPAUIDirect3DDevice9@@PBU_D3DSURFACE_DESC@@PAX@Z ?OnResolutionChanged@CD3DSettingsDlg@@IAEJXZ ?OnVertexProcessingChanged@CD3DSettingsDlg@@IAEJXZ ?OnWindowedFullScreenChanged@CD3DSettingsDlg@@IAEJXZ ?Refresh@CD3DSettingsDlg@@QAEJXZ ?Refresh@CDXUTDialog@@QAEXXZ ?RegisterDialog@CDXUTDialogResourceManager@@QAE_NPAVCDXUTDialog@@@Z ?RemoveAllControls@CDXUTDialog@@QAEXXZ ?RemoveControl@CDXUTDialog@@QAEXH@Z ?Render@CDXUTXFileMesh@@QAEJPAUID3DXEffect@@PBD11111_N2@Z ?Render@CDXUTXFileMesh@@QAEJPAUIDirect3DDevice9@@_N1@Z ?Render@LunaRenderer@@QAEXXZ ?RenderScene@LunaRenderer@@QAEXPAUIDirect3DDevice9@@_NMPBUD3DXMATRIX@@2@Z ?RenderText@LunaRenderer@@AAEXXZ ?RequestFocus@CDXUTDialog@@QAEXPAVCDXUTControl@@@Z ?Reset@CBaseCamera@@UAEXXZ ?RestoreD3D11State@CDXUTDialogResourceManager@@QAEXPAUID3D11DeviceContext@@@Z ?RestoreDeviceObjects@CDXUTXFileMesh@@QAEJPAUIDirect3DDevice9@@@Z ?SendEvent@CDXUTDialog@@QAEXI_NPAVCDXUTControl@@@Z ?SetActive@CD3DSettingsDlg@@QAEX_N@Z ?SetBackgroundColors@CDXUTDialog@@QAEXK@Z ?SetBackgroundColors@CDXUTDialog@@QAEXKKKK@Z ?SetCallback@CDXUTDialog@@QAEXP6GXIHPAVCDXUTControl@@PAX@Z1@Z ?SetCaptionHeight@CDXUTDialog@@QAEXH@Z ?SetCaptionText@CDXUTDialog@@QAEXPB_W@Z ?SetClipToBoundary@CBaseCamera@@QAEX_NPAUD3DXVECTOR3@@1@Z ?SetControlEnabled@CDXUTDialog@@QAEXH_N@Z ?SetDefaultElement@CDXUTDialog@@QAEJIIPAVCDXUTElement@@@Z ?SetDeviceClip@CD3DSettingsDlg@@IAEX_N@Z ?SetDeviceSettingsFromUI@CD3DSettingsDlg@@IAEJXZ ?SetDrag@CBaseCamera@@QAEX_NM@Z ?SetDragRect@CBaseCamera@@UAEXAAUtagRECT@@@Z ?SetEnablePositionMovement@CBaseCamera@@QAEX_N@Z ?SetEnableYAxisMovement@CBaseCamera@@QAEX_N@Z ?SetFVF@CDXUTXFileMesh@@QAEJPAUIDirect3DDevice9@@K@Z ?SetFont@CDXUTDialog@@QAEJIPB_WJJ@Z ?SetInvertPitch@CBaseCamera@@QAEX_N@Z ?SetLo
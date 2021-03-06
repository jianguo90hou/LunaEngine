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


/* Define EGLint. This must be a signed integral ty P`.debug$S        D  6i zl        @B.text$mn          �l o         P`.debug$S        D  To �r        @B.text$mn          s 6u         P`.debug$S        D  ru �x        @B.text$mn          8y J{         P`.debug$S        D  �{ �~        @B.text$mn        !  L m�         P`.debug$S        D  �� �        @B.text$mn          o� ��         P`.debug$S        D   �        @B.text$mn          �� ��         P`.debug$S        D  ۍ �        @B.text$mn          �� ��         P`.debug$S        D  � .�        @B.text$mn        �   ��              P`.debug$S        �  }� M�        @B.text$mn        �   �              P`.debug$S        �  G� �        @B.text$mn          I� ]�         P`.debug$S          �� ��        @B.text$mn          ߠ �         P`.debug$S          � 3�        @B.text$mn          y� ��         P`.debug$S          �� ɧ        @B.text$mn          � *�         P`.debug$S          R� j�        @B.text$mn          �� ˬ         P`.debug$S          � �        @B.text$mn          Q� l�         P`.debug$S          �� ��        @B.text$mn          � �         P`.debug$S          .� B�        @B.text$mn          �� ��         P`.debug$S          ķ ܹ        @B.text$mn          "� 6�         P`.debug$S          ^� r�        @B.text$mn        X   �� �         P`.debug$S        �  � ڿ        @B.text$mn        _  � k�         P`.debug$S        �  �� =�        @B.text$mn        �   �� <�         P`.debug$S           d� ��        @B.text$mn        �   ��              P`.debug$S        �  �� g�        @B.text$mn        �   ��              P`.debug$S        �  a� 1�        @B.text$mn          c� w�         P`.debug$S          �� ��        @B.text$mn          �� �         P`.debug$S          5� M�        @B.text$mn          �� ��         P`.debug$S          �� ��        @B.text$mn          )� D�         P`.debug$S          l� ��        @B.text$mn          �� ��         P`.debug$S          � %�        @B.text$mn          k� ��         P`.debug$S          �� ��        @B.text$mn          �  �         P`.debug$S          H� \�        @B.text$mn          �� ��         P`.debug$S          �� ��        @B.text$mn          <� P�         P`.debug$S          x� ��        @B.text$mn        Q   ��              P`.debug$S        �  #� ��        @B.text$mn        Q   ��              P`.debug$S        t  *� ��        @B.text$mn        Q   ��              P`.debug$S        �  !� ��        @B.text$mn        L   �� K�         P`.debug$S        �  _� ��        @B.text$mn        L   � i�         P`.debug$S        |  }� ��        @B.text$mn        L   +� w�         P`.debug$S        �  �� ;�        @B.text$mn        ^   m�              P`.debug$S           �� ��        @B.text$mn        ^   �              P`.debug$S        <  {� ��        @B.text$mn        ^   ��              P`.debug$S        4  G� {         @B.text$mn        ^   �               P`.debug$S        L   W        @B.text$mn        ^   �              P`.debug$S        8  �         @B.text$mn        B   Q �         P`.debug$S        �   � �        @B.text$mn        B   � �         P`.debug$S                    @B.text$mn        C   %              P`.debug$S        4  h �        @B.text$mn        K   � 	         P`.debug$S        �   7	 +
        @B.text$mn        K   I
 �
         P`.debug$S        �   �
 �        @B.text$mn        K   �          P`.debug$S        �   - !        @B.text$mn        K   ? �         P`.debug$S        �   � �        @B.text$mn        K   � �         P`.debug$S        �            @B.text$mn        K   ) t         P`.debug$S        <  � �        @B.text$mn        K   � 7         P`.debug$S        `  U �        @B.text$mn        K   �          P`.debug$S        @  < |        @B.text$mn        K   � �         P`.debug$S        H   K        @B.text$mn        K   i �         P`.debug$S        p  � B        @B.text$mn        K   ` �         P`.debug$S        p  � 9        @B.text$mn        K   W �         P`.debug$S        \  �         @B.text$mn        K   : �         P`.debug$S        �  � #        @B.text$mn        K   A �         P`.debug$S        X  � !        @B.text$mn        K    ! k!         P`.debug$S        |  �! #        @B.text$mn        K   ## n#         P`.debug$S        h  �# �$        @B.text$mn        K   % ]%         P`.debug$S        �  {% '        @B.text$mn        K   %' p'         P`.debug$S        D  �' �(        @B.text$mn        K   �( ;)         P`.debug$S        L  Y) �*        @B.text$mn        K   �* +         P`.debug$S        p  ,+ �,        @B.text$mn        K   �, -         P`.debug$S        p  #- �.        @B.text$mn        s   �. $/         P`.debug$S        L  B/ �0        @B.text$mn        s   �0 31         P`.debug$S        \  Q1 �2        @B.text$mn        s   �2 R3         P`.debug$S        X  p3 �4        @B.text$mn        s   �4 m5         P`.debug$S        `  �5 �6        @B.text$mn        s   7 �7         P`.debug$S        T  �7 9        @B.text$mn        s   49 �9         P`.debug$S        L  �9 ;        @B.text$mn        s   C; �;         P`.debug$S        T  �; (=        @B.text$mn        s   Z= �=         P`.debug$S        `  �= K?        @B.text$mn        s   }? �?         P`.debug$S        P  @ ^A        @B.text$mn        s   �A B         P`.debug$S        L  !B mC        @B.text$mn        s   �C D         P`.debug$S        \  0D �E        @B.text$mn        s   �E 1F         P`.debug$S        L  OF �G        @B.text$mn        s   �G @H         P`.debug$S        L  ^H �I        @B.text$mn        s   �I OJ         P`.debug$S        h  mJ �K        @B.text$mn        s   L zL         P`.debug$S        @  �L �M        @B.text$mn        s   
N }N         P`.debug$S        L  �N �O        @B.text$mn        K   P dP         P`.debug$S        @  �P �Q        @B.text$mn        K   �Q +R         P`.debug$S        H  IR �S        @B.text$mn        K   �S �S         P`.debug$S        l  T �U        @B.text$mn        K   �U �U         P`.debug$S        l  V wW        @B.text$mn        K   �W �W         P`.debug$S        L  �W JY        @B.text$mn        K   hY �Y         P`.debug$S        p  �Y A[        @B.text$mn        K   _[ �[         P`.debug$S        H  �[ ]        @B.text$mn        K   .] y]         P`.debug$S        H  �] �^        @B.text$mn        K   �^ H_         P`.debug$S        l  f_ �`        @B.text$mn        K   �` ;a         P`.debug$S        l  Ya �b        @B.text$mn        K   �b .c         P`.debug$S        8  Lc �d        @B.text$mn        K   �d �d         P`.debug$S        @  e Kf        @B.text$mn        K   if �f         P`.debug$S        h  �f :h        @B.text$mn        K   Xh �h         P`.debug$S        h  �h )j        @B.text$mn        o   Gj �j         P`.debug$S        ,  �j 
l        @B.text$mn        o   <l �l         P`.debug$S        <  �l n        @B.text$mn        o   An �n         P`.debug$S        8  �n p        @B.text$mn        o   Bp �p         P`.debug$S        @  �p r        @B.text$mn        o   Kr �r         P`.debug$S        4  �r t        @B.text$mn        o   Ht �t         P`.debug$S        ,  �t v        @B.text$mn        o   =v �v         P`.debug$S        4  �v x        @B.text$mn        o   :x �x         P`.debug$S        @  �x z        @B.text$mn        o   Cz �z         P`.debug$S        0  �z 
|        @B.text$mn        o   <| �|         P`.debug$S        ,  �| �}        @B.text$mn        o   1~ �~         P`.debug$S        <  �~ �        @B.text$mn        o   6� ��         P`.debug$S        ,  ̀ ��        @B.text$mn        o   +� ��         P`.debug$S        ,   �        @B.text$mn        o    � ��         P`.debug$S        H  �� ��        @B.text$mn        o   1� ��         P`.debug$S           Ȇ �        @B.text$mn        o   � ��         P`.debug$S        ,  �� ݉        @B.text$mn        K   � Z�         P`.debug$S        <  x� ��        @B.text$mn        K   ҋ �         P`.debug$S        <  ;� w�        @B.text$mn        K   �� ��         P`.debug$S        0  �� .�        @B.text$mn        K   L� ��         P`.debug$S        <  �� �        @B.text$mn        K   � Z�         P`.debug$S        D  x� ��        @B.text$mn        K   ڒ %�         P`.debug$S        D  C� ��        @B.text$mn        K   �� �         P`.debug$S        8  � F�        @B.text$mn        K   d� ��         P`.debug$S        D  ͖ �        @B.text$mn        K   /� z�         P`.debug$S        h  ��  �        @B.text$mn        K   � i�         P`.debug$S        h  �� �        @B.text$mn        K   � X�         P`.debug$S        h  v� ޝ        @B.text$mn        K   �� G�         P`.debug$S        h  e� ͟        @B.text$mn        K   � 6�         P`.debug$S        \  T� ��        @B.text$mn        K   Ρ �         P`.debug$S        \  7� ��        @B.text$mn        K   �� ��         P`.debug$S        h  � ��        @B.text$mn        K   �� �         P`.debug$S        h  	� q�        @B.text$mn        K   �� ڧ         P`.debug$S        P  �� H�        @B.text$mn        K   f� ��         P`.debug$S        t  ϩ C�        @B.text$mn        K   a� ��         P`.debug$S        h  ʫ 2�        @B.text$mn        K   P� ��         P`.debug$S        �  �� E�        @B.text$mn        K   c� ��         P`.debug$S        D  ̯ �        @B.text$mn        K   .� y�         P`.debug$S        h  �� ��        @B.text$mn        K   � h�         P`.debug$S        `  �� �        @B.text$mn        K   � O�         P`.debug$S        �  m� �        @B.text$mn        K   � Z�         P`.debug$S        @  x� ��        @B.text$mn        K   ָ !�         P`.debug$S        d  ?� ��        @B.text$mn        K   �� �         P`.debug$S        8  *� b�        @B.text$mn        K   �� ˼         P`.debug$S        @  � )�        @B.text$mn        K   G� ��         P`.debug$S        h  �� �        @B.text$mn        K   6� ��         P`.debug$S        h  �� �        @B.text$mn        `   %� ��         P`.debug$S        8  �� ��        @B.text$mn        `   � w�         P`.debug$S        H  �� ��        @B.text$mn        `   � y�         P`.debug$S        D  �� ��        @B.text$mn        `   � w�         P`.debug$S        L  �� ��        @B.text$mn        `   � }�         P`.debug$S        @  �� ��        @B.text$mn        `   � w�         P`.debug$S        8  �� ��        @B.text$mn        `   	� i�         P`.debug$S        @  �� ��        @B.text$mn        `   � c�         P`.debug$S        L  �� ��        @B.text$mn        `   	� i�         P`.debug$S        <  �� ��        @B.text$mn        `   �� _�         P`.debug$S        8  �� ��        @B.texALLBACKS9* pLoaderCallbacks=NULL );
    virtual HRESULT                 Create( ID3D11Device* pDev11, BYTE* pData, UINT DataBytes,
                                            bool bCreateAdjacencyIndices=false, bool bCopyStatic=false,
                                            SDKMESH_CALLBACKS11* pLoaderCallbacks=NULL );
    virtual HRESULT                 Create( IDirect3DDevice9* pDev9, BYTE* pData, UINT DataBytes,
                                            bool bCreateAdjacencyIndices=false, bool bCopyStatic=false,
                                            SDKMESH_CALLBACKS9* pLoaderCallbacks=NULL );
    virtual HRESULT                 LoadAnimation( WCHAR* szFileName );
    virtual void                    Destroy();

    //Frame manipulation
    void                            TransformBindPose( D3DXMATRIX* pWorld );
    void                            TransformMesh( D3DXMATRIX* pWorld, double fTime );


    //Direct3D 11 Rendering
    virtual void                    Render( ID3D11DeviceContext* pd3dDeviceContext,
                                            UINT iDiffuseSlot = INVALID_SAMPLER_SLOT,
                                            UINT iNormalSlot = INVALID_SAMPLER_SLOT,
                                            UINT iSpecularSlot = INVALID_SAMPLER_SLOT );
    virtual void                    RenderAdjacent( ID3D11DeviceContext* pd3dDeviceContext,
                                                    UINT iDiffuseSlot = INVALID_SAMPLER_SLOT,
                                                    UINT iNormalSlot = INVALID_SAMPLER_SLOT,
                                                    UINT iSpecularSlot = INVALID_SAMPLER_SLOT );

    //Direct3D 9 Rendering
    virtual void                    Render( LPDIRECT3DDEVICE9 pd3dDevice,
                                            LPD3DXEFFECT pEffect,
                                            D3DXHANDLE hTechnique,
                                            D3DXHANDLE htxDiffuse = 0,
                                            D3DXHANDLE htxNormal = 0,
                                            D3DXHANDLE htxSpecular = 0 );

    //Helpers (D3D11 specific)
    static D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType11( SDKMESH_PRIMITIVE_TYPE PrimType );
    DXGI_FORMAT                     GetIBFormat11( UINT iMesh );
    ID3D11Buffer* GetVB11( UINT iMesh, UINT iVB );
    ID3D11Buffer* GetIB11( UINT iMesh );
    SDKMESH_INDEX_TYPE GetIndexType( UINT iMesh ); 

    ID3D11Buffer* GetAdjIB11( UINT iMesh );

    //Helpers (D3D9 specific)
    static D3DPRIMITIVETYPE         GetPrimitiveType9( SDKMESH_PRIMITIVE_TYPE PrimType );
    D3DFORMAT                       GetIBFormat9( UINT iMesh );
    IDirect3DVertexBuffer9* GetVB9( UINT iMesh, UINT iVB );
    IDirect3DIndexBuffer9* GetIB9( UINT iMesh );

    //Helpers (general)
    char* GetMeshPathA();
    WCHAR* GetMeshPathW();
    UINT                            GetNumMeshes();
    UINT                            GetNumMaterials();
    UINT                            GetNumVBs();
    UINT                            GetNumIBs();

    ID3D11Buffer* GetVB11At( UINT iVB );
    ID3D11Buffer* GetIB11At( UINT iIB );

    IDirect3DVertexBuffer9* GetVB9At( UINT iVB );
    IDirect3DIndexBuffer9* GetIB9At( UINT iIB );

    BYTE* GetRawVerticesAt( UINT iVB );
    BYTE* GetRawIndicesAt( UINT iIB );
    SDKMESH_MATERIAL* GetMaterial( UINT iMaterial );
    SDKMESH_MESH* GetMesh( UINT iMesh );
    UINT                            GetNumSubsets( UINT iMesh );
    SDKMESH_SUBSET* GetSubset( UINT iMesh, UINT iSubset );
    UINT                            GetVertexStride( UINT iMesh, UINT iVB );
    UINT                            GetNumFrames();
    SDKMESH_FRAME*                  GetFrame( UINT iFrame );
    SDKMESH_FRAME*                  FindFrame( char* pszName );
    UINT64                          GetNumVertices( UINT iMesh, UINT iVB );
    UINT64                          GetNumIndices( UINT iMesh );
    D3DXVECTOR3                     GetMeshBBoxCenter( UINT iMesh );
    D3DXVECTOR3                     GetMeshBBoxExtents( UINT iMesh );
    UINT                            GetOutstandingResources();
    UINT                            GetOutstandingBufferResources();
    bool                            CheckLoadDone();
    bool                            IsLoaded();
    bool                            IsLoading();
    void                            SetLoading( bool bLoading );
    BOOL                            HadLoadingError();

    //Animation
    UINT                            GetNumInfluences( UINT iMesh );
    const D3DXMATRIX*               GetMeshInfluenceMatrix( UINT iMesh, UINT iInfluence );
    UINT                            GetAnimationKeyFromTime( double fTime );
    const D3DXMATRIX*               GetWorldMatrix( UINT iFrameIndex );
    const D3DXMATRIX*               GetInfluenceMatrix( UINT iFrameIndex );
    bool                            GetAnimationProperties( UINT* pNumKeys, FLOAT* pFrameTime );
};

//-----------------------------------------------------------------------------
// Name: class CDXUTXFileMesh
// Desc: Class for loading and rendering file-based meshes
//-----------------------------------------------------------------------------
class DLL_EXPORT CDXUTXFileMesh
{
public:
    WCHAR       m_strName[512];
    LPD3DXMESH m_pMesh;   // Managed mesh

    // Cache of data in m_pMesh for easy access
    IDirect3DVertexBuffer9* m_pVB;
    IDirect3DIndexBuffer9* m_pIB;
    IDirect3DVertexDeclaration9* m_pDecl;
    DWORD m_dwNumVertices;
    DWORD m_dwNumFaces;
    DWORD m_dwBytesPerVertex;

    DWORD m_dwNumMaterials; // Materials for the mesh
    D3DMATERIAL9* m_pMaterials;
    CHAR        (*m_strMaterials )[MAX_PATH];
    IDirect3DBaseTexture9** m_pTextures;
    bool m_bUseMaterials;

public:
    // Rendering
    HRESULT     Render( LPDIRECT3DDEVICE9 pd3dDevice,
                        bool bDrawOpaqueSubsets = true,
                        bool bDrawAlphaSubsets = true );
    HRESULT     Render( ID3DXEffect* pEffect,
                        D3DXHANDLE hTexture = NULL,
                        D3DXHANDLE hDiffuse = NULL,
                        D3DXHANDLE hAmbient = NULL,
                        D3DXHANDLE hSpecular = NULL,
                        D3DXHANDLE hEmissive = NULL,
                        D3DXHANDLE hPower = NULL,
                        bool bDrawOpaqueSubsets = true,
                        bool bDrawAlphaSubsets = true );

    // Mesh access
    LPD3DXMESH  GetMesh()
    {
        return m_pMesh;
    }

    // Rendering options
    void        UseMeshMaterials( bool bFlag )
    {
        m_bUseMaterials = bFlag;
    }
    HRESULT     SetFVF( LPDIRECT3DDEVICE9 pd3dDevice, DWORD dwFVF );
    HRESULT     SetVertexDecl( LPDIRECT3DDEVICE9 pd3dDevice, const D3DVERTEXELEMENT9* pDecl,
                               bool bAutoComputeNormals = true, bool bAutoComputeTangents = true,
                               bool bSplitVertexForOptimalTangents = false );

    // Initializing
    HRESULT     RestoreDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice );
    HRESULT     InvalidateDeviceObjects();

    // Creation/destruction
    HRESULT     Create( LPDIRECT3DDEVICE9 pd3dDevice, LPCWSTR strFilename );
    HRESULT     Create( LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXFILEDATA pFileData );
    HRESULT     Create( LPDIRECT3DDEVICE9 pd3dDevice, ID3DXMesh* pInMesh, D3DXMATERIAL* pd3dxMaterials,
                        DWORD dwMaterials );
    HRESULT     CreateMaterials( LPCWSTR strPath, IDirect3DDevice9* pd3dDevice, D3DXMATERIAL* d3dxMtrls,
                                 DWORD dwNumMaterials );
    HRESULT     Destroy();

                CDXUTXFileMesh( LPCWSTR strName = L"CDXUTXMeshFile_Mesh" );
    virtual     ~CDXUTXFileMesh();
};


#endif

#endif


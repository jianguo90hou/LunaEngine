
#include "LunaHDRLighting.h"
#include "../DXUT11/DXUT.h"

#define _Rad    D3DXToRadian

// Static star library information
static STARDEF s_aLibStarDef[NUM_BASESTARLIBTYPES] =
{
	//  star name               lines   passes  length  attn    rotate          bRotate
	{ TEXT("Disable"), 0, 0, 0.0f, 0.0f, _Rad(00.0f), false, },  // STLT_DISABLE

	{ TEXT("Cross"), 4, 3, 1.0f, 0.85f, _Rad(0.0f), true, },  // STLT_CROSS
	{ TEXT("CrossFilter"), 4, 3, 1.0f, 0.95f, _Rad(0.0f), true, },  // STLT_CROSS
	{ TEXT("snowCross"), 6, 3, 1.0f, 0.96f, _Rad(20.0f), true, },  // STLT_SNOWCROSS
	{ TEXT("Vertical"), 2, 3, 1.0f, 0.96f, _Rad(00.0f), false, },  // STLT_VERTICAL
};
static int                      s_nLibStarDefs = sizeof(s_aLibStarDef) / sizeof(STARDEF);


// Static glare library information
static GLAREDEF s_aLibGlareDef[NUM_GLARELIBTYPES] =
{
	//  glare name                              glare   bloom   ghost   distort star    star type
	//  rotate          C.A     current after   ai lum
	{ TEXT("Disable"), 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, STLT_DISABLE,
	_Rad(0.0f), 0.5f, 0.00f, 0.00f, 0.0f, },   // GLT_DISABLE

	{ TEXT("Camera"), 1.5f, 1.2f, 1.0f, 0.00f, 1.0f, STLT_CROSS,
	_Rad(00.0f), 0.5f, 0.25f, 0.90f, 1.0f, },   // GLT_CAMERA
	{ TEXT("Natural Bloom"), 1.5f, 1.2f, 0.0f, 0.00f, 0.0f, STLT_DISABLE,
	_Rad(00.0f), 0.0f, 0.40f, 0.85f, 0.5f, },   // GLT_NATURAL
	{ TEXT("Cheap Lens Camera"), 1.25f, 2.0f, 1.5f, 0.05f, 2.0f, STLT_CROSS,
	_Rad(00.0f), 0.5f, 0.18f, 0.95f, 1.0f, },   // GLT_CHEAPLENS
	/*
	{   TEXT("Afterimage"),                     1.5f,   1.2f,   0.5f,   0.00f,  0.7f,   STLT_CROSS,
	_Rad(00.0f),    0.5f,   0.1f,   0.98f,  2.0f,  },   // GLT_AFTERIMAGE
	*/
	{ TEXT("Cross Screen Filter"), 1.0f, 2.0f, 1.7f, 0.00f, 1.5f, STLT_CROSSFILTER,
	_Rad(25.0f), 0.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_CROSSSCREEN
	{ TEXT("Spectral Cross Filter"), 1.0f, 2.0f, 1.7f, 0.00f, 1.8f, STLT_CROSSFILTER,
	_Rad(70.0f), 1.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_CROSSSCREEN_SPECTRAL
	{ TEXT("Snow Cross Filter"), 1.0f, 2.0f, 1.7f, 0.00f, 1.5f, STLT_SNOWCROSS,
	_Rad(10.0f), 0.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_SNOWCROSS
	{ TEXT("Spectral Snow Cross"), 1.0f, 2.0f, 1.7f, 0.00f, 1.8f, STLT_SNOWCROSS,
	_Rad(40.0f), 1.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_SNOWCROSS_SPECTRAL
	{ TEXT("Sunny Cross Filter"), 1.0f, 2.0f, 1.7f, 0.00f, 1.5f, STLT_SUNNYCROSS,
	_Rad(00.0f), 0.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_SUNNYCROSS
	{ TEXT("Spectral Sunny Cross"), 1.0f, 2.0f, 1.7f, 0.00f, 1.8f, STLT_SUNNYCROSS,
	_Rad(45.0f), 1.5f, 0.20f, 0.93f, 1.0f, },   // GLT_FILTER_SUNNYCROSS_SPECTRAL
	{ TEXT("Cine Camera Vertical Slits"), 1.0f, 2.0f, 1.5f, 0.00f, 1.0f, STLT_VERTICAL,
	_Rad(90.0f), 0.5f, 0.20f, 0.93f, 1.0f, },   // GLT_CINECAM_VERTICALSLIT
	{ TEXT("Cine Camera Horizontal Slits"), 1.0f, 2.0f, 1.5f, 0.00f, 1.0f, STLT_VERTICAL,
	_Rad(00.0f), 0.5f, 0.20f, 0.93f, 1.0f, },   // GLT_CINECAM_HORIZONTALSLIT
};
static int                      s_nLibGlareDefs = sizeof(s_aLibGlareDef) / sizeof(GLAREDEF);



//----------------------------------------------------------
// Information object for star generation 

CStarDef*                       CStarDef::ms_pStarLib = NULL;
D3DXCOLOR CStarDef::ms_avChromaticAberrationColor[];


CStarDef::CStarDef()
{
	Construct();
}

CStarDef::CStarDef(const CStarDef& src)
{
	Construct();
	Initialize(src);
}

CStarDef::~CStarDef()
{
	Destruct();
}


HRESULT CStarDef::Construct()
{
	ZeroMemory(m_strStarName, sizeof(m_strStarName));

	m_nStarLines = 0;
	m_pStarLine = NULL;
	m_fInclination = 0.0f;

	m_bRotation = false;

	return S_OK;
}

void CStarDef::Destruct()
{
	Release();
}

void CStarDef::Release()
{
	SAFE_DELETE_ARRAY(m_pStarLine);
	m_nStarLines = 0;
}


HRESULT CStarDef::Initialize(const CStarDef& src)
{
	if (&src == this)
	{
		return S_OK;
	}

	// Release the data
	Release();

	// Copy the data from source
	wcscpy_s(m_strStarName, 256, src.m_strStarName);
	m_nStarLines = src.m_nStarLines;
	m_fInclinatio        d r�l�8�&            H�`�$  r����?       4�  r� ��Z~        �~          r���x       �  r���x           �l�  r�    x        �s        Z r���x                       e r����           ���%  r����                              T�      r���0I        �s        %  r����                                         r����           ��x�:  r�    �        ��  r���x          ����:  r�    x        ��$  r�L��      ��:  r�    �        0�  r����        $��        
 r����     h�:  r�    �        ��  r�    x       ��          ������    �������୨                            �              0�0����������D�D�୨                           P�    ୨                      r�P�      r�     x       ���        Z r���x                       d r�    �           ����  r� ���\@        ���        %  r�     x                                         t� �����Z        0 d        
 t� �����Z      t��%  t� ����                                       ? t� $��x           ������  t�     x        T_�          t� X��x�c          d        
 t� ���x�c      4��Z t�     x        ���          Y t� ����7        ���  t� �����Z        0 d        
 t� �����Z  0   ���$  t� t���4  �     ���%  t� t��                              L��    >  t�                 ��[         t� ����4  �         �����Y t� ����4        t��������          t�     x         4        d t� $��8�&             �������%  �	&�^�8�&                                      %  �	&���8�&                                      Z �	&���x        ���          Y �	&���8�&        H�����������                    $  t� ����7       X��  t� ���T	�        T_�          t� ���x           ������:  t�     x        $��          d��d��d��    �~x��x���#'                           ���              �����������~�������#'                           ���    �#'                      t� ���      t�     x       �~          t� H���:�            �yU    Q       Z t� $��x        ��          Y t� |���?        H��%  t� ����                F                       Y t� |���        ���������        d t� ���8�&            d��|��$  t� ����?       P��  t� $���Z~        �~          t� ���x       $��  t� ��x           $�����  t�     x        �s        Z t� ��x                       e t� ����           8�����%  t� ���                              p��      t� ��0I        �s        %  t� ����                                         t� ���           �����:  t�     �        ���  t� ��x          ������:  t�     x        ��$  t� h���      ��:  t�     �        L��  |����d�        8�c        
 |�����h      ���
 |�    4y       ���|��                           �3      |�,��x        ���        P |�    x            �����Z |����x                       s |�    4y       ���d |�    8�&            ���P��  |����4�         ��        n |����4�            ������X  ��    x�c            ��            X  ��    p�=            ��              �����p�=        ��        
 �����p�=      X��  �������Z        0 d        
 �������Z  0   ���  ��    p�=          X�����$  �����p�=  0    ���  �����x�c        ��        
 �����x�c      ��  ��
|��x�c          d        
 ��
���x�c      X��  ��    x�c          ��|��  ��	���p�=        ��        
 ��	4 �p�=      ���%  ��4 �p�=                                       A ��    x           ������X  ��    l�?            �              ���l�?        �        
 ���l�?      � �  ��                (�(          ��    l�?        (�(          ��0�p�=        ��        
 ��x�p�=     �:  ��    p�=        0�%  �� ��                ���                    %  ��  �                               ��    >  ��                 ��[       '  ��                h���%  ��x�p�=           '   fff             �    :  ��            $�C ��H�x           0�$�:  ��    x        x�  ����p�=        ��        
 ��$�p�= 0   ��:  ��    p�=        ��%  �����                ���                    %  �� ��                               ��    >  ��                 ��[       '  ��                �L�%  ��$�p�= 0         '   fff            ��    :  ��            ��  ��H�p�=            ����  ����p�= 0         x�$�:  ��    p�=        H�Z ��    x        ��          Y ����p�=        H�[	 ��    01            H�          $  ���l�?  0     H�  ��    l�?          � ���  ��\�d�        8�c        
 �����h      8�
 ��    4y       \�(j�                           �3      ����x        ��        P ��    x            \���  ��(�x�c        ��        
 ����x�c      �Z ����x        h�          Y ��D��7        ��  ����l�?        �        
 ��(�l�?  0   ��%  �� (�                               �    >  ��                 ��[         ��#L�l�?  0         ����Y ��#D�l�?        (�l�L�        s ��    4y       \�d ��    �           ��D�$  ��l��7       (�  �����        ���        n �����            ��\�  ����p�=        ��        
 ����p�=      �  ����l�?        �        
 ����l�?  0   \�G ��    p�=           ���  ��@	�x�c        ��        
 ��@	�x�c      ��  ��$	�l�?        �        
 ���	�l�?       	�K ��	    x�c           ���	�%      �	��                                         ��	@	�           $	�d	�X  ��    x�c            ��            X  ��    p�=            ��              ���
�p�=        ��        
 ���
�p�=      
�  ��|
���Z        0 d        
 ���
���Z  0   X
�  ��    p�=          
��
�$  ���
�p�=  0    |
�  ��X�x�c        ��        
 ��X�x�c      �
�  ��
<�x�c          d        
 ��
X�x�c      �  ��    x�c          �
�<�  ��	��p�=        ��        
 ��	��p�=      |�%  ����p�=                                       A ��    x           ����X  ��    l�?            �              ����l�?        �        
 ����l�?      D�  ��                (�(          ��    l�?        (�(          ����p�=        ��        
 ��8�p�=     ��:  ��    p�=        ��%  �����                ���                    %  �� ��                               ��    >  ��                 ��[       '  ��                (�`�%  ��8�p�=           '   fff            ��    :  ��            ��C ���x           ����:  ��    x        8�  ����p�=        ��        
 ����p�= 0   x�:  ��    p�=        ��%  ��l��                ���                    %  �� l�                               D�    >  ��                 ��[       '  ��                ���%  ����p�= 0         '   fff            l�    :  ��            ��  ���p�=            ����  ����p�= 0         8���:  ��    p�=        �Z ��    x        p�          Y ��H�p�=        �[	 ��    01            �          $  ����l�?  0     �  ��    l�?          D���  ���d�        8�c        
 �����h      ��
 ��    4y       ����                           �3      ����x        T�        P ��    x            �|�  ����x�c        ��        
 ��x�x�c      ��Z ��T�x        (�          Y ���2        x�  ��l�l�?        �        
 ����l�?  0   H�%  �� ��                              ��    >  ��                 ��[         ��'�l�?  0         l���Y ��'�l�?        ��,��        s ��    4y       �d ��    �           ���$  ��,�2       ��  ������        (��        n ��T���            ���  ��\�p�=        ��        
 ��\�p�=      ��  ��@�l�?        �        
 ��\�l�?  0   �G ��    p�=           ��@�  �� �x�c        ��        
 �� �x�c      ��  ����l�?        �        
 ��\�l�?      ��K ��	    x�c           ��\�%      \��                                         ��	 �           ��$�? ��                        ��� d       aU��      p� ����c       � d        a p�     ��c           ��      p�     ��Z        0 d          p�     x�c          d          p�     d�        8�c            �c)t���%      ���                                          r�    �            ����    �~��|�    ��(����          �:�        ��b            ��b$���    ��)4�,�    ��)D�<�    ���T�L�%      ���                                          t�     �            ��d�    �c)��\�    T_�����    ��(����    ��(����    ��( ���    �c)��    �8 ��    �80�(�    �~@�8�    ��(P�H�          �:�        ��b            ��b��X�    ��)����    ��)����    ��z����     ������    ��(����    �c)����    d)����    d)���    d)��    d)$��    d)4�,�    d)D�<�    d)T�L�    d)d�\�    (�(t�l�    (�(��|�    ��z����    �������    (�(����    (�(����    (�(����    d)����    (�(����    �c)���    d)��    d)$��    d)4�,�    d)D�<�    d)T�L�    d)d�\�    d)t�l�    d)��|�    (�(����    (�(����    ��z����    (������    (�(����    (�(����    (�(����    d)���    (�(��    t�$��    �c)4�,�    �c)D�<�    d)T�L�    d)d�\�    (�(t�l�    (�(��|�    d)����    d)����    (�(����    (�(�����x  �  t   �/  �  0   e  >  8     x  u     
e     e        �,d�m �   d    0m     
 H@             �� ��               ���L�� 
	@             �� �� E              ?__LINE__Var@?0???$DumpElements@UD2D1_GRADIENT_STOP@@@@YGXAAVCDumpContext@@PBUD2D1_GRADIENT_STOP@@H@Z@4JA   %      � 4�                                       ���P�h���   ��x���Z        D,d        
 ������Z      T�%  �����                                       ? ����x           x���  �����c        ,d        
 ��h���c      ��%  ��h���c                                       @ ����x           �0�  ����x           ��h�:  ��    x        ��  ����x       ��  ����x      ��[	 ��0�01            ��          \
 ��P��       �(��X  ��    �            �(��(�0�      �� ���        �(�        $  �����      ��  ��    �           |���  �� ��        �(�    D3DXMESHDATATYPE  - D3DXMESHDATA  - _D3DXMESHDATA  1. LPD3DXMESHCONTAINER  `- LPD3DXFRAME  �- LPD3DXANIMATIONSET  5- ID3DXAnimationSet  C- D3DXPLAYBACK_TYPE  C. D3DXKEY_VECTOR3  G- LPD3DXKEY_VECTOR3  ?. D3DXKEY_QUATERNION  M- LPD3DXKEY_QUATERNION  S- LPD3DXKEY_CALLBACK ! m- ID3DXKeyframedAnimationSet  C. _D3DXKEY_VECTOR3  ?. _D3DXKEY_QUATERNION  ;. _D3DXKEY_CALLBACK  9. _D3DXMESHCONTAINER  5. _D3DXFRAME " �- ID3DXCompressedAnimationSet  �- D3DXPRIORITY_TYPE  �- LPD3DXTRACK_DESC  �- D3DXEVENT_TYPE  �- D3DXTRANSITION_TYPE  �- LPD3DXEVENT_DESC  "   D3DXEVENTHANDLE % �- LPD3DXANIMATIONCALLBACKHANDLER   �- LPD3DXANIMATIONCONTROLLER  �- ID3DXAnimationController $ /. ID3DXAnimationCallbackHandler  #. _D3DXTRACK_DESC  . _D3DXEVENT_DESC  / LunaEngine  / CLunaEditorApp �   8     ;-~���j��}��Ǻ�  H   �6w�C��X���b�j\�  �   F��]:V1B��a���  �   	Q4�ʶ6��k ��Q  %  ��PF88`J�ۡ3�}Z  u  3;����)��]V��bJ�  �  ��^t�f��l��^"Y��    V�j�����aRuB  b  -��2~��Sn)�'�4E  �  CW���N�D3I��4  �  9������+���(fb�  B  �:D��׭̏ѺCy  �  j�T��#�I��u���  �  (�ט�^����yk6     Җ�v����󸵒�  i  �s_=��u$ډ�S��  �  �K���N��ű�hsc     ���daz\8�T���<(  X  �8�%�t{�JVz}<  �  �_Q[t�G,R��@�2qC  �  ���j5"�P��bx�� �  >  ��n����֖8S#�;  �  ��B{C�q
���<  �  �Q0WI9.�]aC �t  &  U=��n)�&�|�U��  p  ��3�� 1���Om*ǥg  �  �H�D�u��U�Ql1�X    �[ll�`d�eCzպ�  L  ���zE��^d��M  �      �  <%��	4ml0m����  2	  �!�n��tY�:j��Y  y	  Jc�NTB��UT��߇B  �	  ,�q�î���-��!  
  $�+��@u��۸�N�  �   �   d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\viewtree.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9effect.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\stdafx.h c:\program files (x86)\microsoft visual studio 12.0\vc\include\crtdefs.h c:\program files (x86)\microsoft visual studio 12.0\vc\atlmfc\include\afxpane.h c:\program files (x86)\microsoft visual studio 12.0\vc\atlmfc\include\afxbasepane.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9math.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\propertieswnd.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9mesh.h c:\program files (x86)\microsoft visual studio 12.0\vc\include\math.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9core.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\lunaeditor.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaengine\lunaenginepch.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaengine\lunaengine.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3d9.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9math.inl c:\program files (x86)\microsoft visual studio 12.0\vc\atlmfc\include\afxdockablepane.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9xof.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9shape.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9tex.h c:\program files (x86)\microsoft visual studio 12.0\vc\atlmfc\include\atltypes.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\classview.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9shader.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\outputwnd.cpp d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\outputwnd.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3d9types.h c:\program files (x86)\microsoft visual studio 12.0\vc\include\float.h c:\program files (x86)\microsoft visual studio 12.0\vc\include\crtwrn.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\debug\lunaeditor.pch c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3dx9anim.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\resource.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\mainfrm.h c:\program files (x86)\microsoft directx sdk (june 2010)\include\d3d9caps.h d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\fileview.h $T0 $ebp = $eip $T0 4 + ^ = $ebp $T0 ^ = $esp $T0 8 + =  $20 $T0 208 - ^ =  $23 $T0 212 - ^ =  $24 $T0 216 - ^ =  $T0 $ebp = $eip $T0 4 + ^ = $ebp $T0 ^ = $esp $T0 8 + =  $20 $T0 196 - ^ =  $23 $T0 200 - ^ =  $24 $T0 204 - ^ =  $T0 $ebp = $eip $T0 4 + ^ = $ebp $T0 ^ = $esp $T0 8 + =  $20 $T0 232 - ^ =  $23 $T0 236 - ^ =  $24 $T0 240 - ^ =  $T0 $ebp = $eip $T0 4 + ^ = $ebp $T0 ^ = $esp $T0 8 + =  $20 $T0 212 - ^ =  $23 $T0 216 - ^ =  $24 $T0 220 - ^ =  $T0 $ebp = $eip $T0 4 + ^ = $ebp $T0 ^ = $esp $T0 8 + =  $20 $T0 248 - ^ =  $23 $T0 252 - ^ =  $24 $T0 256 - ^ =  �       L�?  C     G    
 X      \     
 �  �   �  �  
    b �6���PF����j��\D   d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\debug\vc120.pdb d:\engine\tools\lunaeditor\mfc\vs2013\lunaeditor\lunaeditor\outputwnd.cpp                                                                                    ,       H       L       U����   SVWQ������9   ������Y�M��EP�M��    ���u����   �M��    �E�E�P�    �    ���    �E��}� }%j h    h    �M��    ��j �    ;��    �    �    ���    �E��}� }%j h    h    �M��    ��j �    ;��    3�_^[���   ;��    ��]� +   �   @   �   L      Q   �   X   �   h      m   #   u   �      �   �   �   �      �   �   �   �   �      �   '   �   �   �   �   �   �   �   �   U����   SVWQ��4����3   ������Y�M��EP�MQ�UR�M��    _^[���   ;��    ��]� 3   '   C   �   U����   SVWQ��4����3   ������Y�M��M��    �E��     �E�_^[���   ;��    ��]�'   S   0      C   �      �   $           K   �           R
  #     �   q   < G            K   #   7   h<        COutputWnd::COutputWnd  �   �                �  ����{" this  O   �   (           K   @              �4     �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E��M��E��M�H�E�_^[��]�    �   $           @   �          R
  #     �   �   2 G            @   #   7   6)        CSize::CSize  �   �                �  ����b  this     t   initCX     t   initCY  O   �   8           @   �     ,       7 �#   8 �+   9 �4   : �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E��     �M��    _^[���   ;��    ��]�(      0   T   @   �      �   $           H   �           R
  #     �   r   = G            H   #   4   j<        COutputWnd::~COutputWnd  �   �                �  ����{" this  O  �   (           H   @              �,     �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E�M����P�Q�P�Q�@�A�E�_^[��]�    �   $           K   �          R
  #     �   �   ; G            K   #   B   �?        LunaEngine::operator=  �   �                �  ����
/ this     / __that  O    �   X   �   \   �  
 U����   SVWQ��4����3   ������Y�M��M��    �E��t	�E�P�    �E�_^[���   ;��    ��]� '   �   8   �   K   �      �   $           U   �          R
  #     �   �   N G            U   #   ?   i<        COutputWnd::`scalar deleting destructor'  �   �                �  ����{" this  O    �   X   �   \   �  
 U����   SVWQ��4����3   ������Y�M�_^[��]�    �   $           ,   �          R
  #     �   �   J G            ,   #   #   <        CBasePane::AccNotifyObjectFocusEvent  �   �                �  ����*S  this     t   __formal  O�               ,   x             �  �      X      \     
 �      �     
 U����   SVWQ��4����3   ������Y�M�_^[��]�   �   $           *   �           R
  #     �   r   = G            *   #   #   }<        CBasePane::AdjustLayout  �   �                �  ����*S  this  O  �               *   x             �  �   	   X   	   \   	  
 �   	   �   	  
 U����   SVWQ��4����3   ������Y�M��   _^[��]�   �   $           /   �           R
  #     �   u   @ G            /   #   (   !<        CPane::AllowShowOnPaneMenu  �   �                �  �����S  this  O   �               /   `             b  �   2   X   2   \   2  
 �   2   �   2  
 U����   SVWQ��4����3   ������Y�M�j j �M�    �E_^[���   ;��    ��]� +   �   >   �      �   $           H   �          R
  #     �   �   5 G            H   #   2   �;        CPane::CalcSize  �   �                �  �����S  this     t   bVertDock  O�               H   `             �  �   ;   X   ;   \   ;  
 �   ;   �   ;  
 U����   SVWQ��0����4   ������Y�M��} u3��h�    P�M�    ��tF�E����M���l  ��;��    ��u�M����M����  ��;��    ��tǅ0���   �
ǅ0���    ��0���_^[���   ;��    ��]� .   Q   7   �   T   �   q   �   �   �      �   $           �   �          �  #     �   �   B G            �   #   �   <        CDockablePane::CanAcceptPane  �   �                �  �����W  this     /S  pBar  9O       �W   9l       �W   O�   @           �   �     4       h  �#   i  �)   k  �-   n  ��   o  �   f   X   f   \   f  
 �   f   �   f  
 �   f   �   f  
 �   f   �   f  
 U����   SVWQ��4����3   ������Y�M��   _^[��]�   �   $           /   �           R
  #     �   w   B G            /   #   (   <        CDockablePane::CanBeAttached  �   �                �  �����W  this  O �               /   �            s  �   h   X   h   \   h  
 �   h   �   h  
 U����   SVWQ��4����3   ������Y�M��E����   ��_^[��]�   �   $           6   �           R
  #     �   q   < G            6   #   /   <        CBasePane::CanBeClosed  �   �                �  ����%S  this  O   �               6   x             z  �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��0����4   ������Y�M��    ��Ph    �M�Q�    �E����M����  ��;��    ���M����M���  ��;��    #�tǅ0���   �
ǅ0���    ��0���_^[���   ;��    ��]� $   �   -   �   6   �   O   �   j   �   �   �      �   $           �   �          �  #     �   �   8 G            �   #   �   d,        CPane::CanBeDocked  �   �                �  �����S  this     MQ  pDockBar  9J       4S   9e       4S   O  �   8           �   `      ,        �#    �:    ��    �   )   X   )   \   )  
 �   )   �   )  
 �   )   �   )  
 �   )   �   )  
 U����   SVWQ��4����3   ������Y�M��E����   ��_^[��]�   �   $           6   �           R
  #     �   r   = G            6   #   /   H,        CBasePane::CanBeResized  �   �                �  ����%S  this  O  �               6   x             |  �       X       \      
 �       �      
 U����   SVWQ��4����3   ������Y�M��   _^[��]�   �   $           /   �           R
  #     �   n   9 G            /   #   (   <        CBasePane::CanFocus  �   �                �  ����%S  this  O  �               /   x             ~  �      X      \     
 �      �     
 U����   SVWQ��4����3   ������Y�M���jj j �E���M���  ��;��    _^[���   ;��    ��]�>   �   N   �      �   $           V   �           R
  #     �   �   D G            V   #   B   �;        CDockablePane::DockToRecentPos  �   �                �  ����FV  this  99       X   O   �               V   �            �  �   |   X   |   \   |  
 �   |   �   |  
 �   |   �   |  
 U����   SVWQ��4����3   ������Y�M��E����M����  ��;��    _^[���   ;��    ��]�8   �   H   �      �   $           P   �           R
  #     �   �   I G            P   #   <   =,        CBasePane::DoesAllowDynInsertBefore  �   �                �  ����%S  this  93       .S   O  �               P   x             ^  �   �   X   �   \   �  
 �   �   �   �  
 �   �   �   �  
 U����   SVWQ��0����4   ������Y�M��E���h   uǅ0���   �
ǅ0���    ��0���_^[��]�   �   $           R   �           �  #     �   v   A G            R   #   K   Z,        CPane::DoesAllowSiblingBars  �   �                �  �����S  this  O  �               R   `             [  �   /   X   /   \   /  
 �   /   �   /  
 U����   SVWQ��4����3   ������Y�M��E��M���   _^[��]�    �   $           8   �          R
  #     �   �   > G            8   #   /   <        CBasePane::EnableDocking  �   �                �  ����*S  this     "   dwAlignment  O �               8   x             �  �      X      \     
 �      �     
 U����   SVWQ��4����3   ������Y�M��E���  _^[��]�   �   $           3   �           R
  #     �   x   C G            3   #   ,   �;        CDockablePane::GetAHSlideMode  �   �                �  �����W  this  O�               3   �            �  �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E����   _^[��]�   �   $           3   �           R
  #     �   x   C G            3   #   ,   G,        CBasePane::GetControlBarStyle  �   �                �  ����%S  this  O�               3   x             y  �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E����   _^[��]�   �   $           3   �           R
  #     �   y   D G            3   #   ,   ?,        CBasePane::GetEnabledAlignment  �   �                �  ����%S  this  O   �               3   x             d  �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E���h  _^[��]�   �   $           3   �           R
  #     �   u   @ G            3   #   ,   \,        CPane::GetExclusiveRowMode  �   �                �  �����S  this  O   �               3   `             v  �   6   X   6   \   6  
 �   6   �   6  
 U��j�h    d�    P���   SVWQ������:   ������Y�    3�P�E�d�    �M�E샸    u_j�    ���� ����E�    �� ��� t�� ����    ������
ǅ���    �����������E������M싕�����   �E싀   �M�d�    Y_^[���   ;��    ��]�   �   /   T   Q   �   u   �   �   �      �   $           �   �             B     �   �   I        __ehhandler$?GetLunaEngine@CLunaEditorApp@@QAEPAVLunaEngine@@XZ O        __unwindfunclet$?GetLunaEngine@CLunaEditorApp@@QAEPAVLunaEngine@@XZ$0 �   �   C G            �   B   �   �?        CLunaEditorApp::GetLunaEngine  �   �   4            0� 
 :����    �����" this  O�   @           �        4       ,  �B   -  �N   /  ��   1  ��   2  �   �   <   �   @   �  
 �   �   �   �  
 �   �      �  
 5  �   9  �  
 h  �   l  �  
 �� ���P�    YËT$�B�����3��    �    �       �      �   #   �   (   �   U����   SVWQ��4����3   ������Y�M��    _^[���   ;��    ��]�$   �   4   �      �   $           <   �           R
  #     �   t   ? G            <   #   (   k<        COutputWnd::GetMessageMap  �   �                �  �����" this  O�               <   @              �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E���P  ��T  �E��P_^[��]�    �   $           C   �          R
  #     �   }   7 G            C   #   :   �;        CPane::GetMinSize  �   �                �  �����S  this     �'  size  O   �               C   `             K  �   +   X   +   \   +  
 �   +   �   +  
 U����   SVWQ��4����3   ������Y�M��EP�M��    _^[���   ;��    ��]� +   �   ;   �      �   $           E   �          R
  #     �   �   < G            E   #   /   E,        CBasePane::GetPaneIcon  �   �                �  ����*S  this     t   bBigIcon  O  �               E   x             q  �   �   X   �   \   �  
 �   �   �   �  
 U����   SVWQ��4����3   ������Y�M��E����   _^[��]�   �   $           3   �           R
  #     �   r   = G            3   #   ,   F,        CBasePane::GetPaneStyle  �   �                �  ����%S  this  O  �               3   x             x  �   �   X   �   \   �  
 �   �WORD  ��   DBSEEK_FIRSTEQ  �   NAV_MB_HOT % x   NSTCFC_DELAY_REGISTER_NOTIFY  Ú   TapeDriveHardwareError  ��   DBREASON_ROW_INSERT  w�   ADVF_NODATA / �   D3D11_PRIMITIVE_18_CONTROL_POINT_PATCH  �   NAV_MB_PRESSED  ��  	 DBREASON_ROW_RESYNCH " �  � �D3D10_FEATURE_LEVEL_9_3 ) nD   Gdiplus::MetafileTypeEmfPlusDual  �   RPCHTTP_RS_REDIRECT " Ú   TapeDriveUnsupportedMedia  ��   DBSEEK_LASTEQ  ׬   COP_VALUE_ENDSWITH  ׬  	 COP_VALUE_CONTAINS  �   NAV_MB_DISABLED  ��   navOpenInNewWindow  w�   ADVF_PRIMEFIRST  �   RPCHTTP_RS_ACCESS_1 / �   D3D11_PRIMITIVE_19_CONTROL_POINT_PATCH   ��  
 DBREASON_ROW_UNDOCHANGE % Ú  	 TapeDriveScsiConnectionError  ��   DBSEEK_AFTEREQ  Ú  
 TapeDriveTimetoClean  �   RPCHTTP_RS_SESSION   �E   Gdiplus::EmfTypeEmfOnly  ��   D3DRS_ZENABLE  ��   navNoHistory  ׬  
 COP_VALUE_NOTCONTAINS  ��   DBSEEK_AFTER   ��   DBREASON_ROW_UNDOINSERT / �   D3D11_PRIMITIVE_20_CONTROL_POINT_PATCH  w�   ADVF_ONLYONCE  �   RPCHTTP_RS_ACCESS_2  u�   PP_BAR  ��   navNoReadFromCache   ��   DBREASON_ROW_UNDODELETE $ �E   Gdiplus::EmfTypeEmfPlusOnly  w�  @ ADVF_DATAONSTOP  ׬   COP_DOSWILDCARDS  Ú   TapeDriveCleanDriveNow  ��   DBSEEK_BEFOREEQ / �   D3D11_PRIMITIVE_21_CONTROL_POINT_PATCH  ��   D3DRS_FILLMODE  ��    DBSEEK_BEFORE  ��   DBREASON_ROW_UPDATE $ �E   Gdiplus::EmfTypeEmfPlusDual / �   D3D11_PRIMITIVE_22_CONTROL_POINT_PATCH  ��   navNoWriteToCache  u�   PP_BARVERT  ׬   COP_WORD_EQUAL  �   RPCHTTP_RS_INTERFACE  ��  	 D3DRS_SHADEMODE " Ú   TapeDriveMediaLifeExpired  w�   ADVFCACHE_NOHANDLER  w�   ADVFCACHE_FORCEBUILTIN  ��   D3DRS_ZWRITEENABLE  Ú   TapeDriveSnappedTape   ��   DBREASON_ROWSET_CHANGED  ��   navAllowAutosearch  ׬   COP_WORD_STARTSWITH  u�   PP_CHUNK / �   D3D11_PRIMITIVE_23_CONTROL_POINT_PATCH  �   �  / �    D3D11_PRIMITIVE_24_CONTROL_POINT_PATCH  ��   D3DRS_ALPHATESTENABLE ! ׬   COP_APPLICATION_SPECIFIC # xC    Gdiplus::ObjectTypeInvalid  u�   PP_CHUNKVERT  w�    ADVFCACHE_ONSAVE  ��    navBrowserBar  ��   D3DRS_LASTPIXEL  u�   PP_FILL / �  ! D3D11_PRIMITIVE_25_CONTROL_POINT_PATCH ! xC   Gdiplus::ObjectTypeBrush % �   DBREASON_ROWPOSITION_CHANGED  ��  @ navHyperlink  �    DBRANGE_INCLUSIVESTART  ��  � navEnforceRestricted  xC   Gdiplus::ObjectTypePen / �  " D3D11_PRIMITIVE_26_CONTROL_POINT_PATCH  ��   D3DRS_SRCBLEND  �    DBRANGE_INCLUSIVEEND  u�   PP_FILLVERT , �   DBREASON_ROWPOSITION_CHAPTERCHANGED  u�   PP_PULSEOVERLAY  �   DBRANGE_EXCLUSIVESTART   xC   Gdiplus::ObjectTypePath  ��   D3DRS_DESTBLEND  ��   navNewWindowsManaged / �  # D3D11_PRIMITIVE_27_CONTROL_POINT_PATCH % �   DBREASON_ROWPOSITION_CLEARED    �   {0    ��   navUntrustedForDownload / �  $ D3D11_PRIMITIVE_28_CONTROL_POINT_PATCH " xC   Gdiplus::ObjectTypeRegion " �   DBREASON_ROW_ASYNCHINSERT  �   DBRANGE_EXCLUSIVEEND  ��   D3DRS_CULLMODE  u�   PP_MOVEOVERLAY  ��   D3DRS_ZFUNC  ��   navTrustedForActiveX / �  % D3D11_PRIMITIVE_29_CONTROL_POINT_PATCH ! xC   Gdiplus::ObjectTypeImage  �   DBRANGE_EXCLUDENULLS  u�  	 PP_PULSEOVERLAYVERT  �   PARSE_CANONICALIZE   xC   Gdiplus::ObjectTypeFont  u�  
 PP_MOVEOVERLAYVERT / �  & D3D11_PRIMITIVE_30_CONTROL_POINT_PATCH  ��   navOpenInNewTab  �   DBRANGE_PREFIX  ��   D3DRS_ALPHAREF  �   DBRANGE_MATCH  �    DBCOMPAREOPS_LT ( xC   Gdiplus::ObjectTypeStringFormat / �  ' D3D11_PRIMITIVE_31_CONTROL_POINT_PATCH $ ��    USER_MARSHAL_CB_BUFFER_SIZE  u�   PP_TRANSPARENTBAR  ��   D3DRS_ALPHAFUNC  ��   navOpenInBackgroundTab  �   PARSE_FRIENDLY  u�   PP_TRANSPARENTBARVERT  ��    navKeepWordWheelText  �   DBCOMPAREOPS_LE + xC   Gdiplus::ObjectTypeImageAttributes  ��   D3DRS_DITHERENABLE / �  ( D3D11_PRIMITIVE_32_CONTROL_POINT_PATCH  �   PARSE_SECURITY_URL  �   NdisFddiTypeIsolated ! ��   USER_MARSHAL_CB_MARSHALL  �   PARSE_ROOTDOCUMENT # ��   USER_MARSHAL_CB_UNMARSHALL  �   NdisFddiTypeLocalA ) xC  	 Gdiplus::ObjectTypeCustomLineCap  ��   D3DRS_ALPHABLENDENABLE  ��   DBRANGE_MATCH_N_SHIFT  �   DBCOMPAREOPS_EQ  ��   @navVirtualTab  �   DBCOMPAREOPS_GE  ��   D3DRS_FOGENABLE  xC  	 Gdiplus::ObjectTypeMax " ;�    D3D_SRV_DIMENSION_UNKNOWN  �   NdisFddiTypeLocalB  �   PARSE_DOCUMENT  ��   USER_MARSHAL_CB_FREE  ��   PBBS_NORMAL  ��  � DBRANGE_MATCH_N_MASK # ��  � �navBlockRedirectsXDomain ! ;�   D3D_SRV_DIMENSION_BUFFER  ��   PBBS_PARTIAL  xC   Gdiplus::ObjectTypeMin  �   DBCOMPAREOPS_GT $ ��  �   navOpenNewForegroundTab  �   PARSE_ANCHOR  �   NdisFddiTypeLocalAB  ��   D3DRS_SPECULARENABLE   �   DBCOMPAREOPS_BEGINSWITH ! �   PARSE_ENCODE_IS_UNESCAPE $ ;�   D3D_SRV_DIMENSION_TEXTURE1D  �   NdisFddiTypeLocalS # ��  �   navTravelLogScreenshot  ��  " D3DRS_FOGCOLOR  �   DBCOMPAREOPS_CONTAINS ) ;�   D3D_SRV_DIMENSION_TEXTURE1DARRAY  ��  # D3DRS_FOGTABLEMODE  ��  �   navDeferUnload  ν   PBBVS_NORMAL  �   NdisFddiTypeWrapA  �   PARSE_DECODE_IS_ESCAPE  ��  $ D3DRS_FOGSTART  �   DBCOMPAREOPS_NE  �   NdisFddiTypeWrapB  ��  �   navSpeculative  �  	 PARSE_PATH_FROM_URL  ν   PBBVS_PARTIAL $ ;�   D3D_SRV_DIMENSION_TEXTURE2D ) ;�   D3D_SRV_DIMENSION_TEXTURE2DARRAY  �  
 PARSE_URL_FROM_PATH  �   DBCOMPAREOPS_IGNORE , �    Ndis802_11StatusType_Authentication  ��  % D3DRS_FOGEND  �   NdisFddiTypeWrapAB   ��  �   navSuggestNewWindow  ��  & D3DRS_FOGDENSITY  ��   PBFS_NORMAL  ��  �    navSuggestNewTab  �  	 NdisFddiTypeWrapS - �   Ndis802_11StatusType_MediaStreamMode & ;�   D3D_SRV_DIMENSION_TEXTURE2DMS  T�   DBEDITMODE_NONE # �   DBCOMPAREOPS_CASESENSITIVE  �   PARSE_MIME  ��  0 D3DRS_RANGEFOGENABLE  ��  �  @ navReserved1  T�   DBEDITMODE_UPDATE 1 �   Ndis802_11StatusType_PMKID_CandidateList  �   PARSE_SERVER  �  
 NdisFddiTypeCWrapA + ;�   D3D_SRV_DIMENSION_TEXTURE2DMSARRAY  ��   PBFS_ERROR  �    DSD_FORWARD % �    DBCOMPAREOPS_CASEINSENSITIVE  �   DSD_BACKWARD   �   Ndis802_11StatusTypeMax   ��  �  � navHomepageNavigate  ��  4 D3DRS_STENCILENABLE  Չ    COMP_EQUAL  T�   DBEDITMODE_ADD $ ;�   D3D_SRV_DIMENSION_TEXTURE3D  ��   SMIM_TYPE  �   PARSE_SCHEMA  ��   PBFS_PAUSED  �   NdisFddiTypeCWrapB  ��   SMIM_FLAGS - �E  � Gdiplus::WmfRecordTypeSetBkColor  �   PARSE_SITE  Չ   COMP_NOTLESS # q�  	 DBCOMPAREOPS_NOTBEGINSWITH & ;�  	 D3D_SRV_DIMENSION_TEXTURECUBE  �   NdisFddiTypeCWrapS  ��   PBFS_PARTIAL  ��  5 D3DRS_STENCILFAIL  ��   SMIM_ICON ! q�  
 DBCOMPAREOPS_NOTCONTAINS  r�    DWPOS_CENTER  �   PARSE_DOMAIN  �   NdisFddiTypeThrough + ;�  
 D3D_SRV_DIMENSION_TEXTURECUBEARRAY  Y�   WICAsShotParameterSet  ��    REFRESH_NORMAL  ��  6 D3DRS_STENCILZFAIL  r�   DWPOS_TILE  ��   REFRESH_IFEXPIRED , �E  � Gdiplus::WmfRecordTypeSetBkMode  Z�   PBFVS_NORMAL # ;�   D3D_SRV_DIMENSION_BUFFEREX  �   PARSE_LOCATION  ��  7 D3DRS_STENCILPASS $ Y�   WICUserAdjustedParameterSet $ Y�   WICAutoAdjustedParameterSet  ��  8 D3DRS_STENCILFUNC  ��   REFRESH_COMPLETELY  r�   DWPOS_STRETCH  Z�   PBFVS_ERROR  �   PARSE_SECURITY_DOMAIN  �   SMIT_SEPARATOR $ ;�    D3D10_SRV_DIMENSION_UNKNOWN  �   PARSE_ESCAPE  �    DBASYNCHOP_OPEN  �   SMIT_STRING + Y�  ����WICRAWPARAMETERSET_FORCE_DWORD  ��  9 D3DRS_STENCILREF - �E  � Gdiplus::WmfRecordTypeSetMapMode # ;�   D3D10_SRV_DIMENSION_BUFFER  Z�   PBFVS_PAUSED  r�   DWPOS_FIT  �   NdisFddiRingIsolated & 9�    NdisPauseFunctionsUnsupported  r�   DWPOS_FILL & ;�   D3D10_SRV_DIMENSION_TEXTURE1D  �   PARSE_UNESCAPE  Z�   PBFVS_PARTIAL  ��  : D3DRS_STENCILMASK  ��  ; D3DRS_STENCILWRITEMASK # �   NdisFddiRingNonOperational  >�   WICRawRenderModeDraft + ;�   D3D10_SRV_DIMENSION_TEXTURE1DARRAY * �E  � Gdiplus::WmfRecordTypeSetROP2  �   SMIF_ICON # 9�   NdisPauseFunctionsSendOnly  r�   DWPOS_SPAN   �   NdisFddiRingOperational  >�   WICRawRenderModeNormal  5�   RP_GRIPPER % ��    DBASYNCHPHASE_INITIALIZATION  ��  < D3DRS_TEXTUREFACTOR  �   SMIF_ACCELERATOR & ;�   D3D10_SRV_DIMENSION_TEXTURE2D  �?    SLDF_DEFAULT & 9�   NdisPauseFunctionsReceiveOnly ! ��   DBASYNCHPHASE_POPULATION , �E  � Gdiplus::WmfRecordTypeSetRelAbs  ��   PSU_DEFAULT  �?   SLDF_HAS_ID_LIST  �   SMIF_DROPTARGET $ >�   WICRawRenderModeBestQuality ) �   GUIDKIND_DEFAULT_SOURCE_DISP_IID + ;�   D3D10_SRV_DIMENSION_TEXTURE2DARRAY  ��  � D3DRS_WRAP0 ) 9�   NdisPauseFunctionsSendAndReceive   �    TUNNEL_TYPE_NONE  �   NdisFddiRingDetect  5�   RP_GRIPPERVERT & �   NdisFddiRingNonOperationalDup  �?   SLDF_HAS_LINK_INFO   �   TUNNEL_TYPE_OTHER  ��   PSU_SECURITY_URL_ONLY ( ;�   D3D10_SRV_DIMENSION_TEXTURE2DMS  ��  � D3DRS_WRAP1  5�   RP_BAND " 9�   NdisPauseFunctionsUnknown ) >�  ����WICRAWRENDERMODE_FORCE_DWORD  �   SMIF_SUBMENU  ��   DBASYNCHPHASE_COMPLETE   �   TUNNEL_TYPE_DIRECT # �   NdisFddiRingOperationalDup  5�   RP_CHEVRON 2 �E  � Gdiplus::WmfRecordTypeSetPolyFillMode - ;�   D3D10_SRV_DIMENSION_TEXTURE2DMSARRAY  �    SMIF_CHECKED  ��  � D3DRS_WRAP2  �?   SLDF_HAS_NAME  ��   DBASYNCHPHASE_CANCELED   �   TUNNEL_TYPE_6TO4 & ;�   D3D10_SRV_DIMENSION_TEXTURE3D  �   NdisFddiRingDirected  ��  � D3DRS_WRAP3  �  @ SMIF_DROPCASCADE  5�   RP_CHEVRONVERT  �?   SLDF_HAS_RELPATH   �   TUNNEL_TYPE_ISATAP  5�   RP_BACKGROUND  �   NdisFddiRingTrace  :    afxWinHelp 4 �E  � Gdiplus::WmfRecordTypeSetStretchBltMode ( ;�  	 D3D10_SRV_DIMENSION_TEXTURECUBE  ֈ   QUERY_EXPIRATION_DATE  ��  � D3DRS_WRAP4  �?   SLDF_HAS_WORKINGDIR  �  � SMIF_HIDDEN  "�    HHWIN_NAVTAB_TOP  8�    DBSORT_ASCENDING & ;�    D3D10_1_SRV_DIMENSION_UNKNOWN   �   TUNNEL_TYPE_TEREDO  �?    SLDF_HAS_ARGS " ֈ   QUERY_TIME_OF_LAST_CHANGE  ��  � D3DRS_WRAP5  :   afxHTMLHelp  5�   RP_SPLITTER  �   SMIF_DISABLED   �   TUNNEL_TYPE_IPHTTPS  �   SMIF_TRACKPOPUP % ;�   D3D10_1_SRV_DIMENSION_BUFFER  8�   DBSORT_DESCENDING  ��  � D3DRS_WRAP6 3 �E  � Gdiplus::WmfRecordTypeSetTextCharExtra  ֈ   QUERY_CONTENT_ENCODING  5�   RP_SPLITTERVERT  "�   HHWIN_NAVTAB_LEFT  �?  @ SLDF_HAS_ICONLOCATION  �?  � SLDF_UNICODE  ֈ   QUERY_CONTENT_TYPE  �   SMIF_DEMOTED ( ;�   D3D10_1_SRV_DIMENSION_TEXTURE1D  "�   HHWIN_NAVTAB_BOTTOM  ��  � D3DRS_WRAP7 / �E  �	 Gdiplus::WmfRecordTypeSetTextColor  �?   SLDF_FORCE_NO_LINKINFO  �   CHEVS_NORMAL  ��  � D3DRS_CLIPPING - ;�   D3D10_1_SRV_DIMENSION_TEXTURE1DARRAY  �   SMIF_ALTSTATE  ֈ   QUERY_REFRESH  '�   NdisFddiStateOff  ��  � D3DRS_LIGHTING $ ��   DBCOMMANDPERSISTFLAG_NOSAVE  �?   SLDF_HAS_EXP_SZ ( ;�   D3D10_1_SRV_DIMENSION_TEXTURE2D  �   CHEVS_HOT  '�   NdisFddiStateBreak  +�    HH_TAB_CONTENTS  �   SMIF_DRAGNDROP  ֈ   QUERY_RECOMBINE  �   CHEVS_PRESSED 7 �E  �
 Gdiplus::WmfRecordTypeSetTextJustification - ;�   D3D10_1_SRV_DIMENSION_TEXTURE2DARRAY  +�   HH_TAB_INDEX  ֈ   QUERY_CAN_NAVIGATE  '�   NdisFddiStateTrace  �?   SLDF_RUN_IN_SEPARATE # �    IF_ADMINISTRATIVE_DISABLED  ��  � D3DRS_AMBIENT  �    SMIF_NEW  E�    FindStreamInfoStandard % 8�    DBCOMMANDPERSISTFLAG_DEFAULT  '�   NdisFddiStateConnect  ֈ   QUERY_USES_NETWORK  +�   HH_TAB_SEARCH * ;�   D3D10_1_SRV_DIMENSION_TEXTURE2DMS  ��  � D3DRS_FOGVERTEXMODE " �   IF_ADMINISTRATIVE_ENABLED  �?   SLDF_HAS_DARWINID  -�   CHEVSV_NORMAL % �   IF_ADMINISTRATIVE_DEMANDDIAL  ��  � D3DRS_COLORVERTEX / �E  � Gdiplus::WmfRecordTypeSetWindowOrg  +�   HH_TAB_FAVORITES ) 8�   DBCOMMANDPERSISTFLAG_PERSISTVIEW  '�   NdisFddiStateNext  �?    SLDF_RUNAS_USER # E�   FindStreamInfoMaxInfoLevel  ֈ  	 QUERY_IS_CACHED / ;�   D3D10_1_SRV_DIMENSION_TEXTURE2DMSARRAY   ֈ  
 QUERY_IS_INSTALLEDENTRY  �?   @SLDF_HAS_EXP_ICON_SZ  '�   NdisFddiStateSignal ( ;�   D3D10_1_SRV_DIMENSION_TEXTURE3D  -�   CHEVSV_HOT  ��  � D3DRS_LOCALVIEWER  +�   HH_TAB_HISTORY . 8�   DBCOMMANDPERSISTFLAG_PERSISTPROCEDURE  '�   NdisFddiStateJoin / �E  � Gdiplus::WmfRecordTypeSetWindowExt  ��  � D3DRS_NORMALIZENORMALS " ֈ   QUERY_IS_CACHED_OR_MAPPED  �?  � �SLDF_NO_PIDL_ALIAS  +�   HH_TAB_AUTHOR * ;�  	 D3D10_1_SRV_DIMENSION_TEXTURECUBE  -�   CHEVSV_PRESSED  ֈ   QUERY_USES_CACHE  '�   NdisFddiStateVerify / ;�  
 D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY  �?  �   SLDF_FORCE_UNCNAME $ ��  � D3DRS_DIFFUSEMATERIALSOURCE  +�   HH_TAB_CUSTOM_FIRST  '�  	 NdisFddiStateActive $ �?  �   SLDF_RUN_WITH_SHIMLAYER  ֈ   QUERY_IS_SECURE 1 �E  � Gdiplus::WmfRecordTypeSetViewportOrg  `�   SPLITS_NORMAL   ƞ    DBCONSTRAINTTYPE_UNIQUE  +�   HH_TAB_CUSTOM_LAST $ ;�    D3D11_SRV_DIMENSION_UNKNOWN  ;�   IfOperStatusUp % ��  � D3DRS_SPECULARMATERIALSOURCE  �    VT_EMPTY $ �?  �   SLDF_FORCE_NO_LINKTRACK  `�   SPLITS_HOT $ ƞ   DBCONSTRAINTTYPE_FOREIGNKEY $ ��  � D3DRS_AMBIENTMATERIALSOURCE # ;�   D3D11_SRV_DIMENSION_BUFFER  ;�   IfOperStatusDown  �   VT_NULL  ֈ   QUERY_IS_SAFE # g5    DWRITE_PIXEL_GEOMETRY_FLAT ! '�  
 NdisFddiStateMaintenance % ��  � D3DRS_EMISSIVEMATERIALSOURCE  `�   SPLITS_PRESSED " g5   DWRITE_PIXEL_GEOMETRY_RGB  ;�   IfOperStatusTesting  &�    SPBEGINF_NORMAL 1 �E  � Gdiplus::WmfRecordTypeSetViewportExt  �   VT_I2 ( �?  �   SLDF_ENABLE_TARGET_METADATA & ;�   D3D11_SRV_DIMENSION_TEXTURE1D $ ƞ   DBCONSTRAINTTYPE_PRIMARYKEY  �    PDSIF_DEFAULT ! ֈ   QUERY_USES_HISTORYFOLDER  �   VT_I4  ;�   IfOperStatusUnknown + ֈ   QUERY_IS_CACHED_AND_USABLE_OFFLINE  ��  � D3DRS_VERTEXBLEND  ƞ   DBCONSTRAINTTYPE_CHECK  &�   SPBEGINF_AUTOTIME , �?  �   SLDF_DISABLE_LINK_PATH_TRACKING  �   PDSIF_ININVERTEDINDEX + ;�   D3D11_SRV_DIMENSION_TEXTURE1DARRAY " g5   DWRITE_PIXEL_GEOMETRY_BGR & ;�   D3D11_SRV_DIMENSION_TEXTURE2D  �   PDSIF_ISCOLUMN  ;�   IfOperStatusDormant  ��  � D3DRS_CLIPPLANEENABLE 2 �E  � Gdiplus::WmfRecordTypeOffsetWindowOrg  &�   SPBEGINF_NOPROGRESSBAR  ֳ   SPLITSV_NORMAL  �   VT_R4 7 �?  �    SLDF_DISABLE_KNOWNFOLDER_RELATIVE_TRACKING  ֳ   SPLITSV_HOT & i5    DWRITE_RENDERING_MODE_DEFAULT  �   VT_R8  ٵ    NdisWanMediumHub ! &�    SPBEGINF_MARQUEEPROGRESS  �?  �  @ SLDF_NO_KF_ALIAS  ��  � D3DRS_POINTSIZE  ;�   IfOperStatusNotPresent  �   PDSIF_ISCOLUMNSPARSE + ;�   D3D11_SRV_DIMENSION_TEXTURE2DARRAY  �   �   ֳ   SPLITSV_PRESSED  ٵ   NdisWanMediumX_25  �   PDSIF_ALWAYSINCLUDE  ��    DOT11_DS_CHANGED 1 �E  � Gdiplus::WmfRecordTypeScaleWindowExt & i5   DWRITE_RENDERING_MODE_ALIASED  �   VT_CY  ��  � D3DRS_POINTSIZE_MIN # ;�   IfOperStatusLowerLayerDown   &�  @ SPBEGINF_NOCANCELBUTTON  ��    DBUPDELRULE_NOACTION $ �?  �  � SLDF_ALLOW_LINK_TO_LINK ( ;�   D3D11_SRV_DIMENSION_TEXTURE2DMS ! �?  �   SLDF_UNALIAS_ON_SAVE  ٵ   NdisWanMediumIsdn  ��   DOT11_DS_UNCHANGED - ;�   D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY  �   PDSIF_USEFORTYPEAHEAD * i5   DWRITE_RENDERING_MODE_GDI_CLASSIC  ��   DBUPDELRULE_CASCADE  �   VT_DATE   ��  � D3DRS_POINTSPRITEENABLE  �   VT_BSTR  M�   SBP_ARROWBTN 4 �E  � Gdiplus::WmfRecordTypeOffsetViewportOrg * i5   DWRITE_RENDERING_MODE_GDI_NATURAL & ;�   D3D11_SRV_DIMENSION_TEXTURE3D  ��   DOT11_DS_UNKNOWN  �    IMPORT_OBJECT_CODE  ��   DBUPDELRULE_SETNULL  ��  � D3DRS_POINTSCALEENABLE ) �?  �   SLDF_PREFER_ENVIRONMENT_PATH  ٵ   NdisWanMediumSerial  �  	 VT_DISPATCH  ��  � D3DRS_POINTSCALE_A 2 �?  �   SLDF_KEEP_LOCAL_IDLIST_FOR_UNC_TARGET  ��   DBFINDFLAGS_FINDNEXT ( ;�  	 D3D11_SRV_DIMENSION_TEXTURECUBE  ^�    MibIfTableNormal  w�    SPACTION_NONE  ��   DBUPDELRULE_SETDEFAULT & i5   DWRITE_RENDERING_MODE_NATURAL   ٵ   NdisWanMediumFrameRelay  M�   SBP_THUMBBTNHORZ  �   IMPORT_OBJECT_DATA �   �/   M�   SBP_THUMBBTNVERT  ��  � D3DRS_POINTSCALE_B  ^�   MibIfTableRaw  w�   SPACTION_MOVING  �  
 VT_ERROR 3 �E  � Gdiplus::WmfRecordTypeScaleViewportExt , �?  �   SLDF_PERSIST_VOLUME_ID_RELATIVE - ;�  
 D3D11_SRV_DIMENSION_TEXTURECUBEARRAY  �   IMPORT_OBJECT_CONST 0 i5   DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC  ٵ   NdisWanMediumAtm  ��   DBFINDFLAGS_FINDPRIOR  �,    D2D1_WINDOW_STATE_NONE % ;�   D3D11_SRV_DIMENSION_BUFFEREX  �   VT_BOOL & >D    Gdiplus::DebugEventLevelFatal # ��   DBFINDFLAGS_INCLUDECURRENT  <�   AclRevisionInformation  w�   SPACTION_COPYING  �?  ����SLDF_VALID  ��  � D3DRS_POINTSCALE_C  ٵ   NdisWanMediumSonet & i5   DWRITE_RENDERING_MODE_OUTLINE  M�   SBP_LOWERTRACKHORZ  U�    IMPORT_OBJECT_ORDINAL  M�   SBP_UPPERTRACKHORZ ) �E  � Gdiplus::WmfRecordTypeLineTo ( >D   Gdiplus::DebugEventLevelWarning # ��  � D3DRS_MULTISAMPLEANTIALIAS  H�    DBMATCHTYPE_FULL  w�   SPACTION_RECYCLING  �   VT_VARIANT 4 i5   DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC  ٵ   NdisWanMediumSW56K # �,   D2D1_WINDOW_STATE_OCCLUDED  �   MIB_TCP_STATE_CLOSED  <�   AclSizeInformation ' �,   ��D2D1_WINDOW_STATE_FORCE_DWORD  �?  �   �SLDF_RESERVED  U�   IMPORT_OBJECT_NAME ! w�   SPACTION_APPLYINGATTRIBS  H�   DBMATCHTYPE_NONE 4 i5   DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL  �   MIB_TCP_STATE_LISTEN  M�   SBP_LOWERTRACKVERT  �   VT_UNKNOWN  ��  � D3DRS_MULTISAMPLEMASK  ٵ   NdisWanMediumPPTP  ��  � D3DRS_PATCHEDGESTYLE 0 i5   DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL  �   VT_DECIMAL % U�   IMPORT_OBJECT_NAME_NO_PREFIX ) �E  � Gdiplus::WmfRecordTypeMoveTo  ٵ  	 NdisWanMediumL2TP  �    dot11_AC_param_BE  w�   SPACTION_DOWNLOADING  �   MIB_TCP_STATE_SYN_SENT  H�   DBMATCHTYPE_PARTIAL  M�   SBP_UPPERTRACKVERT $ w�   SPACTION_SEARCHING_INTERNET  �   dot11_AC_param_BK : i5   DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC  M�   SBP_GRIPPERHORZ  �   MIB_TCP_STATE_SYN_RCVD  ٵ  
 NdisWanMediumIrda & U�   IMPORT_OBJECT_NAME_UNDECORATE   ��  � D3DRS_DEBUGMONITORTOKEN  �   VT_I1  M�  	 SBP_GRIPPERVERT  �   MIB_TCP_STATE_ESTAB  ٵ   NdisWanMediumParallel  w�   SPACTION_CALCULATING 2 �E  � Gdiplus::WmfRecordTypeExcludeClipRect  �   dot11_AC_param_VI  �   VT_UI1  ��  � D3DRS_POINTSIZE_MAX  �   VT_UI2  F�   COMIMAGE_FLAGS_ILONLY  ٵ   NdisWanMediumPppoe ' ��  � D3DRS_INDEXEDVERTEXBLENDENABLE  M�  
 SBP_SIZEBOX   �   MIB_TCP_STATE_FIN_WAIT1  w�   SPACTION_UPLOADING  �   dot11_AC_param_VO ! x�   DBDEFERRABILITY_DEFERRED  ٵ   NdisWanMediumSSTP % F�   COMIMAGE_FLAGS_32BITREQUIRED  �   dot11_AC_param_max 4 �E  � Gdiplus::WmfRecordTypeIntersectClipRect   �   MIB_TCP_STATE_FIN_WAIT2  �   VT_UI4 # x�   DBDEFERRABILITY_DEFERRABLE  �    PUIFNF_DEFAULT  ��  � D3DRS_COLORWRITEENABLE ! w�  	 SPACTION_SEARCHING_FILES  �   VT_I8  ٵ   NdisWanMediumAgileVPN  �   ABS_UPNORMAL  ~�    IDL_CS_NO_CONVERT " F�   COMIMAGE_FLAGS_IL_LIBRARY ! �   MIB_TCP_STATE_CLOSE_WAIT  ��  � D3DRS_TWEENFACTOR  �   PUIFNF_MNEMONIC  w�  
 SPACTION_DELETING  �   ABS_UPHOT  �   VT_UI8 & �E  � Gdiplus::WmfRecordTypeArc  ٵ   NdisWanMediumGre   ~�   IDL_CS_IN_PLACE_CONVERT  ��  � D3DRS_BLENDOP  �  	 MIB_TCP_STATE_CLOSING ( F�   COMIMAGE_FLAGS_STRONGNAMESIGNED  w�   SPACTION_RENAMING  ��  � D3DRS_POSITIONDEGREE " ~�   IDL_CS_NEW_BUFFER_CONVERT  w�   SPACTION_FORMATTING  �   ABS_UPPRESSED  �  
 MIB_TCP_STATE_LAST_ACK   ٵ   NdisWanMediumSubTypeMax  �   VT_INT ) F�   COMIMAGE_FLAGS_NATIVE_ENTRYPOINT   N�    PROPBAG2_TYPE_UNDEFINED  w�   SPACTION_COPY_MOVING   �   MIB_TCP_STATE_TIME_WAIT  �    PUIF_DEFAULT * �E  � Gdiplus::WmfRecordTypeEllipse  ��  � D3DRS_NORMALDEGREE  N�   PROPBAG2_TYPE_DATA  �   ABS_UPDISABLED * F�  �   COMIMAGE_FLAGS_TRACKDEBUGDATA  �   VT_UINT  �   VT_VOID  F�   COR_VERSION_MAJOR_V2   ��  � D3DRS_SCISSORTESTENABLE  �   PUIF_RIGHTALIGN ! �   MIB_TCP_STATE_DELETE_TCB  �   ABS_DOWNNORMAL  N�   PROPBAG2_TYPE_URL " ��  � D3DRS_SLOPESCALEDEPTHBIAS  N�   PROPBAG2_TYPE_OBJECT  �   PUIF_NOLABELININFOTIP , �E  � Gdiplus::WmfRecordTypeFloodFill  �   ABS_DOWNHOT  �   VT_HRESULT  F�   COR_VERSION_MAJOR $ ��  � D3DRS_ANTIALIASEDLINEENABLE ! ڐ   SPTEXT_ACTIONDESCRIPTION  �   VT_PTR  �   ABS_DOWNPRESSED  N�   PROPBAG2_TYPE_STREAM  F�   COR_VERSION_MINOR  X�    NdisWanHeaderNative   F�   COR_DELETED_NAME_LENGTH ( ��    TcpConnectionOffloadStateInHost  �   VT_SAFEARRAY  ӧ    REGCLS_SINGLEUSE & �E  � Gdiplus::WmfRecordTypePie  X�   NdisWanHeaderEthernet  N�   PROPBAG2_TYPE_STORAGE  �   ABS_DOWNDISABLED # ��  � D3DRS_MINTESSELLATIONLEVEL  ڐ   SPTEXT_ACTIONDETAIL , ��   TcpConnectionOffloadStateOffloading  ӧ   REGCLS_MULTIPLEUSE  �   VT_CARRAY " F�   COR_VTABLEGAP_NAME_LENGTH  �  	 ABS_LEFTNORMAL  N�   PROPBAG2_TYPE_MONIKER # ��  � D3DRS_MAXTESSELLATIONLEVEL  Y�   TYMED_HGLOBAL  ��    PUIFFDF_DEFAULT  Y�   TYMED_FILE  F�   NATIVE_TYPE_MAX_CB , �E  � Gdiplus::WmfRecordTypeRectangle  �  
 ABS_LEFTHOT + ��   TcpConnectionOffloadStateOffloaded  �   VT_USERDEFINED  ӧ   REGCLS_MULTI_SEPARATE  ��  � D3DRS_ADAPTIVETESS_X  ��   PUIFFDF_RIGHTTOLEFT  Y�   TYMED_ISTREAM  ��   PUIFFDF_SHORTFORMAT  ��  � D3DRS_ADAPTIVETESS_Y - F�  � COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE + ��   TcpConnectionOffloadStateUploading  ӧ   REGCLS_SUSPENDED  �   VT_LPSTR  �   ABS_LEFTPRESSED % ��   TcpConnectionOffloadStateMax  ӧ   REGCLS_SURROGATE  ��    NdisWanRaw  �   ABS_LEFTDISABLED  Y�   TYMED_ISTORAGE , �E  � Gdiplus::WmfRecordTypeRoundRect  �   VT_LPWSTR  ��    SFBID_PIDLCHANGED  ��  � D3DRS_ADAPTIVETESS_Z  :    PMCCounter   F�   IMAGE_COR_MIH_METHODRVA  ��   PUIFFDF_NOTIME " �j   OLEGETMONIKER_ONLYIFTHERE  �   ABS_RIGHTNORMAL  Y�    SVUIA_DEACTIVATE  ��   PUIFFDF_FRIENDLYDATE  F�   IMAGE_COR_MIH_EHRVA  ��  � D3DRS_ADAPTIVETESS_W  Y�   TYMED_GDI  �  $ VT_RECORD  :   MaxHardwareCounterType  ��   NdisWanErrorControl ! F�   IMAGE_COR_MIH_BASICBLOCK  �   ABS_RIGHTHOT  �  % VT_INT_PTR  ��   NdisWanReliable " �j   OLEGETMONIKER_FORCEASSIGN ) �E  � Gdiplus::WmfRecordTypePatBlt  Y�   SVUIA_ACTIVATE_NOFOCUS  Y�    TYMED_MFPICT ) ��  � D3DRS_ENABLEADAPTIVETESSELLATION   ��   PRINTFLAG_MAYBOTHERUSER  �  & VT_UINT_PTR  Y�  @ TYMED_ENHMF  F�   COR_VTABLE_32BIT " ��  � D3DRS_TWOSIDEDSTENCILMODE  <�    MBHANDCID_PIDLSELECT  �   ABS_RIGHTPRESSED  �j   OLEGETMONIKER_UNASSIGN  Y�   SVUIA_ACTIVATE_FOCUS ! ǐ    COINITBASE_MULTITHREADED  F�   COR_VTABLE_64BIT  ��   PRINTFLAG_PROMPTUSER ) �E  �  Gdiplus::WmfRecordTypeSaveDC  Y�    TYMED_NULL  �  @ VT_FILETIME  C�    DBTYPE_EMPTY  Y�   SVUIA_INPLACEACTIVATE  ��  � D3DRS_CCW_STENCILFAIL " �j   OLEGETMONIKER_TEMPFORUSER  �   ABS_RIGHTDISABLED  �  A VT_BLOB  �   ABS_UPHOVER " F�   COR_VTABLE_FROM_UNMANAGED  C�   DBTYPE_NULL  s�    ProcessDEPPolicy  ��  � D3DRS_CCW_STENCILZFAIL ' ��   PRINTFLAG_USERMAYCHANGEPRINTER  s�   ProcessASLRPolicy 3 F�   COR_VTABLE_FROM_UNMANAGED_RETAIN_APPDOMAIN  C�   DBTYPE_I2  ��  � D3DRS_CCW_STENCILPASS + �E  � Gdiplus::WmfRecordTypeSetPixel $ ��   PRINTFLAG_RECOMPOSETODEVICE  �  B VT_STREAM  �   ABS_DOWNHOVER  �  C VT_STORAGE % F�   COR_VTABLE_CALL_MOST_DERIVED $ ��   PRINTFLAG_DONTACTUALLYPRINT  �   ABS_LEFTHOVER  C�   DBTYPE_I4  �    ComputerNameNetBIOS  ��  � D3DRS_CCW_STENCILFUNC  ��   OLEWHICHMK_CONTAINER ! s�   ProcessDynamicCodePolicy  C�   DBTYPE_R4 " F�    IMAGE_COR_EATJ_THUNK_SIZE   �   ComputerNameDnsHostname  �    HGSC_NONE  �  D VT_STREAMED_OBJECT 0 �E  �  Gdiplus::WmfRecordTypeOffsetClipRgn  ��   OLEWHICHMK_OBJREL  �   ABS_RIGHTHOVER   ��  � D3DRS_COLORWRITEENABLE1 " ��    PRINTFLAG_FORCEPROPERTIES ' s�   ProcessStrictHandleCheckPolicy   ��  � D3DRS_COLORWRITEENABLE2  ��   OLEWHICHMK_OBJFULL  �  E VT_STORED_OBJECT  �   ComputerNameDnsDomain  ��  @ PRINTFLAG_PRINTTOFILE  C�   DBTYPE_R8  �   HGSC_MUSICLIBRARY ' s�   ProcessSystemCallDisablePolicy  F�   MAX_CLASS_NAME   ��  � D3DRS_COLORWRITEENABLE3 % s�   ProcessMitigationOptionsMask  �  F VT_BLOB_OBJECT  �   HGSC_PICTURESLIBRARY & �   ComputerNameDnsFullyQualified * �E  �! Gdiplus::WmfRecordTypeTextOut  C�   DBTYPE_CY  i�   SCRBS_NORMAL  F�   MAX_PACKAGE_NAME + s�   ProcessExtensionPointDisablePolicy  C�   DBTYPE_DATE $ �   ComputerNamePhysicalNetBIOS  ��    Ndis802_11FH  i�   SCRBS_HOT  �  G VT_CF  ��  � D3DRS_BLENDFACTOR  �   HGSC_VIDEOSLIBRARY  ��   USERCLASSTYPE_FULL  ��  � D3DRS_SRGBWRITEENABLE  s�   ProcessReserved1Policy  �  H VT_CLSID ) �E  �"	 Gdiplus::WmfRecordTypeBitBlt  i�   SCRBS_PRESSED  C�   DBTYPE_BSTR ( �   ComputerNamePhysicalDnsHostname  ��   Ndis802_11DS  �   HGSC_DOCUMENTSLIBRARY  s�   ProcessSignaturePolicy  ��   USERCLASSTYPE_SHORT  ��   Ndis802_11OFDM5  �  I VT_VERSIONED_STREAM  i�   SCRBS_DISABLED & �   ComputerNamePhysicalDnsDomain  C�  	 DBTYPE_IDISPATCH  ��  � D3DRS_DEPTHBIAS  �   HGSC_PRINTERS  �  �VT_BSTR_BLOB . �   ComputerNamePhysicalDnsFullyQualified - �E  �# Gdiplus::WmfRecordTypeStretchBlt  ��   USERCLASSTYPE_APPNAME  ��   Ndis802_11OFDM24  i�   SCRBS_HOVER  ��  � D3DRS_WRAP8  C�  
 DBTYPE_ERROR # s�  	 MaxProcessMitigationPolicy  �   ComputerNameMax  �   VT_VECTOR  ��   CTRLINFO_EATS_RETURN  C�   DBTYPE_BOOL  ��   Ndis802_11Automode  ��  � D3DRS_WRAP9  C�   DBTYPE_VARIANT ! ��   Ndis802_11NetworkTypeMax ( ��   IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF  �    VT_ARRAY   �   SZB_RIGHTALIGN * �E  �$ Gdiplus::WmfRecordTypePolygon  ��   CTRLINFO_EATS_ESCAPE  ��  � D3DRS_WRAP10  ��  � D3DRS_WRAP11  �j    OLE_CHANGED " �   OLEMISC_RECOMPOSEONRESIZE  C�   DBTYPE_IUNKNOWN   �   SZB_LEFTALIGN  �   @VT_BYREF  �   OLEMISC_ONLYICONIC  �j   OLE_SAVED + �E  �% Gdiplus::WmfRecordTypePolyline  ��  � D3DRS_WRAP12  �  � �VT_RESERVED  C�   DBTYPE_DECIMAL   �   SZB_TOPRIGHTALIGN   �   SZB_TOPLEFTALIGN  C�   DBTYPE_UI1 ! �   OLEMISC_INSERTNOTREPLACE  ��    MCAST_INCLUDE  �  ���VT_ILLEGAL  �j   OLE_CLOSED  ��  � D3DRS_WRAP13  �  �VT_ILLEGALMASKED !  �   SZB_HALFBOTTOMRIGHTALIGN  N�    D3D_INCLUDE_LOCAL  C�    DBTYPE_ARRAY  �   OLEMISC_STATIC ) �E  �& Gdiplus::WmfRecordTypeEscape  ��   MCAST_EXCLUDE  ��  � D3DRS_WRAP14  �j   OLE_RENAMED       ASSOC_FILTER_NONE  ��  � D3DRS_WRAP15  C�   @DBTYPE_BYREF  �  �VT_TYPEMASK !     ASSOC_FILTER_RECOMMENDED  �j   OLE_CHANGED_STATE  �   OLEMISC_CANTLINKINSIDE  (�   NdisRingStateOpened    �   SZB_HALFBOTTOMLEFTALIGN  N�   D3D_INCLUDE_SYSTEM , �E  �' Gdiplus::WmfRecordTypeRestoreDC  �    OLEMISC_CANLINKBYOLE1   �   SZB_HALFTOPRIGHTALIGN ' ��  � D3DRS_SEPARATEALPHABLENDENABLE  N�    D3D10_INCLUDE_LOCAL  �j   OLE_CHANGED_ASPECT  (�   NdisRingStateClosed  C�   DBTYPE_I1  �  @ OLEMISC_ISLINKOBJECT  N�   D3D10_INCLUDE_SYSTEM  C�   DBTYPE_UI2   �   SZB_HALFTOPLEFTALIGN  (�   NdisRingStateOpening  ��  � D3DRS_SRCBLENDALPHA  �  � OLEMISC_INSIDEOUT - �E  �( Gdiplus::WmfRecordTypeFillRegion  ��  � D3DRS_DESTBLENDALPHA  -�    DBCID_EMPTY  C�   DBTYPE_UI4  N�    OT_UNKNOWN $ N�  ����D3D_INCLUDE_FORCE_DWORD  (�   NdisRingStateClosing �   ^   ��   SPNP_UP $ �   OLEMISC_ACTIVATEWHENVISIBLE  N�   OT_LINK  ��  � D3DRS_BLENDOPALPHA  ��    TS_MIN ! (�   NdisRingStateOpenFailure  �    LIM_SMALL  -�   DBCID_ONDRAG  C�   DBTYPE_I8  �   LIM_LARGE  ��   SPNP_DOWN ! (�   NdisRingStateRingFailure . �E  �) Gdiplus::WmfRecordTypeFrameRegion - �   OLEMISC_RENDERINGISDEVICEINDEPENDENT  V�    BMICON_LARGE  ��   TS_TRUE  -�   DBCID_CLSIDOFBAR  C�   DBTYPE_UI8  ��  ����D3DRS_FORCE_DWORD  N�   OT_EMBEDDED  ��   TS_DRAW  ��   SPNP_UPHORZ # �   OLEMISC_INVISIBLEATRUNTIME  V�   BMICON_SMALL  C�  H DBTYPE_GUID  -�   DBCID_RESIZE  N�   OT_STATIC  -�   DBCID_GETBAR  �   OLEMISC_ALWAYSRUN  N�   OT_OLE2 / �E  �* Gdiplus::WmfRecordTypeInvertRegion  C�   DBTYPE_VECTOR  ��   SPNP_DOWNHORZ   �   �   �   OLEMISC_ACTSLIKEBUTTON      D3DMCS_MATERIAL  C�  � �DBTYPE_RESERVED  ��   UPS_NORMAL   ��    NdisMediaStateConnected . �E  �+ Gdiplus::WmfRecordTypePaintRegion  �    OLEMISC_ACTSLIKELABEL     D3DMCS_COLOR1  C�  � DBTYPE_BYTES  ��    CIP_DISK_FULL # ��   NdisMediaStateDisconnected  ��   UPS_HOT  C�  � DBTYPE_STR     D3DMCS_COLOR2  �   @OLEMISC_NOUIACTIVATE  �  � �OLEMISC_ALIGNABLE    ����D3DMCS_FORCE_DWORD  ��   UPS_PRESSED  C�  � DBTYPE_WSTR 3 �E  �, Gdiplus::WmfRecordTypeSelectClipRegion  ��   CIP_ACCESS_DENIED & ��    SharedVirtualDisksUnsupported  ��   UPS_DISABLED ! ��   CIP_NEWER_VERSION_EXISTS  C�  � DBTYPE_NUMERIC   �  �   OLEMISC_SIMPLEFRAME $ ��   SharedVirtualDisksSupported / �E  �- Gdiplus::WmfRecordTypeSelectObject  C�  � DBTYPE_UDT ' �  �   OLEMISC_SETCLIENTSITEFIRST ! ��   CIP_OLDER_VERSION_EXISTS  E�   DNS_NORMAL  ��   CIP_NAME_CONFLICT  î    Ndis802_11PowerModeCAM  �  �   OLEMISC_IMEMODE  C�  � DBTYPE_DBDATE  <�   D3DTSS_COLOROP  <�   D3DTSS_COLORARG1  E�   DNS_HOT  k�    DBRESULTFLAG_DEFAULT # î   Ndis802_11PowerModeMAX_PSP / �E  �. Gdiplus::WmfRecordTypeSetTextAlign  C�  � DBTYPE_DBTIME . �  �   OLEMISC_IGNOREACTIVATEWHENVISIBLE 1 ��   CIP_TRUST_VERIFICATION_COMPONENT_MISSING ) �    SharedVirtualDiskHandleStateNone  C�  � DBTYPE_DBTIMESTAMP / �   SharedVirtualDiskHandleStateFileShared % �  �   OLEMISC_WANTSTOMENUMERGE + ��   CIP_EXE_SELF_REGISTERATION_TIMEOUT $ î   Ndis802_11PowerModeFast_PSP  k�   DBRESULTFLAG_ROWSET  <�   D3DTSS_COLORARG2  E�   DNS_PRESSED # �    D3D10_DRIVER_TYPE_HARDWARE + �E  �/ Gdiplus::WmfRecordTypeDrawText  E�   DNS_DISABLED  ��   CIP_UNSAFE_TO_ABORT  k�   DBRESULTFLAG_ROW  <�   D3DTSS_ALPHAOP 1 �   SharedVirtualDiskHandleStateHandleShared + �  �    OLEMISC_SUPPORTSMULTILEVELUNDO  î   Ndis802_11PowerModeMax  N � DBTYPE_HCHAPTER  <�   D3DTSS_ALPHAARG1 $ �   D3D10_DRIVER_TYPE_REFERENCE  ��   CIP_NEED_REBOOT  <�   D3DTSS_ALPHAARG2 ( �E  �0 Gdiplus::WmfRecordTypeChord , �   ��D3D10_STANDARD_MULTISAMPLE_PATTERN  5�   UPHZS_NORMAL & ��  	 CIP_NEED_REBOOT_UI_PERMISSION  �   D3D10_DRIVER_TYPE_NULL  5�   UPHZS_HOT  <�   D3DTSS_BUMPENVMAT00  8k    OLECLOSE_SAVEIFDIRTY  ��  @ DBTYPE_FILETIME # �   D3D10_DRIVER_TYPE_SOFTWARE  ��    HHACT_TAB_CONTENTS * �   ��D3D10_CENTER_MULTISAMPLE_PATTERN  ��   HHACT_TAB_INDEX  ��  � DBTYPE_PROPVARIANT  8k   OLECLOSE_NOSAVE  <�   D3DTSS_BUMPENVMAT01 1 �E  �1 Gdiplus::WmfRecordTypeSetMapperFlags  �   D3D10_DRIVER_TYPE_WARP  5�   UPHZS_PRESNEMAP_TEXTURES-1].
		g_pEffect->SetTechnique("ResampleAvgLum");
		g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));

		g_pd3dDevice->SetRenderTarget(0, apSurfToneMap[dwCurTexture]);
		g_pd3dDevice->SetTexture(0, g_apTexToneMap[dwCurTexture + 1]);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);


		hr = g_pEffect->Begin(&uiPassCount, 0);
		if (FAILED(hr))
			goto LCleanReturn;

		for (uiPass = 0; uiPass < uiPassCount; uiPass++)
		{
			g_pEffect->BeginPass(uiPass);

			// Draw a fullscreen quad to sample the RT
			DrawFullScreenQuad(0.0f, 0.0f, 1.0f, 1.0f);

			g_pEffect->EndPass();
		}

		g_pEffect->End();
		dwCurTexture--;
	}

	// Downsample to 1x1
	g_apTexToneMap[1]->GetLevelDesc(0, &desc);
	GetSampleOffsets_DownScale4x4(desc.Width, desc.Height, avSampleOffsets);


	// Perform the final pass of the average luminance calculation. This pass
	// scales the 4x4 log of average luminance texture from above and performs
	// an exp() operation to return a single texel cooresponding to the average
	// luminance of the scene in g_apTexToneMap[0].
	g_pEffect->SetTechnique("ResampleAvgLumExp");
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));

	g_pd3dDevice->SetRenderTarget(0, apSurfToneMap[0]);
	g_pd3dDevice->SetTexture(0, g_apTexToneMap[1]);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);


	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(0.0f, 0.0f, 1.0f, 1.0f);

		g_pEffect->EndPass();
	}

	g_pEffect->End();


	hr = S_OK;
LCleanReturn:
	for (i = 0; i < NUM_TONEMAP_TEXTURES; i++)
	{
		SAFE_RELEASE(apSurfToneMap[i]);
	}

	return hr;
}




//-----------------------------------------------------------------------------
// Name: CalculateAdaptation()
// Desc: Increment the user's adapted luminance
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::CalculateAdaptation()
{
	HRESULT hr = S_OK;
	UINT uiPass, uiPassCount;

	// Swap current & last luminance
	PDIRECT3DTEXTURE9 pTexSwap = g_pTexAdaptedLuminanceLast;
	g_pTexAdaptedLuminanceLast = g_pTexAdaptedLuminanceCur;
	g_pTexAdaptedLuminanceCur = pTexSwap;

	PDIRECT3DSURFACE9 pSurfAdaptedLum = NULL;
	V(g_pTexAdaptedLuminanceCur->GetSurfaceLevel(0, &pSurfAdaptedLum));

	// This simulates the light adaptation that occurs when moving from a 
	// dark area to a bright area, or vice versa. The g_pTexAdaptedLuminance
	// texture stores a single texel cooresponding to the user's adapted 
	// level.
	g_pEffect->SetTechnique("CalculateAdaptedLum");
	g_pEffect->SetFloat("g_fElapsedTime", DXUTGetElapsedTime());

	g_pd3dDevice->SetRenderTarget(0, pSurfAdaptedLum);
	g_pd3dDevice->SetTexture(0, g_pTexAdaptedLuminanceLast);
	g_pd3dDevice->SetTexture(1, g_apTexToneMap[0]);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);


	V(g_pEffect->Begin(&uiPassCount, 0));

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(0.0f, 0.0f, 1.0f, 1.0f);

		g_pEffect->EndPass();
	}

	g_pEffect->End();


	SAFE_RELEASE(pSurfAdaptedLum);
	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RenderStar()
// Desc: Render the blooming effect
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::RenderStar()
{
	HRESULT hr = S_OK;
	UINT uiPassCount, uiPass;
	int i, d, p, s; // Loop variables

	LPDIRECT3DSURFACE9 pSurfStar = NULL;
	hr = g_apTexStar[0]->GetSurfaceLevel(0, &pSurfStar);
	if (FAILED(hr))
		return hr;

	// Clear the star texture
	g_pd3dDevice->ColorFill(pSurfStar, NULL, D3DCOLOR_ARGB(0, 0, 0, 0));
	SAFE_RELEASE(pSurfStar);

	// Avoid rendering the star if it's not being used in the current glare
	if (g_GlareDef.m_fGlareLuminance <= 0.0f ||
		g_GlareDef.m_fStarLuminance <= 0.0f)
	{
		return S_OK;
	}

	// Initialize the constants used during the effect
	const CStarDef& starDef = g_GlareDef.m_starDef;
	const float fTanFoV = atanf(D3DX_PI / 8);
	const D3DXVECTOR4 vWhite(1.0f, 1.0f, 1.0f, 1.0f);
	static const int s_maxPasses = 3;
	static const int nSamples = 8;
	static D3DXVECTOR4 s_aaColor[s_maxPasses][8];
	static const D3DXCOLOR s_colorWhite(0.63f, 0.63f, 0.63f, 0.0f);

	D3DXVECTOR4 avSampleWeights[MAX_SAMPLES];
	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];

	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	PDIRECT3DSURFACE9 pSurfSource = NULL;
	PDIRECT3DSURFACE9 pSurfDest = NULL;

	// Set aside all the star texture surfaces as a convenience
	PDIRECT3DSURFACE9 apSurfStar[NUM_STAR_TEXTURES] = { 0 };
	for (i = 0; i < NUM_STAR_TEXTURES; i++)
	{
		hr = g_apTexStar[i]->GetSurfaceLevel(0, &apSurfStar[i]);
		if (FAILED(hr))
			goto LCleanReturn;
	}

	// Get the source texture dimensions
	hr = g_pTexStarSource->GetSurfaceLevel(0, &pSurfSource);
	if (FAILED(hr))
		goto LCleanReturn;

	D3DSURFACE_DESC desc;
	hr = pSurfSource->GetDesc(&desc);
	if (FAILED(hr))
		goto LCleanReturn;

	SAFE_RELEASE(pSurfSource);

	float srcW;
	srcW = (FLOAT)desc.Width;
	float srcH;
	srcH = (FLOAT)desc.Height;



	for (p = 0; p < s_maxPasses; p++)
	{
		float ratio;
		ratio = (float)(p + 1) / (float)s_maxPasses;

		for (s = 0; s < nSamples; s++)
		{
			D3DXCOLOR chromaticAberrColor;
			D3DXColorLerp(&chromaticAberrColor,
				&(CStarDef::GetChromaticAberrationColor(s)),
				&s_colorWhite,
				ratio);

			D3DXColorLerp((D3DXCOLOR*)&(s_aaColor[p][s]),
				&s_colorWhite, &chromaticAberrColor,
				g_GlareDef.m_fChromaticAberration);
		}
	}

	float radOffset;
	radOffset = g_GlareDef.m_fStarInclination + starDef.m_fInclination;


	PDIRECT3DTEXTURE9 pTexSource;


	// Direction loop
	for (d = 0; d < starDef.m_nStarLines; d++)
	{
		CONST STARLINE& starLine = starDef.m_pStarLine[d];

		pTexSource = g_pTexStarSource;

		float rad;
		rad = radOffset + starLine.fInclination;
		float sn, cs;
		sn = sinf(rad), cs = cosf(rad);
		D3DXVECTOR2 vtStepUV;
		vtStepUV.x = sn / srcW * starLine.fSampleLength;
		vtStepUV.y = cs / srcH * starLine.fSampleLength;

		float attnPowScale;
		attnPowScale = (fTanFoV + 0.1f) * 1.0f *
			(160.0f + 120.0f) / (srcW + srcH) * 1.2f;

		// 1 direction expansion loop
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		int iWorkTexture;
		iWorkTexture = 1;
		for (p = 0; p < starLine.nPasses; p++)
		{

			if (p == starLine.nPasses - 1)
			{
				// Last pass move to other work buffer
				pSurfDest = apSurfStar[d + 4];
			}
			else
			{
				pSurfDest = apSurfStar[iWorkTexture];
			}

			// Sampling configration for each stage
			for (i = 0; i < nSamples; i++)
			{
				float lum;
				lum = powf(starLine.fAttenuation, attnPowScale * i);

				avSampleWeights[i] = s_aaColor[starLine.nPasses - 1 - p][i] *
					lum * (p + 1.0f) * 0.5f;


				// Offset of sampling coordinate
				avSampleOffsets[i].x = vtStepUV.x * i;
				avSampleOffsets[i].y = vtStepUV.y * i;
				if (fabs(avSampleOffsets[i].x) >= 0.9f ||
					fabs(avSampleOffsets[i].y) >= 0.9f)
				{
					avSampleOffsets[i].x = 0.0f;
					avSampleOffsets[i].y = 0.0f;
					avSampleWeights[i] *= 0.0f;
				}

			}


			g_pEffect->SetTechnique("Star");
			g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
			g_pEffect->SetVectorArray("g_avSampleWeights", avSampleWeights, nSamples);

			g_pd3dDevice->SetRenderTarget(0, pSurfDest);
			g_pd3dDevice->SetTexture(0, pTexSource);
			g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);


			hr = g_pEffect->Begin(&uiPassCount, 0);
			if (FAILED(hr))
				return hr;

			for (uiPass = 0; uiPass < uiPassCount; uiPass++)
			{
				g_pEffect->BeginPass(uiPass);

				// Draw a fullscreen quad to sample the RT
				DrawFullScreenQuad(0.0f, 0.0f, 1.0f, 1.0f);

				g_pEffect->EndPass();
			}

			g_pEffect->End();

			// Setup next expansion
			vtStepUV *= nSamples;
			attnPowScale *= nSamples;

			// Set the work drawn just before to next texture source.
			pTexSource = g_apTexStar[iWorkTexture];

			iWorkTexture += 1;
			if (iWorkTexture > 2)
			{
				iWorkTexture = 1;
			}

		}
	}


	pSurfDest = apSurfStar[0];


	for (i = 0; i < starDef.m_nStarLines; i++)
	{
		g_pd3dDevice->SetTexture(i, g_apTexStar[i + 4]);
		g_pd3dDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pd3dDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		avSampleWeights[i] = vWhite * 1.0f / (FLOAT)starDef.m_nStarLines;
	}

	CHAR strTechnique[256];
	sprintf_s(strTechnique, 256, "MergeTextures_%d", starDef.m_nStarLines);

	g_pEffect->SetTechnique(strTechnique);

	g_pEffect->SetVectorArray("g_avSampleWeights", avSampleWeights, starDef.m_nStarLines);

	g_pd3dDevice->SetRenderTarget(0, pSurfDest);

	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(0.0f, 0.0f, 1.0f, 1.0f);

		g_pEffect->EndPass();
	}

	g_pEffect->End();

	for (i = 0; i < starDef.m_nStarLines; i++)
		g_pd3dDevice->SetTexture(i, NULL);


	hr = S_OK;
LCleanReturn:
	for (i = 0; i < NUM_STAR_TEXTURES; i++)
	{
		SAFE_RELEASE(apSurfStar[i]);
	}

	return hr;
}




//-----------------------------------------------------------------------------
// Name: RenderBloom()
// Desc: Render the blooming effect
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::RenderBloom()
{
	HRESULT hr = S_OK;
	UINT uiPassCount, uiPass;
	int i = 0;


	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];
	FLOAT afSampleOffsets[MAX_SAMPLES];
	D3DXVECTOR4 avSampleWeights[MAX_SAMPLES];

	PDIRECT3DSURFACE9 pSurfScaledHDR;
	g_pTexSceneScaled->GetSurfaceLevel(0, &pSurfScaledHDR);

	PDIRECT3DSURFACE9 pSurfBloom;
	g_apTexBloom[0]->GetSurfaceLevel(0, &pSurfBloom);

	PDIRECT3DSURFACE9 pSurfHDR;
	g_pTexScene->GetSurfaceLevel(0, &pSurfHDR);

	PDIRECT3DSURFACE9 pSurfTempBloom;
	g_apTexBloom[1]->GetSurfaceLevel(0, &pSurfTempBloom);

	PDIRECT3DSURFACE9 pSurfBloomSource;
	g_apTexBloom[2]->GetSurfaceLevel(0, &pSurfBloomSource);

	// Clear the bloom texture
	g_pd3dDevice->ColorFill(pSurfBloom, NULL, D3DCOLOR_ARGB(0, 0, 0, 0));

	if (g_GlareDef.m_fGlareLuminance <= 0.0f ||
		g_GlareDef.m_fBloomLuminance <= 0.0f)
	{
		hr = S_OK;
		goto LCleanReturn;
	}

	RECT rectSrc;
	GetTextureRect(g_pTexBloomSource, &rectSrc);
	InflateRect(&rectSrc, -1, -1);

	RECT rectDest;
	GetTextureRect(g_apTexBloom[2], &rectDest);
	InflateRect(&rectDest, -1, -1);

	CoordRect coords;
	GetTextureCoords(g_pTexBloomSource, &rectSrc, g_apTexBloom[2], &rectDest, &coords);

	D3DSURFACE_DESC desc;
	hr = g_pTexBloomSource->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;


	g_pEffect->SetTechnique("GaussBlur5x5");

	hr = GetSampleOffsets_GaussBlur5x5(desc.Width, desc.Height, avSampleOffsets, avSampleWeights, 1.0f);

	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
	g_pEffect->SetValue("g_avSampleWeights", avSampleWeights, sizeof(avSampleWeights));

	g_pd3dDevice->SetRenderTarget(0, pSurfBloomSource);
	g_pd3dDevice->SetTexture(0, g_pTexBloomSource);
	g_pd3dDevice->SetScissorRect(&rectDest);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);


	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}
	g_pEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	hr = g_apTexBloom[2]->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;

	hr = GetSampleOffsets_Bloom(desc.Width, afSampleOffsets, avSampleWeights, 3.0f, 2.0f);
	for (i = 0; i < MAX_SAMPLES; i++)
	{
		avSampleOffsets[i] = D3DXVECTOR2(afSampleOffsets[i], 0.0f);
	}


	g_pEffect->SetTechnique("Bloom");
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
	g_pEffect->SetValue("g_avSampleWeights", avSampleWeights, sizeof(avSampleWeights));

	g_pd3dDevice->SetRenderTarget(0, pSurfTempBloom);
	g_pd3dDevice->SetTexture(0, g_apTexBloom[2]);
	g_pd3dDevice->SetScissorRect(&rectDest);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);


	g_pEffect->Begin(&uiPassCount, 0);
	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}
	g_pEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);


	hr = g_apTexBloom[1]->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;

	hr = GetSampleOffsets_Bloom(desc.Height, afSampleOffsets, avSampleWeights, 3.0f, 2.0f);
	for (i = 0; i < MAX_SAMPLES; i++)
	{
		avSampleOffsets[i] = D3DXVECTOR2(0.0f, afSampleOffsets[i]);
	}


	GetTextureRect(g_apTexBloom[1], &rectSrc);
	InflateRect(&rectSrc, -1, -1);

	GetTextureCoords(g_apTexBloom[1], &rectSrc, g_apTexBloom[0], NULL, &coords);


	g_pEffect->SetTechnique("Bloom");
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
	g_pEffect->SetValue("g_avSampleWeights", avSampleWeights, sizeof(avSampleWeights));

	g_pd3dDevice->SetRenderTarget(0, pSurfBloom);
	g_pd3dDevice->SetTexture(0, g_apTexBloom[1]);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);


	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}

	g_pEffect->End();


	hr = S_OK;

LCleanReturn:
	SAFE_RELEASE(pSurfBloomSource);
	SAFE_RELEASE(pSurfTempBloom);
	SAFE_RELEASE(pSurfBloom);
	SAFE_RELEASE(pSurfHDR);
	SAFE_RELEASE(pSurfScaledHDR);

	return hr;
}



//-----------------------------------------------------------------------------
// Name: DrawFullScreenQuad
// Desc: Draw a properly aligned quad covering the entire render target
//-----------------------------------------------------------------------------
void LunaHDRLighting::DrawFullScreenQuad(float fLeftU, float fTopV, float fRightU, float fBottomV)
{
	D3DSURFACE_DESC dtdsdRT;
	PDIRECT3DSURFACE9 pSurfRT;

	// Acquire render target width and height
	g_pd3dDevice->GetRenderTarget(0, &pSurfRT);
	pSurfRT->GetDesc(&dtdsdRT);
	pSurfRT->Release();

	// Ensure that we're directly mapping texels to pixels by offset by 0.5
	// For more info see the doc page titled "Directly Mapping Texels to Pixels"
	FLOAT fWidth5 = (FLOAT)dtdsdRT.Width - 0.5f;
	FLOAT fHeight5 = (FLOAT)dtdsdRT.Height - 0.5f;

	// Draw the quad
	ScreenVertex svQuad[4];

	svQuad[0].p = D3DXVECTOR4(-0.5f, -0.5f, 0.5f, 1.0f);
	svQuad[0].t = D3DXVECTOR2(fLeftU, fTopV);

	svQuad[1].p = D3DXVECTOR4(fWidth5, -0.5f, 0.5f, 1.0f);
	svQuad[1].t = D3DXVECTOR2(fRightU, fTopV);

	svQuad[2].p = D3DXVECTOR4(-0.5f, fHeight5, 0.5f, 1.0f);
	svQuad[2].t = D3DXVECTOR2(fLeftU, fBottomV);

	svQuad[3].p = D3DXVECTOR4(fWidth5, fHeight5, 0.5f, 1.0f);
	svQuad[3].t = D3DXVECTOR2(fRightU, fBottomV);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pd3dDevice->SetFVF(ScreenVertex::FVF);
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, svQuad, sizeof(ScreenVertex));
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}


//-----------------------------------------------------------------------------
// Name: GetTextureRect()
// Desc: Get the dimensions of the texture
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetTextureRect(PDIRECT3DTEXTURE9 pTexture, RECT* pRect)
{
	HRESULT hr = S_OK;

	if (pTexture == NULL || pRect == NULL)
		return E_INVALIDARG;

	D3DSURFACE_DESC desc;
	hr = pTexture->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;

	pRect->left = 0;
	pRect->top = 0;
	pRect->right = desc.Width;
	pRect->bottom = desc.Height;

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetTextureCoords()
// Desc: Get the texture coordinates to use when rendering into the destination
//       texture, given the source and destination rectangles
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetTextureCoords(PDIRECT3DTEXTURE9 pTexSrc, RECT* pRectSrc, PDIRECT3DTEXTURE9 pTexDest, RECT* pRectDest, CoordRect* pCoords)
{
	HRESULT hr = S_OK;
	D3DSURFACE_DESC desc;
	float tU, tV;

	// Validate arguments
	if (pTexSrc == NULL || pTexDest == NULL || pCoords == NULL)
		return E_INVALIDARG;

	// Start with a default mapping of the complete source surface to complete 
	// destination surface
	pCoords->fLeftU = 0.0f;
	pCoords->fTopV = 0.0f;
	pCoords->fRightU = 1.0f;
	pCoords->fBottomV = 1.0f;

	// If not using the complete source surface, adjust the coordinates
	if (pRectSrc != NULL)
	{
		// Get destination texture description
		hr = pTexSrc->GetLevelDesc(0, &desc);
		if (FAILED(hr))
			return hr;

		// These delta values are the distance between source texel centers in 
		// texture address space
		tU = 1.0f / desc.Width;
		tV = 1.0f / desc.Height;

		pCoords->fLeftU += pRectSrc->left * tU;
		pCoords->fTopV += pRectSrc->top * tV;
		pCoords->fRightU -= (desc.Width - pRectSrc->right) * tU;
		pCoords->fBottomV -= (desc.Height - pRectSrc->bottom) * tV;
	}

	// If not drawing to the complete destination surface, adjust the coordinates
	if (pRectDest != NULL)
	{
		// Get source texture description
		hr = pTexDest->GetLevelDesc(0, &desc);
		if (FAILED(hr))
			return hr;

		// These delta values are the distance between source texel centers in 
		// texture address space
		tU = 1.0f / desc.Width;
		tV = 1.0f / desc.Height;

		pCoords->fLeftU -= pRectDest->left * tU;
		pCoords->fTopV -= pRectDest->top * tV;
		pCoords->fRightU += (desc.Width - pRectDest->right) * tU;
		pCoords->fBottomV += (desc.Height - pRectDest->bottom) * tV;
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Scene_To_SceneScaled()
// Desc: Scale down g_pTexScene by 1/4 x 1/4 and place the result in 
//       g_pTexSceneScaled
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::Scene_To_SceneScaled()
{
	HRESULT hr = S_OK;
	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];


	// Get the new render target surface
	PDIRECT3DSURFACE9 pSurfScaledScene = NULL;
	hr = g_pTexSceneScaled->GetSurfaceLevel(0, &pSurfScaledScene);
	if (FAILED(hr))
		goto LCleanReturn;

	const D3DSURFACE_DESC* pBackBufferDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	// Create a 1/4 x 1/4 scale copy of the HDR texture. Since bloom textures
	// are 1/8 x 1/8 scale, border texels of the HDR texture will be discarded 
	// to keep the dimensions evenly divisible by 8; this allows for precise 
	// control over sampling inside pixel shaders.
	g_pEffect->SetTechnique("DownScale4x4");

	// Place the rectangle in the center of the back buffer surface
	RECT rectSrc;
	rectSrc.left = (pBackBufferDesc->Width - g_dwCropWidth) / 2;
	rectSrc.top = (pBackBufferDesc->Height - g_dwCropHeight) / 2;
	rectSrc.right = rectSrc.left + g_dwCropWidth;
	rectSrc.bottom = rectSrc.top + g_dwCropHeight;

	// Get the texture coordinates for the render target
	CoordRect coords;
	GetTextureCoords(g_pTexScene, &rectSrc, g_pTexSceneScaled, NULL, &coords);

	// Get the sample offsets used within the pixel shader
	GetSampleOffsets_DownScale4x4(pBackBufferDesc->Width, pBackBufferDesc->Height, avSampleOffsets);
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));

	g_pd3dDevice->SetRenderTarget(0, pSurfScaledScene);
	g_pd3dDevice->SetTexture(0, g_pTexScene);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	UINT uiPassCount, uiPass;
	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}

	g_pEffect->End();


	hr = S_OK;
LCleanReturn:
	SAFE_RELEASE(pSurfScaledScene);
	return hr;
}




//-----------------------------------------------------------------------------
// Name: SceneScaled_To_BrightPass
// Desc: Run the bright-pass filter on g_pTexSceneScaled and place the result
//       in g_pTexBrightPass
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::SceneScaled_To_BrightPass()
{
	HRESULT hr = S_OK;

	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];
	D3DXVECTOR4 avSampleWeights[MAX_SAMPLES];


	// Get the new render target surface
	PDIRECT3DSURFACE9 pSurfBrightPass;
	hr = g_pTexBrightPass->GetSurfaceLevel(0, &pSurfBrightPass);
	if (FAILED(hr))
		goto LCleanReturn;


	D3DSURFACE_DESC desc;
	g_pTexSceneScaled->GetLevelDesc(0, &desc);

	// Get the rectangle describing the sampled portion of the source texture.
	// Decrease the rectangle to adjust for the single pixel black border.
	RECT rectSrc;
	GetTextureRect(g_pTexSceneScaled, &rectSrc);
	InflateRect(&rectSrc, -1, -1);

	// Get the destination rectangle.
	// Decrease the rectangle to adjust for the single pixel black border.
	RECT rectDest;
	GetTextureRect(g_pTexBrightPass, &rectDest);
	InflateRect(&rectDest, -1, -1);

	// Get the correct texture coordinates to apply to the rendered quad in order 
	// to sample from the source rectangle and render into the destination rectangle
	CoordRect coords;
	GetTextureCoords(g_pTexSceneScaled, &rectSrc, g_pTexBrightPass, &rectDest, &coords);

	// The bright-pass filter removes everything from the scene except lights and
	// bright reflections
	g_pEffect->SetTechnique("BrightPassFilter");

	g_pd3dDevice->SetRenderTarget(0, pSurfBrightPass);
	g_pd3dDevice->SetTexture(0, g_pTexSceneScaled);
	g_pd3dDevice->SetTexture(1, g_pTexAdaptedLuminanceCur);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetScissorRect(&rectDest);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	UINT uiPass, uiPassCount;
	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad to sample the RT
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}

	g_pEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	hr = S_OK;
LCleanReturn:
	SAFE_RELEASE(pSurfBrightPass);
	return hr;
}




//-----------------------------------------------------------------------------
// Name: BrightPass_To_StarSource
// Desc: Perform a 5x5 gaussian blur on g_pTexBrightPass and place the result
//       in g_pTexStarSource. The bright-pass filtered image is blurred before
//       being used for star operations to avoid aliasing artifacts.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::BrightPass_To_StarSource()
{
	HRESULT hr = S_OK;

	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];
	D3DXVECTOR4 avSampleWeights[MAX_SAMPLES];

	// Get the new render target surface
	PDIRECT3DSURFACE9 pSurfStarSource;
	hr = g_pTexStarSource->GetSurfaceLevel(0, &pSurfStarSource);
	if (FAILED(hr))
		goto LCleanReturn;


	// Get the destination rectangle.
	// Decrease the rectangle to adjust for the single pixel black border.
	RECT rectDest;
	GetTextureRect(g_pTexStarSource, &rectDest);
	InflateRect(&rectDest, -1, -1);

	// Get the correct texture coordinates to apply to the rendered quad in order 
	// to sample from the source rectangle and render into the destination rectangle
	CoordRect coords;
	GetTextureCoords(g_pTexBrightPass, NULL, g_pTexStarSource, &rectDest, &coords);

	// Get the sample offsets used within the pixel shader
	D3DSURFACE_DESC desc;
	hr = g_pTexBrightPass->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;


	GetSampleOffsets_GaussBlur5x5(desc.Width, desc.Height, avSampleOffsets, avSampleWeights);
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
	g_pEffect->SetValue("g_avSampleWeights", avSampleWeights, sizeof(avSampleWeights));

	// The gaussian blur smooths out rough edges to avoid aliasing effects
	// when the star effect is run
	g_pEffect->SetTechnique("GaussBlur5x5");

	g_pd3dDevice->SetRenderTarget(0, pSurfStarSource);
	g_pd3dDevice->SetTexture(0, g_pTexBrightPass);
	g_pd3dDevice->SetScissorRect(&rectDest);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	UINT uiPassCount, uiPass;
	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}

	g_pEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);


	hr = S_OK;
LCleanReturn:
	SAFE_RELEASE(pSurfStarSource);
	return hr;
}




//-----------------------------------------------------------------------------
// Name: StarSource_To_BloomSource
// Desc: Scale down g_pTexStarSource by 1/2 x 1/2 and place the result in 
//       g_pTexBloomSource
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::StarSource_To_BloomSource()
{
	HRESULT hr = S_OK;

	D3DXVECTOR2 avSampleOffsets[MAX_SAMPLES];

	// Get the new render target surface
	PDIRECT3DSURFACE9 pSurfBloomSource;
	hr = g_pTexBloomSource->GetSurfaceLevel(0, &pSurfBloomSource);
	if (FAILED(hr))
		goto LCleanReturn;


	// Get the rectangle describing the sampled portion of the source texture.
	// Decrease the rectangle to adjust for the single pixel black border.
	RECT rectSrc;
	GetTextureRect(g_pTexStarSource, &rectSrc);
	InflateRect(&rectSrc, -1, -1);

	// Get the destination rectangle.
	// Decrease the rectangle to adjust for the single pixel black border.
	RECT rectDest;
	GetTextureRect(g_pTexBloomSource, &rectDest);
	InflateRect(&rectDest, -1, -1);

	// Get the correct texture coordinates to apply to the rendered quad in order 
	// to sample from the source rectangle and render into the destination rectangle
	CoordRect coords;
	GetTextureCoords(g_pTexStarSource, &rectSrc, g_pTexBloomSource, &rectDest, &coords);

	// Get the sample offsets used within the pixel shader
	D3DSURFACE_DESC desc;
	hr = g_pTexBrightPass->GetLevelDesc(0, &desc);
	if (FAILED(hr))
		return hr;

	GetSampleOffsets_DownScale2x2(desc.Width, desc.Height, avSampleOffsets);
	g_pEffect->SetValue("g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));

	// Create an exact 1/2 x 1/2 copy of the source texture
	g_pEffect->SetTechnique("DownScale2x2");

	g_pd3dDevice->SetRenderTarget(0, pSurfBloomSource);
	g_pd3dDevice->SetTexture(0, g_pTexStarSource);
	g_pd3dDevice->SetScissorRect(&rectDest);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	UINT uiPassCount, uiPass;
	hr = g_pEffect->Begin(&uiPassCount, 0);
	if (FAILED(hr))
		goto LCleanReturn;

	for (uiPass = 0; uiPass < uiPassCount; uiPass++)
	{
		g_pEffect->BeginPass(uiPass);

		// Draw a fullscreen quad
		DrawFullScreenQuad(coords);

		g_pEffect->EndPass();
	}

	g_pEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);



	hr = S_OK;
LCleanReturn:
	SAFE_RELEASE(pSurfBloomSource);
	return hr;
}




//-----------------------------------------------------------------------------
// Name: GetSampleOffsets_DownScale4x4
// Desc: Get the texture coordinate offsets to be used inside the DownScale4x4
//       pixel shader.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetSampleOffsets_DownScale4x4(DWORD dwWidth, DWORD dwHeight, D3DXVECTOR2 avSampleOffsets[])
{
	if (NULL == avSampleOffsets)
		return E_INVALIDARG;

	float tU = 1.0f / dwWidth;
	float tV = 1.0f / dwHeight;

	// Sample from the 16 surrounding points. Since the center point will be in
	// the exact center of 16 texels, a 0.5f offset is needed to specify a texel
	// center.
	int index = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			avSampleOffsets[index].x = (x - 1.5f) * tU;
			avSampleOffsets[index].y = (y - 1.5f) * tV;

			index++;
		}
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetSampleOffsets_DownScale2x2
// Desc: Get the texture coordinate offsets to be used inside the DownScale2x2
//       pixel shader.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetSampleOffsets_DownScale2x2(DWORD dwWidth, DWORD dwHeight, D3DXVECTOR2 avSampleOffsets[])
{
	if (NULL == avSampleOffsets)
		return E_INVALIDARG;

	float tU = 1.0f / dwWidth;
	float tV = 1.0f / dwHeight;

	// Sample from the 4 surrounding points. Since the center point will be in
	// the exact center of 4 texels, a 0.5f offset is needed to specify a texel
	// center.
	int index = 0;
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			avSampleOffsets[index].x = (x - 0.5f) * tU;
			avSampleOffsets[index].y = (y - 0.5f) * tV;

			index++;
		}
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetSampleOffsets_GaussBlur5x5
// Desc: Get the texture coordinate offsets to be used inside the GaussBlur5x5
//       pixel shader.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetSampleOffsets_GaussBlur5x5(DWORD dwD3DTexWidth,	DWORD dwD3DTexHeight, D3DXVECTOR2* avTexCoordOffset, D3DXVECTOR4* avSampleWeight, FLOAT fMultiplier)
{
	float tu = 1.0f / (float)dwD3DTexWidth;
	float tv = 1.0f / (float)dwD3DTexHeight;

	D3DXVECTOR4 vWhite(1.0f, 1.0f, 1.0f, 1.0f);

	float totalWeight = 0.0f;
	int index = 0;
	for (int x = -2; x <= 2; x++)
	{
		for (int y = -2; y <= 2; y++)
		{
			// Exclude pixels with a block distance greater than 2. This will
			// create a kernel which approximates a 5x5 kernel using only 13
			// sample points instead of 25; this is necessary since 2.0 shaders
			// only support 16 texture grabs.
			if (abs(x) + abs(y) > 2)
				continue;

			// Get the unscaled Gaussian intensity for this offset
			avTexCoordOffset[index] = D3DXVECTOR2(x * tu, y * tv);
			avSampleWeight[index] = vWhite * GaussianDistribution((float)x, (float)y, 1.0f);
			totalWeight += avSampleWeight[index].x;

			index++;
		}
	}

	// Divide the current weight by the total weight of all the samples; Gaussian
	// blur kernels add to 1.0f to ensure that the intensity of the image isn't
	// changed when the blur occurs. An optional multiplier variable is used to
	// add or remove image intensity during the blur.
	for (int i = 0; i < index; i++)
	{
		avSampleWeight[i] /= totalWeight;
		avSampleWeight[i] *= fMultiplier;
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetSampleOffsets_Bloom
// Desc: Get the texture coordinate offsets to be used inside the Bloom
//       pixel shader.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetSampleOffsets_Bloom(DWORD dwD3DTexSize,	float afTexCoordOffset[15],	D3DXVECTOR4* avColorWeight,	float fDeviation, float fMultiplier)
{
	int i = 0;
	float tu = 1.0f / (float)dwD3DTexSize;

	// Fill the center texel
	float weight = fMultiplier * GaussianDistribution(0, 0, fDeviation);
	avColorWeight[0] = D3DXVECTOR4(weight, weight, weight, 1.0f);

	afTexCoordOffset[0] = 0.0f;

	// Fill the first half
	for (i = 1; i < 8; i++)
	{
		// Get the Gaussian intensity for this offset
		weight = fMultiplier * GaussianDistribution((float)i, 0, fDeviation);
		afTexCoordOffset[i] = i * tu;

		avColorWeight[i] = D3DXVECTOR4(weight, weight, weight, 1.0f);
	}

	// Mirror to the second half
	for (i = 8; i < 15; i++)
	{
		avColorWeight[i] = avColorWeight[i - 7];
		afTexCoordOffset[i] = -afTexCoordOffset[i - 7];
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetSampleOffsets_Bloom
// Desc: Get the texture coordinate offsets to be used inside the Bloom
//       pixel shader.
//-----------------------------------------------------------------------------
HRESULT LunaHDRLighting::GetSampleOffsets_Star(DWORD dwD3DTexSize,	float afTexCoordOffset[15],	D3DXVECTOR4* avColorWeight,	float fDeviation)
{
	int i = 0;
	float tu = 1.0f / (float)dwD3DTexSize;

	// Fill the center texel
	float weight = 1.0f * GaussianDistribution(0, 0, fDeviation);
	avColorWeight[0] = D3DXVECTOR4(weight, weight, weight, 1.0f);

	afTexCoordOffset[0] = 0.0f;

	// Fill the first half
	for (i = 1; i < 8; i++)
	{
		// Get the Gaussian intensity for this offset
		weight = 1.0f * GaussianDistribution((float)i, 0, fDeviation);
		afTexCoordOffset[i] = i * tu;

		avColorWeight[i] = D3DXVECTOR4(weight, weight, weight, 1.0f);
	}

	// Mirror to the second half
	for (i = 8; i < 15; i++)
	{
		avColorWeight[i] = avColorWeight[i - 7];
		afTexCoordOffset[i] = -afTexCoordOffset[i - 7];
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GaussianDistribution
// Desc: Helper function for GetSampleOffsets function to compute the 
//       2 parameter Gaussian distrubution using the given standard deviation
//       rho
//-----------------------------------------------------------------------------
float LunaHDRLighting::GaussianDistribution(float x, float y, float rho)
{
	float g = 1.0f / sqrtf(2.0f * D3DX_PI * rho * rho);
	g *= expf(-(x * x + y * y) / (2 * rho * rho));

	return g;
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
void LunaHDRLighting::RenderText()
{
	// The helper object simply helps keep track of text position, and color
	// and then it calls pFont->DrawText( g_pSprite, strMsg, -1, &rc, DT_NOCLIP, g_clr );
	// If NULL is passed in as the sprite object, then it will work however the 
	// pFont->DrawText() will not be batched together.  Batching calls will improves performance.
	CDXUTTextHelper txtHelper(g_pFont, g_pTextSprite, 15);

	// Output statistics
	txtHelper.Begin();
	txtHelper.SetInsertionPos(5, 5);
	txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	txtHelper.DrawTextLine(DXUTGetFrameStats(DXUTIsVsyncEnabled()));
	txtHelper.DrawTextLine(DXUTGetDeviceStats());

	txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	WCHAR glareType[255];
	swprintf_s(glareType, L"Glare type: %s", g_GlareDef.m_strGlareName);
	txtHelper.DrawTextLine(glareType);

	if (g_bUseMultiSampleFloat16)
	{
		txtHelper.DrawTextLine(L"Using MultiSample Render Target");
		txtHelper.DrawFormattedTextLine(L"Number of Samples: %d", (int)g_MaxMultiSampleType);
		txtHelper.DrawFormattedTextLine(L"Quality: %d", g_dwMultiSampleQuality);
	}

	// Draw help
	if (g_bShowHelp)
	{
		const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetD3D9BackBufferSurfaceDesc();
		txtHelper.SetInsertionPos(10, pd3dsdBackBuffer->Height - 15 * 6);
		txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 0.75f, 0.0f, 1.0f));
		txtHelper.DrawTextLine(L"Controls (F1 to hide):");

		txtHelper.SetInsertionPos(40, pd3dsdBackBuffer->Height - 15 * 5);
		txtHelper.DrawTextLine(L"Look: Left drag mouse\n"
			L"Move: A,W,S,D or Arrow Keys\n"
			L"Quit: ESC");
	}
	else
	{
		txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		txtHelper.DrawTextLine(L"Press F1 for help");
	}
	txtHelper.End();
}






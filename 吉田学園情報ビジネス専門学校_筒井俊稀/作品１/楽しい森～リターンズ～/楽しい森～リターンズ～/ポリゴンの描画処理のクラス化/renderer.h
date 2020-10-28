//=============================================================================
//
// �����_���[���� [renderer.h]
// Author : 
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include<Windows.h>
#include"d3dx9.h"

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
//-----------------------------------------------------------------------------
//�����_�����O�N���X
//-----------------------------------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexturePolygon; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_PosPolygon;
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
	
};

#endif
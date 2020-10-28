//------------------------------------------
//
//	�w�i�̏���[bullet.h]
//	����
//
//------------------------------------------
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

class CPolygon;
class CRanking;
//------------------------------------------
//	�w�i�̃N���X
//------------------------------------------
class CGameover : public CScene
{
public:
	CGameover();
	~CGameover();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CGameover *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif // !_BG_H_#pragma once#pragma once

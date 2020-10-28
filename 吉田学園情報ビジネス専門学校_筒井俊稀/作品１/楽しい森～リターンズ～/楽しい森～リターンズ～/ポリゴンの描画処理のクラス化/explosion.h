#pragma once
//=============================================================================
//
// �e�̔����̏��� [explosion.cpp]
// Author : �g�V�L
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C��k���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	�e�̔����̃N���X
//-----------------------------------------------------------------------------
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = 9);
	~CExplosion();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCounterAnim;//�J�E���^�[
	int m_nPatternAnim;//�p�^�[��No
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
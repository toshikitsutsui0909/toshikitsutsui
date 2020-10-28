#pragma once
//=============================================================================
//
// 弾の爆発の処理 [explosion.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インkルードファイル
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	弾の爆発のクラス
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
	int m_nCounterAnim;//カウンター
	int m_nPatternAnim;//パターンNo
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
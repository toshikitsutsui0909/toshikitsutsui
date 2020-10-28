#pragma once
//------------------------------------------
//
//	クラスポリゴン描画[player.h]
//	筒井
//
//------------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2d.h"

//-----------------------------------------------------------------------------
//	クラス
//-----------------------------------------------------------------------------
class CPlayer : public CScene2d
{
public:
	CPlayer(int nPriority = 7);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	void SetPlayer(bool bPlaying);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nChageCount;
	int m_Count;
	int m_nCntBullet;
	bool m_bPlaying;
	bool m_bIsDamage;
	int m_nLife;
	int m_nCountLife;
};

#endif

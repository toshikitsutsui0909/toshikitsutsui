#pragma once
//------------------------------------------
//
//	クラスポリゴン描画[player.h]
//	筒井
//
//------------------------------------------

#ifndef _GAUGEBER_H_
#define _GAUGEBER_H_

#include "scene2d.h"

//-----------------------------------------------------------------------------
//	クラス
//-----------------------------------------------------------------------------
class CGaugeber : public CScene2d
{
public:
	CGaugeber(int nPriority = 13);
	~CGaugeber();

	static CGaugeber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif

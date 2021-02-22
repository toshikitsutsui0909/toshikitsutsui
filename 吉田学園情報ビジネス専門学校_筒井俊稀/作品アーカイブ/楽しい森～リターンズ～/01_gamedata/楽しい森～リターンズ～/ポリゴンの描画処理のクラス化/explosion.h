//=============================================================================
//
// 弾の爆発の処理 [explosion.cpp]
// Author : 筒井
//
//=============================================================================

//二重インクルード防止
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

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
	//メンバ関数宣言
	CExplosion(int nPriority = OBJTYPE_EXPLOSION);
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
	D3DXVECTOR3 m_pos;//座標
	D3DXVECTOR3 m_size;//大きさ
};

#endif // !_EXPLOSION_H_
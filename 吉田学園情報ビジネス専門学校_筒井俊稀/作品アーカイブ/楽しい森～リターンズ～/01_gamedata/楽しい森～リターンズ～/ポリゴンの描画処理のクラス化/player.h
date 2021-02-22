#pragma once
//------------------------------------------
//
//	クラスポリゴン描画[player.h]
//	筒井
//
//------------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	クラス
//-----------------------------------------------------------------------------
class CPlayer : public CScene2d
{
public:
	//メンバ関数宣言
	CPlayer(int nPriority = OBJTYPE_PLAYER);
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
	//メンバ変数宣言
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	D3DXVECTOR3 m_pos;//座標
	D3DXVECTOR3 m_size;//大きさ
	int m_nChageCount;//チャージカウント
	int m_Count;//
	int m_nCntBullet;//バレットの撃つ間隔
	bool m_bPlaying;//プレイヤーを使っているか
	bool m_bIsDamage;//ダメージを食らったか
	int m_nLife;//プレイヤー体力
	int m_nCountLife;//残機
};

#endif

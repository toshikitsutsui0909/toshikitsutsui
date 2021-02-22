//------------------------------------------
//
//	クラスポリゴン描画[player.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _GAUGEBER_H_
#define _GAUGEBER_H_

//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	クラス
//-----------------------------------------------------------------------------
class CGaugeber : public CScene2d
{
public:
	//メンバ関数宣言
	CGaugeber(int nPriority = OBJTYPE_GAUGEBER);
	~CGaugeber();

	static CGaugeber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	//メンバ変数宣言
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	D3DXVECTOR3 m_pos;//座標
	D3DXVECTOR3 m_size;//大きさ
};

#endif

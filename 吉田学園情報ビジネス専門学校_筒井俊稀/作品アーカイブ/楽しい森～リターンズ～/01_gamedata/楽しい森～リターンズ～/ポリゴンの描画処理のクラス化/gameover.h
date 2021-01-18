//------------------------------------------
//
//	背景の処理[bullet.h]
//	筒井
//
//------------------------------------------
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CPolygon;
class CRanking;
//------------------------------------------
//	背景のクラス
//------------------------------------------
class CGameover : public CScene
{
public:
	//メンバ関数宣言
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
	//メンバ変数宣言
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;//座標
	D3DXVECTOR3 m_size;//大きさ
};

#endif // !_BG_H_

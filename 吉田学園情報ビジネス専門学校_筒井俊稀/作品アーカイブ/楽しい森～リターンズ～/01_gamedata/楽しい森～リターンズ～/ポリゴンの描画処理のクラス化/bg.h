//------------------------------------------
//
//	背景の処理[bg.h]
//	Author : 筒井 俊稀
//
//------------------------------------------

//二重インクルード防止
#ifndef _BG_H_
#define _BG_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CScene2d;

//------------------------------------------
//	背景のクラス
//------------------------------------------
class CBg : public CScene
{
public:
	//メンバ関数宣言
	CBg(int nPriority = OBJTYPE_NONE);
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	//メンバ変数宣言
	float m_fSpeedFast;								//背景移動スピード
	float m_fSpeedSecond;							//背景移動スピード
	float m_fSpeedThird;							//背景移動スピード
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];	//テクスチャ
	CScene2d *m_apScene2d[MAX_BG];					//Scene情報
	D3DXVECTOR3 m_pos;								//座標
	D3DXVECTOR3 m_size;								//大きさ
};

#endif // !_BG_H_

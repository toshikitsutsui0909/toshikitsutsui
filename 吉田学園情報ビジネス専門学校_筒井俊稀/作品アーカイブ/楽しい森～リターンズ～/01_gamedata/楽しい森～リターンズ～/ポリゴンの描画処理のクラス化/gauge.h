//------------------------------------------
//
//	ゲージの処理[gauge.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _GAUGE_H_
#define _GAUGE_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"

//------------------------------------------
//	ゲージクラス
//------------------------------------------
class CGauge
{
public:
	//メンバ関数宣言
	CGauge();
	~CGauge();

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNum(int nNum);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
private:
	//メンバ変数宣言
	static LPDIRECT3DTEXTURE9	m_pTexture;//テクスチャ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;//頂点バッファ
	D3DXVECTOR3					m_pos;	   //座標
	D3DXVECTOR3					m_size;	   //大きさ
	int							m_nNum;	   //ゲージ量

};

#endif // !_GAUGE_H_

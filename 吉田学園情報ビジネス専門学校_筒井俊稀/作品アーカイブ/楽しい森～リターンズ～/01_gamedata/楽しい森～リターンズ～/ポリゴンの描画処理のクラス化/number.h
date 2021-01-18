//------------------------------------------
//
//	クラスポリゴン描画[player.h]
//	筒井
//
//------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"

//------------------------------------------
//	クラス
//------------------------------------------
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Updata(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetPosition(void) { return m_Pos; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//バッファ
	D3DXVECTOR3				m_Pos;		//座標
	D3DXVECTOR3				m_Size;		//大きさ
	D3DXCOLOR				m_col;		//カラー
};

#endif // !_NUMBER_H_

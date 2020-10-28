//------------------------------------------
//
//	背景の処理[bullet.h]
//	筒井
//
//------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

class CPolygon;
class CRanking;
class CScore;
//------------------------------------------
//	背景のクラス
//------------------------------------------
class CResult : public CScene
{
public:
	CResult();
	~CResult();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CResult *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CRanking *m_pRank;
};

#endif // !_BG_H_#pragma once#pragma once

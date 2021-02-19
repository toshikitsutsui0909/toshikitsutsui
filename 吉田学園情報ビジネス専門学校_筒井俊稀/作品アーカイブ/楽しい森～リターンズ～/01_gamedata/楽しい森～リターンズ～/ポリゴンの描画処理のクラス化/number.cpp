//=============================================================================
//
// 数字の処理 [number.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "number.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NUMBER "data/texture/number000.png"

//=============================================================================
//	静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	//各メンバ変数の初期化
	m_pVtxBuff = NULL;
	m_Pos = D3DXVECTOR3();
	m_Size = D3DXVECTOR3();
	m_col = D3DXCOLOR(255,255,255,255);
}

//=============================================================================
//	デストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//	テクスチャロード処理
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NUMBER, &m_pTexture);

	return S_OK;
}

//=============================================================================
//	テクスチャ破棄
//=============================================================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//	生成処理
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	if (pNumber != NULL)
	{
		pNumber->Init(pos, size);
	}
	return pNumber;
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_Pos = pos;

	m_Size = size;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3((m_Pos.x - m_Size.x / 2), (m_Pos.y - m_Size.y / 2), 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + m_Size.x / 2), (m_Pos.y - m_Size.y / 2), 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3((m_Pos.x - m_Size.x / 2), (m_Pos.y + m_Size.y / 2), 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + m_Size.x / 2), (m_Pos.y + m_Size.y / 2), 0.0f);//右下

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	//バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CNumber::Updata(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
//	数字を設定する処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2((float)nNumber*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)nNumber*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)nNumber*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)nNumber*0.1f + 0.1f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	カラーを設定
//=============================================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

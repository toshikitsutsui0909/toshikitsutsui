//=============================================================================
//
// polygon処理 [scene2d.cpp]
// Author : 
//
//=============================================================================
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

#define FLASH_RATE 0.05f
//=============================================================================
//	コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	//初期化しよう
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	//中心のPOSを求める
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_size = D3DXVECTOR3();
	m_col = D3DXCOLOR();
	m_bFlash = true;
	m_FlashState = FLASH_STATE_IN;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CScene2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	m_size = size;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//右下

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
void CScene2d::Uninit(void)
{
	//バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
//	更新処理
//=============================================================================
void CScene2d::Update(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================
void CScene2d::Draw(void)
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
//	描画したい場所の座標を求める処理
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
                                                                                                                                                                                                                                                                                                                                                                                                                                                                         	VERTEX_2D *pVtx; //頂点情報へのポインタ

	m_pos = pos;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//右下

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	描画したい場所の大きさを求める処理
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
//	描画したい場所のテクスチャを求める処理
//=============================================================================
void CScene2d::SetTex(D3DXVECTOR2* tex)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を設定
	pVtx[0].tex = tex[0];
 	pVtx[1].tex = tex[1];
	pVtx[2].tex = tex[2];
	pVtx[3].tex = tex[3];

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	描画したい場所のテクスチャを求める処理
//=============================================================================
void CScene2d::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	m_col = col;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	テクスチャを分ける処理
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	テクスチャフラッシュ処理
//=============================================================================
void CScene2d::Flashing(void)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	if (m_FlashState == FLASH_STATE_IN)
	{
  		m_col.a -= FLASH_RATE;
		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_FlashState = FLASH_STATE_OUT;
		}
	}
	else if (m_FlashState == FLASH_STATE_OUT)
	{
		m_col.a += FLASH_RATE;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_FlashState = FLASH_STATE_IN;
		}
	}
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//	生成処理
//=============================================================================
CScene2d * CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2d *pScene2D;
	pScene2D = new CScene2d;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, size);
	}
	return pScene2D;
}


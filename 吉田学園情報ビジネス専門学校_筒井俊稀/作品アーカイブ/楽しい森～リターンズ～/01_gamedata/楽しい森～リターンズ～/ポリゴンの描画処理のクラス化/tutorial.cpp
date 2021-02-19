//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_PATH_TUTOLIAL "data/texture/tutorial000.png"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
HRESULT CTutorial::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TUTOLIAL, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CTutorial::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	if (pTutorial != NULL)
	{
		pTutorial->Init(pos, size);
	}
	return pTutorial;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//右下

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
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
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
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
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

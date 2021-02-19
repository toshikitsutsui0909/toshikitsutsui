//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : トシキ
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_PATH_TITLE "data/texture/タイトル.jpg"

//=============================================================================
// 静的メンバ変数宣言初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;
	if (pTitle != NULL)
	{
		pTitle->Init(pos, size);
	}
	return pTitle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3(0,SCREEN_HEIGHT, 0.0f);//左下
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
void CTitle::Uninit(void)
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
void CTitle::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
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
// テクスチャロード
//=============================================================================
HRESULT CTitle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TITLE, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CTitle::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

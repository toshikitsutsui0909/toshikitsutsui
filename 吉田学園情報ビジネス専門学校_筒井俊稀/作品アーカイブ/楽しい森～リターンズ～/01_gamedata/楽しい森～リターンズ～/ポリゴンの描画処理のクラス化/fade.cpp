//=============================================================================
//
// フェードの処理 [fade.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define FADE_RATE (0.1f)

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_NONE;
	m_mode = CManager::MODE_TITLE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CFade * CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFade *pFade;
	pFade = new CFade;
	if (pFade != NULL)
	{
		pFade->Init(pos, size);
	}
	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	CScene::SetObjType(OBJTYPE_FADE);

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
	pVtx[0].col = m_ColorFade;
	pVtx[1].col = m_ColorFade;
	pVtx[2].col = m_ColorFade;
	pVtx[3].col = m_ColorFade;


	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	m_fade = FADE_OUT;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
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
void CFade::Update(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_ColorFade.a -= FADE_RATE;
			if (m_ColorFade.a <= 0.0f)
			{
				m_ColorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_ColorFade.a += FADE_RATE;
			if (m_ColorFade.a >= 1.0f)
			{
				m_ColorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_mode);
			}
		}
	}
	//頂点バッファの範囲をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].col = m_ColorFade;
	pVtx[1].col = m_ColorFade;
	pVtx[2].col = m_ColorFade;
	pVtx[3].col = m_ColorFade;

	//頂点データのをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_OUT;
	m_mode = mode;
}
//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//-----------------------------------------------------------------------------
//	コンストラクタ
//-----------------------------------------------------------------------------
CBg::CBg(int nPriority) : CScene(nPriority)
{
	//変数の初期化
	m_apScene2d[0] = NULL;
	m_apScene2d[1] = NULL;
	m_apScene2d[2] = NULL;
	
	m_fSpeed0 = 0;
	m_fSpeed1 = 0;
	m_fSpeed2 = 0;
}

//-----------------------------------------------------------------------------
//	デストラクタ
//-----------------------------------------------------------------------------
CBg::~CBg()
{
}

//-----------------------------------------------------------------------------
//	テクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	////テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/texture/bg104.png", &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "data/texture/bg101.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data/texture/bg111.png", &m_apTexture[2]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	テクスチャ破棄の処理
//-----------------------------------------------------------------------------
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	生成処理
//-----------------------------------------------------------------------------
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg *pBg;
	pBg = new CBg;
	if (pBg != NULL)
	{
		pBg->Init(pos, size);
	}
	return pBg;
}

//-----------------------------------------------------------------------------
//	初期化処理
//-----------------------------------------------------------------------------
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		m_apScene2d[nCount] = new CScene2d;
		if (m_apScene2d[nCount] != NULL)
		{
			m_apScene2d[nCount]->Init(pos, size);
			m_apScene2d[nCount]->BindTexture(m_apTexture[nCount]);
			m_apScene2d[nCount]->SetObjType(OBJTYPE_BG);
		}
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
//	終了処理
//-----------------------------------------------------------------------------
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2d[nCount] != NULL)
		{
			m_apScene2d[nCount]->Uninit();
			m_apScene2d[nCount] = NULL;
		}
	}

	Release();
}

//-----------------------------------------------------------------------------
//	更新処理
//-----------------------------------------------------------------------------
void CBg::Update(void)
{
	D3DXVECTOR2 tex[4];

	//移動量を決める
	m_fSpeed0 += 0.003f;
	m_fSpeed1 += 0.002f;
	m_fSpeed2 += 0.005f;

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed0, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed0, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed0, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed0, 1.0f);

	m_apScene2d[0]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed1, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed1, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed1, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed1, 1.0f);

	m_apScene2d[1]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed2, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed2, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed2, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed2, 1.0f);

	m_apScene2d[2]->SetTex(tex);

}

//-----------------------------------------------------------------------------
//	描画処理
//-----------------------------------------------------------------------------
void CBg::Draw(void)
{
}

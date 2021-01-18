//=============================================================================
//
// 背景の処理 [bullet.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "ui.h"
#include "renderer.h"
#include "manager.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define RATE (0.005f)

//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_apTexture[UITYPE::TYPE_MAX] = {};

//-----------------------------------------------------------------------------
//	コンストラクタ
//-----------------------------------------------------------------------------
CUi::CUi(int nPriority) : CScene2d(nPriority)
{
	m_type = CUi::TYPE_NONE;
	m_bLoop = true;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCount = 0;
}

//-----------------------------------------------------------------------------
//	デストラクタ
//-----------------------------------------------------------------------------
CUi::~CUi()
{

}

//-----------------------------------------------------------------------------
//	テクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/texture/kuro.jpg", &m_apTexture[CUi::TYPE_KUROHAIKEI]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/texture/playerlife.png", &m_apTexture[CUi::TYPE_LIFE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/texture/WARNING.png", &m_apTexture[CUi::TYPE_WARNING]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/texture/prese_enter.png", &m_apTexture[CUi::TYPE_PRESS_ENTER]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	テクスチャ破棄の処理
//-----------------------------------------------------------------------------
void CUi::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_UI; nCount++)
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
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move)
{
	CUi *pUi;
	pUi = new CUi;
	if (pUi != NULL)
	{
		pUi->Init(pos, size, type);
	}
	return pUi;
}

//-----------------------------------------------------------------------------
//	初期化処理
//-----------------------------------------------------------------------------
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move)
{
	CScene2d::Init(pos, size);
	SetObjType(CScene::OBJTYPE_NONE);
	m_type = type;
	CScene2d::BindTexture(m_apTexture[m_type]);
	CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
	return S_OK;
}

//-----------------------------------------------------------------------------
//	終了処理
//-----------------------------------------------------------------------------
void CUi::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	更新処理
//-----------------------------------------------------------------------------
void CUi::Update(void)
{
	m_nCount++;
	if (m_type == TYPE_WARNING)
	{
		CScene2d::Flashing();
	}
	if (m_type == TYPE_PRESS_ENTER)
	{
		if (m_nCount % 20 == 0)
		{
			CScene2d::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		if (m_nCount % 40 == 0)
		{
			CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//-----------------------------------------------------------------------------
//	描画処理
//-----------------------------------------------------------------------------
void CUi::Draw(void)
{
	/*LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/
	CScene2d::Draw();
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

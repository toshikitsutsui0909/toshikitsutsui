//=============================================================================
//
// 弾の爆発の処理 [explosion.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define TEXTURE_PATH_EXPLOSION "data/texture/explosion000.png"	//爆発テクスチャ

#define EXPLOSION_TEX_ANM 0.125f								//アニメーション間隔の値
#define EXPLOSION_ANM_UNINIT 8									//終了タイミングのカウント
#define EXPLOSION_ANM_COUNT 4									//アニメーションする速さ

//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//-----------------------------------------------------------------------------
//	弾の爆発のコンストラクタ
//-----------------------------------------------------------------------------
CExplosion::CExplosion(int nPriority) : CScene2d(nPriority)
{
	//メンバ変数の初期化
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
}

//-----------------------------------------------------------------------------
//	弾の爆発のデストラクタ
//-----------------------------------------------------------------------------
CExplosion::~CExplosion()
{
}

//-----------------------------------------------------------------------------
//	弾の爆発のテクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_EXPLOSION, &m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	弾の爆発のテクスチャ破棄処理
//-----------------------------------------------------------------------------
void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
//	弾の爆発の生成処理
//-----------------------------------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, size);
	}
	return pExplosion;
}

//-----------------------------------------------------------------------------
//	弾の爆発の初期化処理
//-----------------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	D3DXVECTOR2 tex[4];
	// テクスチャ座標を設定
	tex[0] = D3DXVECTOR2(EXPLOSION_TEX_ANM, 0.0f);
	tex[1] = D3DXVECTOR2(EXPLOSION_TEX_ANM + EXPLOSION_TEX_ANM, 0.0f);
	tex[2] = D3DXVECTOR2(EXPLOSION_TEX_ANM, 1.0f);
	tex[3] = D3DXVECTOR2(EXPLOSION_TEX_ANM + EXPLOSION_TEX_ANM, 1.0f);;

	CScene2d::Init(pos ,size);
	CScene2d::BindTexture(m_pTexture);
	//テクスチャ座標更新
	CScene2d::SetTex(tex);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	弾の爆発の終了処理
//-----------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	弾の爆発の更新処理
//-----------------------------------------------------------------------------
void CExplosion::Update(void)
{
	D3DXVECTOR2 tex[4];
	//カウンター更新
	m_nCounterAnim++;
	if (m_nCounterAnim % EXPLOSION_ANM_COUNT == 0)
	{
		//パターン更新
		m_nPatternAnim++;
		// テクスチャ座標を設定
		tex[0] = D3DXVECTOR2((float)m_nPatternAnim*EXPLOSION_TEX_ANM, 0.0f);
		tex[1] = D3DXVECTOR2((float)m_nPatternAnim*EXPLOSION_TEX_ANM + EXPLOSION_TEX_ANM, 0.0f);
		tex[2] = D3DXVECTOR2((float)m_nPatternAnim*EXPLOSION_TEX_ANM, 1.0f);
		tex[3] = D3DXVECTOR2((float)m_nPatternAnim*EXPLOSION_TEX_ANM + EXPLOSION_TEX_ANM, 1.0f);

		//テクスチャ座標更新
		CScene2d::SetTex(tex);
	}
	//アニメーション終了
	if (m_nPatternAnim >= EXPLOSION_ANM_UNINIT)
	{
		Uninit();
	}
}

//-----------------------------------------------------------------------------
//	弾の爆発の描画処理
//-----------------------------------------------------------------------------
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

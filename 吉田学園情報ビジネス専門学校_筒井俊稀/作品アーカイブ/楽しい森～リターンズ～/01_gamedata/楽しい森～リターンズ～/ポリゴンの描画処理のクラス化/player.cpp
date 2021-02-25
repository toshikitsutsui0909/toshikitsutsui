//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : トシキ
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "player.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "explosion.h"
#include "charge.h"
#include "life.h"
#include "score.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define TEXTURE_PLAYER "data/texture/player1.png"	//プレイヤーテクスチャ

#define PLAYER_LIFE_MAX 3							//残機数
#define PLAYER_LIFE_NUM 1							//ライフ
#define PLAYER_LIFE_DECREASE 1						//残機減る数
#define PLAYER_DIE_POINT 5000						//減るポイント数

#define CBULLET_COUNT 60							//チャージ弾が溜まる時間のカウント値
#define BULLET_SPEED 8.0f							//弾のスピード
#define CBULLET_SPEED 12.0f							//チャージ弾のスピード


//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;


//-----------------------------------------------------------------------------
//	プレイヤーのコンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_nChageCount = 0;
	m_nCntBullet = 0;
	m_bPlaying = true;
	m_bIsDamage = false;
	m_nLife = PLAYER_LIFE_NUM;
	m_nCountLife = PLAYER_LIFE_MAX;
	m_Count = 0;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
}

//-----------------------------------------------------------------------------
//	プレイヤーのデストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
//	プレイヤーの生成処理
//-----------------------------------------------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size);
	}
	return pPlayer;
}

//-----------------------------------------------------------------------------
//	プレイヤーの初期化処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2d::Init(pos,size);
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PLAYER);
	CScene2d::BindTexture(m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	プレイヤーの終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	プレイヤーの更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{
	//VERTEX_2D *pVtx; //頂点情報へのポインタ
	m_pos = GetPosition();
	CInputKeyBoard *pInputKeyBoard
	= CManager::GetInputKeyBoard();

	CSound *pSound
	= CManager::GetSound();

	m_Count++;
	if (!m_bIsDamage)
	{
		if (m_Count % 10 == 0)
		{
			SetColor(D3DXCOLOR(0.8f, 0.0f, 0.0f, 0.0f));
		}
		if(m_Count % 20 == 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	if (m_Count >= 180)
	{
		m_bIsDamage = true;
	}
	if (m_bPlaying)
	{
		//上
		if (pInputKeyBoard->GetKeyPress(DIK_W) == true)
		{
			m_pos.y -= MOVE_SPEED;

		}
		//下
		if (pInputKeyBoard->GetKeyPress(DIK_S) == true)
		{
			m_pos.y += MOVE_SPEED;

		}
		//左
		if (pInputKeyBoard->GetKeyPress(DIK_A) == true)
		{
			m_pos.x -= MOVE_SPEED;

		}
		//右
		if (pInputKeyBoard->GetKeyPress(DIK_D) == true)
		{
			m_pos.x += MOVE_SPEED;

		}

		//画面の端の当たり判定
		//横
		//左
		if (m_pos.x - PLAYER_SIZE_X / 2 <= 0)
		{
			m_pos.x = 0.0f + PLAYER_SIZE_X / 2;
		}
		//右
		if (m_pos.x + PLAYER_SIZE_X / 2 >= SCREEN_WIDTH)
		{
			m_pos.x = SCREEN_WIDTH - PLAYER_SIZE_X / 2;
		}

		//縦
		//上
		if (m_pos.y - PLAYER_SIZE_Y / 2 <= 75.0f)
		{
			m_pos.y = 75.0f + PLAYER_SIZE_Y / 2;
		}
		//下
		if (m_pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - 190.0f)
		{
			m_pos.y = (SCREEN_HEIGHT - 190.0f) - PLAYER_SIZE_Y / 2;
		}



		//球を発
		//長押しで発射
		if (pInputKeyBoard->GetKeyPress(DIK_M) == true)
		{
			m_nCntBullet++;
			if (m_nCntBullet == 10)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
				CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE_PLAYER_X, BULLET_SIZE_PLAYER_Y,
					 0.0f), D3DXVECTOR3(8.0f, 0.0f, 0.0f), CBullet::BULLETTYPE_PLAYER);
				m_nCntBullet = 0;
			}
		}
		if (pInputKeyBoard->GetKeyPress(DIK_SPACE) == true)
		{
			m_nChageCount++;
			CCharge::Add();
		}
		if (pInputKeyBoard->GetKeyRelease(DIK_SPACE) && m_nChageCount >= CBULLET_COUNT)
		{
			//チャージ弾
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			CChargeBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE_PLAYER_X * 2, BULLET_SIZE_PLAYER_Y * 2,
				0.0f), D3DXVECTOR3(CBULLET_SPEED, 0.0f, 0.0f), CBullet::BULLETTYPE_PLAYER);
			m_nChageCount = 0;
			CCharge::Set();
		}
		else if (pInputKeyBoard->GetKeyRelease(DIK_SPACE) && m_nChageCount < CBULLET_COUNT)
		{
			//通常弾
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE_PLAYER_X, BULLET_SIZE_PLAYER_Y, 0.0f), D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f), CBullet::BULLETTYPE_PLAYER);
			m_nChageCount = 0;
			CCharge::Set();
		}
	}

	SetPos(m_pos);
}

//-----------------------------------------------------------------------------
//	プレイヤーの描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	自機のダメージ
//-----------------------------------------------------------------------------
void CPlayer::Hit(int nDamage)
{
	if (m_bIsDamage)
	{
		CGame::GetLife()->SubtractLife(PLAYER_LIFE_DECREASE);
		m_nLife -= nDamage;
		if (m_nLife <= 0)
		{
			CGame::GetScore()->AddScore(-PLAYER_DIE_POINT);
			CSound *pSound = CManager::GetSound();
			CGame *pGame = CManager::GetGame();
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			//爆発の生成
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			//自機の残機がゼロじゃない時自機を生成する
			pGame->SetGameState(CGame::GAMESTATE_NORMAL);
			//自機の破棄
			Uninit();
		}
	}
}

//-----------------------------------------------------------------------------
//	プレイヤーの情報の設定
//-----------------------------------------------------------------------------
void CPlayer::SetPlayer(bool bPlaying)
{
	m_bPlaying = bPlaying;
}

//-----------------------------------------------------------------------------
//	プレイヤーのテクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	プレイヤーのテクスチャ破棄の処理
//-----------------------------------------------------------------------------
void CPlayer::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "explosion.h"
#include "score.h"
#include "game.h"
#include "main.h"
#include "player.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define TEXTURE_PATH_ENEMY_NORMAL	"data/texture/enemy1.png"	//NORMAL
#define TEXTURE_PATH_ENEMY_HARD		"data/texture/enemy2.png"	//HARD
#define TEXTURE_PATH_ENEMY_BOSS		"data/texture/boss1.png"	//boss
#define PATH_ENEMY_DATA				"data/file/enemydata.txt"

#define ENEMY_LIFE_NORMAL 1										//通常敵の体力
#define ENEMY_LIFE_HARD 3										//特殊敵の体力
#define ENEMY_LIFE_BOSS 300										//ボスの体力

#define ENEMY_MOVE_X -4.0f
#define ENEMY_MOVE_Y 1.0f

#define ENEMY_NORMAL_POINTUP 2000								//通常敵を倒したときのポイント
#define ENEMY_HARD_POINTUP 6000									//特殊敵を倒したときのポイント
#define ENEMY_BOSS_POINTUP 250000								//ボスを倒したときのポイント

//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[ENEMYTYPE::TYPE_MAX] = {};
//-----------------------------------------------------------------------------
//	敵のコンストラクタ
//-----------------------------------------------------------------------------
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	//各変数の初期化
	m_nDamage = 1;
	m_nCount = 0;
	m_nLife = 0;
	m_nRandNumber = 0;
	m_move = D3DXVECTOR3(ENEMY_MOVE_X, ENEMY_MOVE_Y, 0.0f);
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
	m_Counter = 0;
	m_nCntCol = 0;
	m_bDamege = false;
}

//-----------------------------------------------------------------------------
//	敵のデストラクタ
//-----------------------------------------------------------------------------
CEnemy::~CEnemy()
{
}

//-----------------------------------------------------------------------------
//	敵のテクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	FILE*pFile = NULL;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_NORMAL, &m_apTexture[ENEMYTYPE::TYPE_NORMAL]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_NORMAL, &m_apTexture[ENEMYTYPE::TYPE_NORMAL_2]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_NORMAL, &m_apTexture[ENEMYTYPE::TYPE_NORMAL_3]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_HARD, &m_apTexture[ENEMYTYPE::TYPE_NORMAL_4]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_HARD, &m_apTexture[ENEMYTYPE::TYPE_NORMAL_5]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_HARD, &m_apTexture[ENEMYTYPE::TYPE_HARDTYPE]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_ENEMY_BOSS, &m_apTexture[ENEMYTYPE::TYPE_BOSS]);


	return S_OK;
}

//-----------------------------------------------------------------------------
//	敵のテクスチャ破棄処理
//-----------------------------------------------------------------------------
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < ENEMYTYPE::TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	敵の生成処理
//-----------------------------------------------------------------------------
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type)
{
	CEnemy *pEnemy = NULL;
	pEnemy = new CEnemy;
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, size, type);
	}
	return pEnemy;
}

//-----------------------------------------------------------------------------
//	敵の初期化処理
//-----------------------------------------------------------------------------
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type)
{
	CScene2d::Init(pos, size);
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_ENEMY);
	m_type = type;
	switch (m_type)
	{
	case TYPE_NORMAL:
		m_nLife = ENEMY_LIFE_NORMAL;
		break;

	case TYPE_NORMAL_2:
		m_nLife = ENEMY_LIFE_NORMAL;
		break;

	case TYPE_NORMAL_3:
		m_nLife = ENEMY_LIFE_NORMAL;
		break;

	case TYPE_NORMAL_4:
		m_nLife = ENEMY_LIFE_NORMAL;
		break;

	case TYPE_NORMAL_5:
		m_nLife = ENEMY_LIFE_NORMAL;
		break;

	case TYPE_HARDTYPE:
		m_nLife = ENEMY_LIFE_HARD;
		break;

	case TYPE_BOSS:
		m_nLife = ENEMY_LIFE_BOSS;
		break;
	}
	//2Dポリゴンの生成
	CScene2d::BindTexture(m_apTexture[m_type]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	敵の終了処理
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
 	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	敵の更新処理
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	m_pos = GetPosition();

	CSound *pSound
		= CManager::GetSound();

	//ゲームの情報を取得
	CGame *pGame = CManager::GetGame();

	m_nCount++;
	//ダメージをくらったら点滅させる
	if (m_bDamege)
	{
		m_nCntCol++;
		CScene2d::SetColor(D3DXCOLOR(1, 0, 0, 1));
		//カウントが5行ったらダメージ判定をつける
		if (m_nCntCol >= 5)
		{
			CScene2d::SetColor(D3DXCOLOR(1, 1, 1, 1));
			m_nCntCol = 0;
			m_bDamege = false;
		}
	}
	//敵の移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	SetPos(m_pos);

	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene = GetScene(nPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objtype;
				objtype = pScene->GetObjType();
				//当たったものが自機だった場合
				if (objtype == CScene::OBJTYPE_PLAYER)
				{
					D3DXVECTOR3 PosPlayer = ((CScene2d*)pScene)->GetPosition();
					D3DXVECTOR3 SizePlayer = ((CScene2d*)pScene)->GetSize();
					////当たり判定
					if (PosPlayer.x + SizePlayer.x / 2 >= m_pos.x
						&& PosPlayer.x - SizePlayer.x / 2 <= m_pos.x
						&& PosPlayer.y + SizePlayer.y / 2 >= m_pos.y
						&& PosPlayer.y - SizePlayer.y / 2 <= m_pos.y)
					{
						((CPlayer*)pScene)->Hit(m_nDamage);
						return;
					}
					//ゲームステートの初期化
					//pGame->SetGameState(CGame::GAMESTATE_NONE);
				}
			}
		}
	}
	//敵の種類ごとの設定（移動＆弾）
	switch (m_type)
	{
	//通常の敵
	case TYPE_NORMAL:
		m_Counter++;
		if (m_Counter == 30 || m_pos.x >= 1200.0f)
		{
			m_move.y *= -1.0f;
			m_Counter = 0;
		}
		if (40 % (rand() % 150+ 30) == 0 && m_pos.x - ENEMY_SIZE_X <= SCREEN_WIDTH)
		{
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

			float fTangent = atan2f(playerPos.y - m_pos.y, playerPos.x - m_pos.x);

			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f), 
				D3DXVECTOR3(cosf(fTangent) * 7.0f, sinf(fTangent) * 7.0f, 0.0f), CBullet::BULLETTYPE_ENEMY);
		}
		break;

	//通常の敵２
	case TYPE_NORMAL_2:
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE_X <= 750.0f)
		{
			m_move.y = 3.0f;
		}
		if (m_pos.y - ENEMY_SIZE_X >= 450.0f)
		{
			m_move.y = 0.0f;
		}
		if (m_nCount % 60 == 0 && m_pos.x - ENEMY_SIZE_X <= 750.0f)
		{
			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
				D3DXVECTOR3(-5.0f, 0.0f, 0.0f), CBullet::BULLETTYPE_ENEMY);
		}
		break;

	//通常の敵３
	case TYPE_NORMAL_3:
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE_X <= 800.0f)
		{
			m_move.y = -3.0f;
		}
		if (m_pos.y - ENEMY_SIZE_X <= 100.0f)
		{
			m_move.y = 0.0f;
		}
		if (m_nCount % 50 == 0 && m_pos.x - ENEMY_SIZE_X <= 900.0f)
		{
			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
				D3DXVECTOR3(-5.0f, 0.0f, 0.0f), CBullet::BULLETTYPE_ENEMY);
		}
		break;

	//通常の敵４
	case TYPE_NORMAL_4:
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE_X <= 400.0f)
		{
			m_move.y = 4.0f;
		}
		if (m_pos.y - ENEMY_SIZE_X >= 250.0f)
		{
			m_move.y = 0.0f;
			m_move.x = 4.0f;
		}
		break;

	//通常の敵５
	case TYPE_NORMAL_5:
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE_X <= 400.0f)
		{
			m_move.y = -4.0f;
		}
		if (m_pos.y - ENEMY_SIZE_X <= 400.0f)
		{
			m_move.y = 0.0f;
			m_move.x = 4.0f;
		}
		if (m_nCount % 50 == 0 && m_pos.x - BOSS_SIZE <= 700.0f)
		{
			int num = 2;
			float fTheta = 20.0f;
			float fRaddaStep = D3DXToRadian(fTheta);
			float Radda = num % 2 ? -num / 2 * fRaddaStep : (-num / 2 + 0.5f) * fRaddaStep;
			for (int nCount = 0; nCount <= num; nCount++, Radda += fRaddaStep)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
					D3DXVECTOR3(-cosf(Radda) * 5, sinf(Radda) * 4, 0.0f), CBullet::BULLETTYPE_ENEMY_2);
			}
		}
		break;

	//紫の敵
	case TYPE_HARDTYPE:
		m_Counter++;
		m_move.x = -6.0f;
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE / 2 <= 900.0f)
		{
			m_move.x = 0.0f;
		}
		if (m_nCount % 50 == 0 && m_pos.x - BOSS_SIZE <= 900.0f)
		{
			int num = 2;
			float fTheta = 20.0f;
			float fRaddaStep = D3DXToRadian(fTheta);
			float Radda = num % 2 ? -num / 2 * fRaddaStep : (-num / 2 + 0.5f) * fRaddaStep;
			for (int nCount = 0; nCount <= num; nCount++, Radda += fRaddaStep)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
					D3DXVECTOR3(-cosf(Radda) * 5, sinf(Radda) * 4, 0.0f), CBullet::BULLETTYPE_ENEMY_2);
			}
		}
		if (m_Counter >= 270)
		{
			m_move.x = 5.0f;
		}
		break;

	//ボス敵
	case TYPE_BOSS:
		m_move.y = 0.0f;
		if (m_pos.x - ENEMY_SIZE / 2 <= 1100.0f)
		{
			m_move.x = 0.0f;
		}

		if (50 % (rand() % 100 + 20) == 0 && m_pos.x - BOSS_SIZE <= SCREEN_WIDTH)
		{
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();
			float fTangent = atan2f(playerPos.y - m_pos.y, playerPos.x - m_pos.x);
			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f), 
				D3DXVECTOR3(cosf(fTangent) * 7.0f, sinf(fTangent) * 7.0f, 0.0f), CBullet::BULLETTYPE_ENEMY);
		}
		if (m_nCount % 60 == 0 && m_pos.x - BOSS_SIZE <= SCREEN_WIDTH)
		{
			int num = 5;
			float fTheta = 20.0f;
			float fRaddaStep = D3DXToRadian(fTheta);
			float Radda = num % 2 ? -num / 2 * fRaddaStep : (-num / 2 + 0.5f) * fRaddaStep;
			for (int nCount = 0; nCount <= num; nCount++, Radda += fRaddaStep)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
					D3DXVECTOR3(-cosf(Radda) * 10, sinf(Radda) * 10, 0.0f),CBullet::BULLETTYPE_ENEMY_2);
			}
		}
		if (m_nCount % 80 == 0 && m_pos.x - BOSS_SIZE <= SCREEN_WIDTH)
		{
			int num = 4;
			float fTheta = 20.0f;
			float fRaddaStep = D3DXToRadian(fTheta);
			float Radda = num % 2 ? -num / 2 * fRaddaStep : (-num / 2 + 0.5f) * fRaddaStep;
			for (int nCount = 0; nCount <= num; nCount++, Radda += fRaddaStep)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f),
					D3DXVECTOR3(-cosf(Radda) * 8, sinf(Radda) * 8, 0.0f), CBullet::BULLETTYPE_ENEMY);
			}
		}
		if (m_nLife <= 0)
		{
			m_move.y = 1.0f;
		}
		if (m_pos.y + BOSS_SIZE / 2 >= SCREEN_HEIGHT - 170.0f)
		{
			m_move.y = 0.0f;
			Hit(m_nDamage);
		}
		break;
	}

	//敵が画面外に出たら消す処理
	if (m_pos.x - ENEMY_SIZE <= -100.0f)
	{
		Uninit();
		return;
	}
	if (m_pos.x + ENEMY_SIZE >= SCREEN_WIDTH + 2500.0f)
	{
		Uninit();
		return;
	}
}

//-----------------------------------------------------------------------------
//	敵の描画処理
//-----------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	ダメージ
//-----------------------------------------------------------------------------
void CEnemy::Hit(int nDamage)
{
	//ゲームの情報を取得
	CGame *pGame = CManager::GetGame();
	//音楽情報の取得
	CSound *pSound = CManager::GetSound();

	//ライフのメンバ変数にダメージの情報を代入
	m_nLife -= nDamage;
	m_bDamege = true;

	//ライフがゼロになった時（死んだとき）
	if (m_nLife <= 0)
	{
		//m_typeの処理
		switch (m_type)
		{
		//通常の敵
		case TYPE_NORMAL:
			//スコア100を加
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//通常の敵２
		case TYPE_NORMAL_2:
			//スコア100を加
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//通常の敵３
		case TYPE_NORMAL_3:
			//スコア100を加
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//通常の敵４
		case TYPE_NORMAL_4:
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//通常の敵５
		case TYPE_NORMAL_5:
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//紫の敵
		case TYPE_HARDTYPE:
			CGame::GetScore()->AddScore(ENEMY_HARD_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//ボス敵
		case TYPE_BOSS:
			if (m_pos.y + BOSS_SIZE / 2 >= SCREEN_HEIGHT - 170.0f)
			{
				pGame->GetPlayer()->SetPlayer(false);
				//スコア500を加算
				CGame::GetScore()->AddScore(ENEMY_BOSS_POINTUP);
				//爆発の生成
				CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE * 10, EXPLOSION_SIZE * 10, 0.0f));
				//爆発の音
				pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
				//クリアに移行
				pGame->SetGameState(CGame::GAMESTATE_CLEAR);
				Uninit();
			}
			break;
		}
	}
}
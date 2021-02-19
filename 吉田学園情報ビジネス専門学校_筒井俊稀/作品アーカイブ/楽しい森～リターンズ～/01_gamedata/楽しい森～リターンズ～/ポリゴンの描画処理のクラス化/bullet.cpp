//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "scene2d.h"
#include "explosion.h"
#include "sound.h"
#include "score.h"
#include "enemy.h"
#include "main.h"
#include "player.h"
#include "game.h"
#include "life.h"

//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define NORMAL_DAMAGE_NUM 1												//体力（NORMAL）
#define HARD_DAMAGE_NUM 3												//体力（HARD）

#define TEXTURE_PATH_BULLET_PLAYER "data/texture/bullet100.png"			//弾テクスチャ
#define TEXTURE_PATH_BULLET_ENEMY1 "data/texture/enemy_bullet000.png"	//エネミー弾テクスチャ
#define TEXTURE_PATH_BULLET_ENEMY2 "data/texture/enemy_bullet001.png"	//エネミー弾テクスチャ

#define BULLET_DIE_POINT_RIGHT 100.0f									//弾が消えるポイント（右）
#define BULLET_DIE_POINT_LEFT 100.0f									//弾が消えるポイント（左）
#define BULLET_DIE_POINT_UP 60.0f										//弾が消えるポイント（上）
#define BULLET_DIE_POINT_DOWN 170.0f									//弾が消えるポイント（下）

//-----------------------------------------------------------------------------
//	静的メンバ変数の初期化
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[BULLETTYPE::BULLETTYPE_MAX] = {};
int CBullet::m_nCount = 0;
bool CBullet::m_bDamage = true;

//-----------------------------------------------------------------------------
//	弾のコンストラクタ
//-----------------------------------------------------------------------------
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	//弾の情報の初期化
	m_BulletType = BULLETTYPE_NONE;
	m_nDamage = 0;
	m_move = D3DXVECTOR3();
}

//-----------------------------------------------------------------------------
//	弾のデストラクタ
//-----------------------------------------------------------------------------
CBullet::~CBullet()
{
}

//-----------------------------------------------------------------------------
//	弾のテクスチャロード処理
//-----------------------------------------------------------------------------
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_PLAYER, &m_apTexture[BULLETTYPE_PLAYER]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_ENEMY1, &m_apTexture[BULLETTYPE_ENEMY]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_ENEMY2, &m_apTexture[BULLETTYPE_ENEMY_2]);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
void CBullet::UnLoad(void)
{
	for (int nCount = BULLETTYPE_PLAYER; nCount < BULLETTYPE_MAX; nCount++)
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
//	弾の生成処理
//-----------------------------------------------------------------------------
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	if (pBullet != NULL)
	{
		pBullet->Init(pos, size, move, type, distance);
	}
	return pBullet;
}

//-----------------------------------------------------------------------------
//	弾の初期化処理
//-----------------------------------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CScene2d::Init(pos,size);
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET);
	m_move = move;
	m_BulletType = type;
	//ダメージ数
	SetBullet(NORMAL_DAMAGE_NUM);
	CScene2d::BindTexture(m_apTexture[type]);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	弾の終了処理
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	弾の更新処理
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	//posの変数
	D3DXVECTOR3 pos;
	//弾の位置情報を取得
	pos = GetPosition();

	//サウンド情報を取得
	CSound *pSound
	= CManager::GetSound();

	//移動方向に値を足す
	pos.x += m_move.x;
	pos.y += m_move.y;

	SetPos(pos);

	//各弾の処理
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		//各弾の処理
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene = GetScene(nPriority, nCntScene);
			CGame *pGame = CManager::GetGame();
			if (pScene != NULL)
			{
				OBJTYPE objtype;
				objtype = pScene->GetObjType();

				//プレイヤーの弾
				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					//当たったものが敵だった場合
					if (objtype == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 PosEnemy = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizeEnemy = ((CScene2d*)pScene)->GetSize();
						////当たり判定
						if (PosEnemy.x + SizeEnemy.x / 2 >= pos.x
							&& PosEnemy.x - SizeEnemy.x / 2 <= pos.x
							&& PosEnemy.y + SizeEnemy.y / 2 >= pos.y
							&& PosEnemy.y - SizeEnemy.y / 2 <= pos.y)
						{
							((CEnemy*)pScene)->Hit(m_nDamage);
							//弾の破棄
							Uninit();
							return;
						}
					}
				}

				//エネミーの弾
				if (m_BulletType == BULLETTYPE_ENEMY || m_BulletType == BULLETTYPE_ENEMY_2)
				{
					//当たったものが自機だった場合
					if (objtype == OBJTYPE_PLAYER)
					{
						D3DXVECTOR3 PosPlayer = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizePlayer = ((CScene2d*)pScene)->GetSize();
						////当たり判定
						if (PosPlayer.x + SizePlayer.x / 2 >= pos.x
							&& PosPlayer.x - SizePlayer.x / 2 <= pos.x
							&& PosPlayer.y + SizePlayer.y / 2 >= pos.y
							&& PosPlayer.y - SizePlayer.y / 2 <= pos.y)
						{
							((CPlayer*)pScene)->Hit(m_nDamage);
							//弾の破棄
							Uninit();
							return;
						}
					}
					//残機がなくなったら敵の弾消す
					if (pGame->GetGameState() == CGame::GAMESTATE_CLEAR || pGame->GetGameState() == CGame::GAMESTATE_END)
					{
						//弾の破棄
						Uninit();
						return;
					}
				}
			}
		}
	}
	//ライフがゼロになった時
	//右
	if (pos.x + PLAYER_SIZE_X >= SCREEN_WIDTH + BULLET_DIE_POINT_RIGHT)
	{
		Uninit();
		return;
	}
	//左
	if (pos.x - PLAYER_SIZE_X <= -BULLET_DIE_POINT_LEFT)
	{
		Uninit();
		return;
	}
	//上
	if (pos.y - PLAYER_SIZE_Y / 2 <= BULLET_DIE_POINT_UP)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
	//下
	if (pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - BULLET_DIE_POINT_DOWN)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
}

//-----------------------------------------------------------------------------
//	弾の描画処理
//-----------------------------------------------------------------------------
void CBullet::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	弾の攻撃力の設定
//-----------------------------------------------------------------------------
void CBullet::SetBullet(int nDamage)
{
  	m_nDamage = nDamage;
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
CChargeBullet::CChargeBullet()
{
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
CChargeBullet::~CChargeBullet()
{

}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
CChargeBullet * CChargeBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CChargeBullet *pChargeBullet;
	pChargeBullet = new CChargeBullet;
	if (pChargeBullet != NULL)
	{
		pChargeBullet->Init(pos, size, move, type, distance);
	}
	return pChargeBullet;
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
HRESULT CChargeBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CBullet::Init(pos, size, move, type, distance);
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_CBULLET);
	m_move = move;
	m_BulletType = type;
	//ダメージ数
 	SetBullet(HARD_DAMAGE_NUM);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
void CChargeBullet::Uninit(void)
{
	CBullet::Uninit();
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
void CChargeBullet::Update(void)
{
	D3DXVECTOR3 pos;
	pos = GetPosition();

	CSound *pSound
		= CManager::GetSound();

	//移動方向に値を足す
	pos.x += m_move.x;
	pos.y += m_move.y;

	SetPos(pos);

	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		//各弾の処理
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene = GetScene(nPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objtype;
				objtype = pScene->GetObjType();

				//プレイヤーの弾
				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					//当たったものが敵だった場合
					if (objtype == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 PosEnemy = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizeEnemy = ((CScene2d*)pScene)->GetSize();
						////当たり判定
						if (PosEnemy.x + SizeEnemy.x / 2 >= pos.x
							&& PosEnemy.x - SizeEnemy.x / 2 <= pos.x
							&& PosEnemy.y + SizeEnemy.y / 2 >= pos.y
							&& PosEnemy.y - SizeEnemy.y / 2 <= pos.y)
						{
							((CEnemy*)pScene)->Hit(m_nDamage);
							//爆発の生成
							pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

							return;
						}
					}
				}
			}
		}
	}
	//ライフがゼロになった時
	//右
	if (pos.x + PLAYER_SIZE_X >= SCREEN_WIDTH + BULLET_DIE_POINT_RIGHT)
	{
		Uninit();
		return;
	}
	//左
	if (pos.x - PLAYER_SIZE_X <= -BULLET_DIE_POINT_LEFT)
	{
		Uninit();
		return;
	}
	//上
	if (pos.y - PLAYER_SIZE_Y / 2 <= BULLET_DIE_POINT_UP)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
	//下
	if (pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - BULLET_DIE_POINT_DOWN)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
}

//-----------------------------------------------------------------------------
//	弾のテクスチャの破棄の処理
//-----------------------------------------------------------------------------
void CChargeBullet::Draw(void)
{
	CScene2d::Draw();
}
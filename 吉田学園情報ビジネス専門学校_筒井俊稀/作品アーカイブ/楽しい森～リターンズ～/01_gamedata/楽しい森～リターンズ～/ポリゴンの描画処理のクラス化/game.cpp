//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : トシキ
//
//=============================================================================
#include "game.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"
#include "bg.h"
#include "score.h"
#include "ui.h"
#include "life.h"
#include "fade.h"
#include "charge.h"
#include "gaugeber.h"
#include "input.h"
#include "sound.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_COUNT 60

#define WARNING_POS_X 640.0f	//ワーニングのX座標
#define WARNING_POS_Y 330.0f	//ワーニングのY座標
#define WARNING_SIZE_X 700.0f	//サイズX
#define WARNING_SIZE_Y 200.0f	//サイズY

#define ENEMY_POS_X_1 1500.0f	//前
#define ENEMY_POS_X_2 1600.0f	//二番目
#define ENEMY_POS_X_3 1700.0f	//三番目
#define ENEMY_POS_X_4 1800.0f	//四番目
#define ENEMY_POS_X_5 1900.0f	//最後

#define ENEMY_POS_Y_1 200.0f	//上
#define ENEMY_POS_Y_2 450.0f	//下
#define ENEMY_POS_Y_3 300.0f	//真ん中

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScore*CGame::m_pScore = NULL;
CPlayer*CGame::m_pPlayer = NULL;
CLife*CGame::m_pLife = NULL;
CUi*CGame::m_pUi = NULL;
CSound*CGame::m_pSound = NULL;
int CGame::m_nCount = 0;
CGame::GAMESTATE CGame::m_gameState = CGame::GAMESTATE_NONE;
CGame::ENEMYSTATE CGame::m_enemystate = CGame::ENEMYSTATE_1;
//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	//初期化
	m_nEnemyCounter = 0;
	m_nCounterGameState = 0;
	m_fCountUi = 1000.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CGame *pGame;
	pGame = new CGame;
	if (pGame != NULL)
	{
		pGame->Init(pos, size);
	}
	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//自機の生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 620.0f, 0.0f));
	//下のUIの表示の生成（スコアと自機の残機が入っているところ）
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 720.0f, 0.0f), D3DXVECTOR3(1280.0f, 250.0f, 0.0f),CUi::TYPE_DOWNUI);
	//チャージの生成処理
	CCharge::Create();
	//ゲージバーの生成処理
	CGaugeber::Create(D3DXVECTOR3(590.0f,635.0f,0.0f), D3DXVECTOR3(490.0f, 25.0f, 0.0f));
	//自機の残機の生成
	m_pLife = CLife::Create(D3DXVECTOR3(145.0f, 625.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CUi::Create(D3DXVECTOR3(60.0f, 620.0f, 0.0f), D3DXVECTOR3(120.0f, 50.0f, 0.0f), CUi::TYPE_LIFE);
	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(550.0f, 0.0f, 0.0f), D3DXVECTOR3(NUMBER_SIZE, NUMBER_SIZE, 0.0f));
	//静的メンバ変数宣言の初期化
	InitVariable();

	m_pSound = CManager::GetSound();
	m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
	//ゲームステート初期化
	m_gameState = GAMESTATE_NONE;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{	
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	D3DXVECTOR3 pos = m_pPlayer->GetPosition();
	CFade *pFade;

	m_nEnemyCounter++;

	switch (m_gameState)
	{
		//プレイヤーが死んだとき
	case GAMESTATE_NORMAL:
		m_nCounterGameState++;
		if (m_nCounterGameState >= GAME_COUNT)
		{
			m_nCount++;
			if (m_pPlayer != NULL && m_nCount != 3)
			{
				//プレイヤー復活
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
				m_nCounterGameState = 0;
				SetGameState(GAMESTATE_NONE);
			}
		}
		if (m_nCount == 3)
		{
			//残機0で終了
			SetGameState(GAMESTATE_END);
			m_nCount = 0;
		}
		break;
		//ゲームオーバー
	case GAMESTATE_END:
		m_nCounterGameState++;
		pFade = CManager::GetFade();
		if (m_nCounterGameState >= GAME_COUNT)
		{
			//画面モードの設定
			pFade->SetFade(CManager::MODE_GAMEOVER);
			SetEnemyState(ENEMYSTATE_1);
		}
		break;
		//ゲームクリア
	case GAMESTATE_CLEAR:
		m_pPlayer->SetPlayer(false);
		pFade = CManager::GetFade();
		m_nCounterGameState++;
		if (m_nCounterGameState >= GAME_COUNT)
		{
			//画面モードの設定
			pFade->SetFade(CManager::MODE_RESULT);
			SetEnemyState(ENEMYSTATE_1);
		}
		break;
	}

	//敵の出方
	switch (m_enemystate)
	{
	case ENEMYSTATE_1:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter >= 120)
		{
			SetEnemyState(ENEMYSTATE_2);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_2:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter >= 120)
		{
			SetEnemyState(ENEMYSTATE_3);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_3:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter >= 270)
		{
			SetEnemyState(ENEMYSTATE_4);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_4:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(1525.0f, 200.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1550.0f, 300.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1575.0f, 400.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
		}
		else if (m_nEnemyCounter >= 320)
		{
			SetEnemyState(ENEMYSTATE_5);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_5:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter == 120)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 350.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 350.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 350.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 350.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, 350.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter == 240)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 250.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 250.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 250.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 250.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, 250.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter >= 420)
		{
			SetEnemyState(ENEMYSTATE_6);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_6:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 150.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_2);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 150.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_2);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 150.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_2);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 150.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_2);

			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 500.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_3);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 500.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_3);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 500.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_3);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 500.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_3);
		}
		else if (m_nEnemyCounter >= 240)
		{
			SetEnemyState(ENEMYSTATE_7);
			m_nEnemyCounter = 0;
		}
		break;

	case ENEMYSTATE_7:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(1525.0f, 175.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1550.0f, 225.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1575.0f, 275.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
		}
		if (m_nEnemyCounter == 220)
		{
			CEnemy::Create(D3DXVECTOR3(1500.0f, 325.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1525.0f, 375.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
			CEnemy::Create(D3DXVECTOR3(1550.0f, 425.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_HARDTYPE);
		}
		else if (m_nEnemyCounter >= 760)
		{
			SetEnemyState(ENEMYSTATE_8);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_8:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_5);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_5);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_5);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, 450.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL_5);
		}
		else if (m_nEnemyCounter >= 360)
		{
			SetEnemyState(ENEMYSTATE_9);
			m_nEnemyCounter = 0;
		}
		break;
	case ENEMYSTATE_9:
		if (m_nEnemyCounter == 5)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_1, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		if (m_nEnemyCounter == 60)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_2, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		if (m_nEnemyCounter == 120)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_2, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_3, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_4, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_5, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_NORMAL);
		}
		else if (m_nEnemyCounter >= 500)
		{
			SetEnemyState(ENEMYSTATE_11);
			m_nEnemyCounter = 0;
			m_pUi = CUi::Create(D3DXVECTOR3(WARNING_POS_X, WARNING_POS_Y, 0.0f), D3DXVECTOR3(WARNING_SIZE_X, WARNING_SIZE_Y, 0.0f), CUi::TYPE_WARNING);
			m_pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pSound->Play(CSound::SOUND_LABEL_BGM_ALARM);
		}
		break;
	case ENEMYSTATE_11:
		//ボス敵を出現させる（生成処理）
		if (m_nEnemyCounter == 270)
		{
			if (m_pUi != NULL)
			{
				m_pUi->Uninit();
				m_pUi = NULL;
			}
			m_pSound->Stop(CSound::SOUND_LABEL_BGM_ALARM);
			m_pSound->Play(CSound::SOUND_LABEL_BGM_BOSS);
		}
		if (m_nEnemyCounter == 290)
		{
			CEnemy::Create(D3DXVECTOR3(ENEMY_POS_X_1, ENEMY_POS_Y_3, 0.0f), D3DXVECTOR3(BOSS_SIZE, BOSS_SIZE, 0.0f), CEnemy::ENEMYTYPE::TYPE_BOSS);
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// 静的メンバ変数の初期化
//=============================================================================
void CGame::InitVariable(void)
{
	m_nCount = 0;
}

//=============================================================================
// ゲームステートを設定
//=============================================================================
void CGame::SetGameState(GAMESTATE state)
{
	m_gameState = state;
}

//=============================================================================
// ゲームステートを取得
//=============================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_gameState;
}

//=============================================================================
// エネミーの設定
//=============================================================================
void CGame::SetEnemyState(ENEMYSTATE state)
{
	m_enemystate = state;
}

//=============================================================================
// エネミー情報を取得
//=============================================================================
CGame::ENEMYSTATE CGame::GetEnemyState(void)
{
	return m_enemystate;
}

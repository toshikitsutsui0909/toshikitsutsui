//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "enemy.h"
#include <Windows.h>
#include "manager.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "ui.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "gaugeber.h"
#include "tutorial.h"
#include "scene.h"
#include "ui.h"
#include "gameover.h"

//-----------------------------------------------------------------------------
//		静的メンバ変数の初期化
//-----------------------------------------------------------------------------
CRenderer*CManager::m_pRenderer = NULL;
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;
CSound*CManager::m_pSound = NULL;
CTitle*CManager::m_pTitle = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CFade * CManager::m_pFade = NULL;
CScene * CManager::m_pScene = NULL;
CScore*CManager::m_pScore = NULL;
CUi*CManager::m_pUi = NULL;
CGameover*CManager::m_pGameover = NULL;
CBasemode*CManager::m_pBasemode = NULL;

//-----------------------------------------------------------------------------
//		コンストラクタ
//-----------------------------------------------------------------------------
CManager::CManager()
{
}

//-----------------------------------------------------------------------------
//		デストラクタ
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
//		初期化処理
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダリングクラスを生成
	m_pRenderer = new CRenderer;
	// 初期化処理
	m_pRenderer->Init(hWnd, bWindow);

	//入力処理を生成
	m_pInputKeyBoard = new CInputKeyBoard;
	// 初期化処理
	m_pInputKeyBoard->Init(hInstance, hWnd);

	//サウンド処理を生成
	m_pSound = new CSound;
	// 初期化処理
	m_pSound->Init(hWnd);


	//各テクスチャロード処理
	//プレイヤーのテクスチャロード
	CPlayer::Load();
	//球のテクスチャロード
	CBullet::Load();
	//敵のテクスチャロード
	CEnemy::Load();
	//弾の爆発のテクスチャロード
	CExplosion::Load();
	//弾の爆発のテクスチャロード
	CBg::Load();
	//数字のテクスチャロード
	CNumber::Load();
	//UIのテクスチャロード
	CUi::Load();
	//チュートリアルのテクスチャロード
	CTutorial::Load();
	//リザルトのテクスチャロード
	CResult::Load();
	//ゲージバーのテクスチャロード
	CGaugeber::Load();
	//ゲームオーバーのテクスチャロード
	CGameover::Load();
	//タイトルのテクスチャロード
	CTitle::Load();
	m_pFade = CFade::Create();

	return S_OK;
 }

//-----------------------------------------------------------------------------
//		終了処理
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//各テクスチャ破棄処理
	CTitle::UnLoad();
	CGameover::UnLoad();
	CGaugeber::UnLoad();
	CResult::UnLoad();
	CTutorial::UnLoad();
	CNumber::Unload();
	CUi::UnLoad();
	CBg::UnLoad();
	CExplosion::UnLoad();
	CEnemy::UnLoad();
	CBullet::UnLoad();
	CPlayer::UnLoad();
	CScene::ReleaseAll();

	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();
		//メモリを解放
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pInputKeyBoard != NULL)
	{
		// 終了処理
		m_pInputKeyBoard->Uninit();
		//メモリを解放
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}
	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		//メモリを解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-----------------------------------------------------------------------------
//		更新処理
//-----------------------------------------------------------------------------
void CManager::Updata(void)
{
	// 更新処理
	m_pInputKeyBoard->Update();

	if (m_pRenderer != NULL)
	{
		// 更新処理
		m_pRenderer->Update();
	}

	//更新モード
	switch (m_mode)
	{
		//タイトルの時
	case MODE_TITLE:
		//エンターキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//サウンド処理とモード移行
			m_pSound->Play(CSound::SOUND_LABEL_SE_ENTER);
			m_pFade->SetFade(MODE_TUTORIAL);
		}
		break;
		//チュートリアルの時
	case MODE_TUTORIAL:
		//エンターキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//サウンド処理とモード移行
			m_pSound->Play(CSound::SOUND_LABEL_SE_ENTER);
			m_pFade->SetFade(MODE_GAME);
		}
		break;
		//ゲームの時
	case MODE_GAME:
		//Pキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_P))
		{
			m_pScene->Pause(false);
		}
		//エンターキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			m_pScene->Pause(true);
		}
		break;
		//ゲームオーバーの時
	case MODE_GAMEOVER:
		//エンターキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//モード移行
			m_pFade->SetFade(MODE_RESULT);
		}
		break;
		//リザルトの時
	case MODE_RESULT:
		//エンターキーが押された時
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//モード移行
			m_pFade->SetFade(MODE_TITLE);
		}
		break;
	}
}

//-----------------------------------------------------------------------------
//		描画処理
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}

	//描画モード
	switch (m_mode)
	{
	case MODE_TITLE:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_GAME:
		break;
	case MODE_RESULT:
		break;
	}

}

//-----------------------------------------------------------------------------
//		モードを設定
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//初期化と終了のモード分け
	switch (m_mode)
	{
		//タイトルの時
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
			if (m_pUi != NULL)
			{
				m_pUi->Uninit();
				m_pUi = NULL;
			}
		}
		break;
		//チュートリアルの時
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
			m_pSound->Stop();
		}
		break;
		//ゲームの時
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			CScene::ReleaseAllFade();
			m_pGame = NULL;
			m_pSound->Stop();
		}
		break;
		//ゲームオーバーの時
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Uninit();
			m_pGameover = NULL;
			m_pSound->Stop();
		}
		break;
		//リザルトの時
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
			m_pSound->Stop();
		}
		break;
	}
	//mode変数に現在のモードを入れる
	m_mode = mode;

	switch (mode)
	{
		//タイトルの時
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
			m_pUi = CUi::Create(D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR3(700.0f, 80.0f, 0.0f), CUi::TYPE_PRESS_ENTER);
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		//チュートリアルの時
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
			m_pUi = CUi::Create(D3DXVECTOR3(950.0f, 670.0f, 0.0f), D3DXVECTOR3(480.0f, 60.0f, 0.0f), CUi::TYPE_PRESS_ENTER);
		}
		break;
		//ゲームの時
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
		break;
		//ゲームの時
	case MODE_GAMEOVER:
		if (m_pGame == NULL)
		{
			m_pGameover = CGameover::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		//リザルトの時
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
	}
}
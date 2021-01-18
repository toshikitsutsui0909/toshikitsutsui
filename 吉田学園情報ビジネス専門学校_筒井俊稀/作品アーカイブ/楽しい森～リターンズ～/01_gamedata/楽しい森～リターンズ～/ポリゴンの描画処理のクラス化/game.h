//------------------------------------------
//
//	背景の処理[bullet.h]
//	筒井
//
//------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CScore;
class CPlayer;
class CLife;
class CTrackingplayer;
class CUi;
class CSound;
//------------------------------------------
//	背景のクラス
//------------------------------------------
class CGame : public CScene
{
public:
	//ゲーム状態
	typedef enum
	{

		GAMESTATE_NONE = 0,//何もしていない状態
		GAMESTATE_NORMAL,  //通常状態
		GAMESTATE_END,	   //ゲーム終了状態（画面移開始待ち状態）
		GAMESTATE_CLEAR,   //クリア状態
		GAMESTATE_MAX

	}GAMESTATE;

	//敵の出し方設定
	typedef enum
	{
		ENEMYSTATE_1 = 0,
		ENEMYSTATE_2,
		ENEMYSTATE_3,
		ENEMYSTATE_4,
		ENEMYSTATE_5,
		ENEMYSTATE_6,
		ENEMYSTATE_7,
		ENEMYSTATE_8,
		ENEMYSTATE_9,
		ENEMYSTATE_10,
		ENEMYSTATE_11,
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	//メンバ関数宣言
	CGame();
	~CGame();
	static CGame *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void InitVariable(void);
	//各情報取得と設定
	static void SetGameState(GAMESTATE state);
	static GAMESTATE GetGameState(void);
	static void SetEnemyState(ENEMYSTATE state);
	static ENEMYSTATE GetEnemyState(void);
	static CScore *GetScore(void) { return m_pScore; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CLife *GetLife(void) { return m_pLife; }
	static CUi *GetUi(void) { return m_pUi; }
	static CSound *GetSound(void) { return m_pSound; }
private:
	static CScore *m_pScore;		//スコア情報
	static CLife *m_pLife;			//ライフ情報
	static CPlayer *m_pPlayer;		//プレイヤー情報
	static CUi *m_pUi;				//UI情報
	static CSound *m_pSound;		//サウンド情報
	static GAMESTATE m_gameState;	//ゲーム推移情報
	static ENEMYSTATE m_enemystate;	//敵情報
	static int m_nCount;			//
	int m_nEnemyCounter;			//
	int m_nCounterGameState;		//
	float m_fCountUi;				//
};

#endif // !_BG_H_#pragma once#pragma once

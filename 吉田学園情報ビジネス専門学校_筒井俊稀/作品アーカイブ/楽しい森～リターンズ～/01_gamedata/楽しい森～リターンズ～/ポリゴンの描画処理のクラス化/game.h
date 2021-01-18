//------------------------------------------
//
//	�w�i�̏���[bullet.h]
//	����
//
//------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CScore;
class CPlayer;
class CLife;
class CTrackingplayer;
class CUi;
class CSound;
//------------------------------------------
//	�w�i�̃N���X
//------------------------------------------
class CGame : public CScene
{
public:
	//�Q�[�����
	typedef enum
	{

		GAMESTATE_NONE = 0,//�������Ă��Ȃ����
		GAMESTATE_NORMAL,  //�ʏ���
		GAMESTATE_END,	   //�Q�[���I����ԁi��ʈڊJ�n�҂���ԁj
		GAMESTATE_CLEAR,   //�N���A���
		GAMESTATE_MAX

	}GAMESTATE;

	//�G�̏o�����ݒ�
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

	//�����o�֐��錾
	CGame();
	~CGame();
	static CGame *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void InitVariable(void);
	//�e���擾�Ɛݒ�
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
	static CScore *m_pScore;		//�X�R�A���
	static CLife *m_pLife;			//���C�t���
	static CPlayer *m_pPlayer;		//�v���C���[���
	static CUi *m_pUi;				//UI���
	static CSound *m_pSound;		//�T�E���h���
	static GAMESTATE m_gameState;	//�Q�[�����ڏ��
	static ENEMYSTATE m_enemystate;	//�G���
	static int m_nCount;			//
	int m_nEnemyCounter;			//
	int m_nCounterGameState;		//
	float m_fCountUi;				//
};

#endif // !_BG_H_#pragma once#pragma once

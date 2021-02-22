//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �g�V�L
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
// �}�N����`
//=============================================================================
#define GAME_COUNT 60

#define WARNING_POS_X 640.0f	//���[�j���O��X���W
#define WARNING_POS_Y 330.0f	//���[�j���O��Y���W
#define WARNING_SIZE_X 700.0f	//�T�C�YX
#define WARNING_SIZE_Y 200.0f	//�T�C�YY

#define ENEMY_POS_X_1 1500.0f	//�O
#define ENEMY_POS_X_2 1600.0f	//��Ԗ�
#define ENEMY_POS_X_3 1700.0f	//�O�Ԗ�
#define ENEMY_POS_X_4 1800.0f	//�l�Ԗ�
#define ENEMY_POS_X_5 1900.0f	//�Ō�

#define ENEMY_POS_Y_1 200.0f	//��
#define ENEMY_POS_Y_2 450.0f	//��
#define ENEMY_POS_Y_3 300.0f	//�^��

//=============================================================================
// �ÓI�����o�ϐ��錾
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
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	//������
	m_nEnemyCounter = 0;
	m_nCounterGameState = 0;
	m_fCountUi = 1000.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ��������
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
// ����������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���@�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 620.0f, 0.0f));
	//����UI�̕\���̐����i�X�R�A�Ǝ��@�̎c�@�������Ă���Ƃ���j
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 720.0f, 0.0f), D3DXVECTOR3(1280.0f, 250.0f, 0.0f),CUi::TYPE_DOWNUI);
	//�`���[�W�̐�������
	CCharge::Create();
	//�Q�[�W�o�[�̐�������
	CGaugeber::Create(D3DXVECTOR3(590.0f,635.0f,0.0f), D3DXVECTOR3(490.0f, 25.0f, 0.0f));
	//���@�̎c�@�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(145.0f, 625.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	CUi::Create(D3DXVECTOR3(60.0f, 620.0f, 0.0f), D3DXVECTOR3(120.0f, 50.0f, 0.0f), CUi::TYPE_LIFE);
	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(550.0f, 0.0f, 0.0f), D3DXVECTOR3(NUMBER_SIZE, NUMBER_SIZE, 0.0f));
	//�ÓI�����o�ϐ��錾�̏�����
	InitVariable();

	m_pSound = CManager::GetSound();
	m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
	//�Q�[���X�e�[�g������
	m_gameState = GAMESTATE_NONE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{	
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	D3DXVECTOR3 pos = m_pPlayer->GetPosition();
	CFade *pFade;

	m_nEnemyCounter++;

	switch (m_gameState)
	{
		//�v���C���[�����񂾂Ƃ�
	case GAMESTATE_NORMAL:
		m_nCounterGameState++;
		if (m_nCounterGameState >= GAME_COUNT)
		{
			m_nCount++;
			if (m_pPlayer != NULL && m_nCount != 3)
			{
				//�v���C���[����
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
				m_nCounterGameState = 0;
				SetGameState(GAMESTATE_NONE);
			}
		}
		if (m_nCount == 3)
		{
			//�c�@0�ŏI��
			SetGameState(GAMESTATE_END);
			m_nCount = 0;
		}
		break;
		//�Q�[���I�[�o�[
	case GAMESTATE_END:
		m_nCounterGameState++;
		pFade = CManager::GetFade();
		if (m_nCounterGameState >= GAME_COUNT)
		{
			//��ʃ��[�h�̐ݒ�
			pFade->SetFade(CManager::MODE_GAMEOVER);
			SetEnemyState(ENEMYSTATE_1);
		}
		break;
		//�Q�[���N���A
	case GAMESTATE_CLEAR:
		m_pPlayer->SetPlayer(false);
		pFade = CManager::GetFade();
		m_nCounterGameState++;
		if (m_nCounterGameState >= GAME_COUNT)
		{
			//��ʃ��[�h�̐ݒ�
			pFade->SetFade(CManager::MODE_RESULT);
			SetEnemyState(ENEMYSTATE_1);
		}
		break;
	}

	//�G�̏o��
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
		//�{�X�G���o��������i���������j
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
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
void CGame::InitVariable(void)
{
	m_nCount = 0;
}

//=============================================================================
// �Q�[���X�e�[�g��ݒ�
//=============================================================================
void CGame::SetGameState(GAMESTATE state)
{
	m_gameState = state;
}

//=============================================================================
// �Q�[���X�e�[�g���擾
//=============================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_gameState;
}

//=============================================================================
// �G�l�~�[�̐ݒ�
//=============================================================================
void CGame::SetEnemyState(ENEMYSTATE state)
{
	m_enemystate = state;
}

//=============================================================================
// �G�l�~�[�����擾
//=============================================================================
CGame::ENEMYSTATE CGame::GetEnemyState(void)
{
	return m_enemystate;
}

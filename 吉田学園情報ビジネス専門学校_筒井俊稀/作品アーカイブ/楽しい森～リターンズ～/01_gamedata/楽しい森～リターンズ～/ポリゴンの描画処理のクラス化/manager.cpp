//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : ���� �r�H
//
//=============================================================================
//=============================================================================
//	�C���N���[�h�t�@�C��
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
//		�ÓI�����o�ϐ��̏�����
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
//		�R���X�g���N�^
//-----------------------------------------------------------------------------
CManager::CManager()
{
}

//-----------------------------------------------------------------------------
//		�f�X�g���N�^
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
//		����������
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_�����O�N���X�𐶐�
	m_pRenderer = new CRenderer;
	// ����������
	m_pRenderer->Init(hWnd, bWindow);

	//���͏����𐶐�
	m_pInputKeyBoard = new CInputKeyBoard;
	// ����������
	m_pInputKeyBoard->Init(hInstance, hWnd);

	//�T�E���h�����𐶐�
	m_pSound = new CSound;
	// ����������
	m_pSound->Init(hWnd);


	//�e�e�N�X�`�����[�h����
	//�v���C���[�̃e�N�X�`�����[�h
	CPlayer::Load();
	//���̃e�N�X�`�����[�h
	CBullet::Load();
	//�G�̃e�N�X�`�����[�h
	CEnemy::Load();
	//�e�̔����̃e�N�X�`�����[�h
	CExplosion::Load();
	//�e�̔����̃e�N�X�`�����[�h
	CBg::Load();
	//�����̃e�N�X�`�����[�h
	CNumber::Load();
	//UI�̃e�N�X�`�����[�h
	CUi::Load();
	//�`���[�g���A���̃e�N�X�`�����[�h
	CTutorial::Load();
	//���U���g�̃e�N�X�`�����[�h
	CResult::Load();
	//�Q�[�W�o�[�̃e�N�X�`�����[�h
	CGaugeber::Load();
	//�Q�[���I�[�o�[�̃e�N�X�`�����[�h
	CGameover::Load();
	//�^�C�g���̃e�N�X�`�����[�h
	CTitle::Load();
	m_pFade = CFade::Create();

	return S_OK;
 }

//-----------------------------------------------------------------------------
//		�I������
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//�e�e�N�X�`���j������
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
		// �I������
		m_pSound->Uninit();
		//�����������
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pInputKeyBoard != NULL)
	{
		// �I������
		m_pInputKeyBoard->Uninit();
		//�����������
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�����������
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-----------------------------------------------------------------------------
//		�X�V����
//-----------------------------------------------------------------------------
void CManager::Updata(void)
{
	// �X�V����
	m_pInputKeyBoard->Update();

	if (m_pRenderer != NULL)
	{
		// �X�V����
		m_pRenderer->Update();
	}

	//�X�V���[�h
	switch (m_mode)
	{
		//�^�C�g���̎�
	case MODE_TITLE:
		//�G���^�[�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//�T�E���h�����ƃ��[�h�ڍs
			m_pSound->Play(CSound::SOUND_LABEL_SE_ENTER);
			m_pFade->SetFade(MODE_TUTORIAL);
		}
		break;
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:
		//�G���^�[�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//�T�E���h�����ƃ��[�h�ڍs
			m_pSound->Play(CSound::SOUND_LABEL_SE_ENTER);
			m_pFade->SetFade(MODE_GAME);
		}
		break;
		//�Q�[���̎�
	case MODE_GAME:
		//P�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_P))
		{
			m_pScene->Pause(false);
		}
		//�G���^�[�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			m_pScene->Pause(true);
		}
		break;
		//�Q�[���I�[�o�[�̎�
	case MODE_GAMEOVER:
		//�G���^�[�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//���[�h�ڍs
			m_pFade->SetFade(MODE_RESULT);
		}
		break;
		//���U���g�̎�
	case MODE_RESULT:
		//�G���^�[�L�[�������ꂽ��
		if (m_pInputKeyBoard->GetKeyTregger(DIK_RETURN))
		{
			//���[�h�ڍs
			m_pFade->SetFade(MODE_TITLE);
		}
		break;
	}
}

//-----------------------------------------------------------------------------
//		�`�揈��
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}

	//�`�惂�[�h
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
//		���[�h��ݒ�
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//�������ƏI���̃��[�h����
	switch (m_mode)
	{
		//�^�C�g���̎�
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
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
			m_pSound->Stop();
		}
		break;
		//�Q�[���̎�
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			CScene::ReleaseAllFade();
			m_pGame = NULL;
			m_pSound->Stop();
		}
		break;
		//�Q�[���I�[�o�[�̎�
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			m_pGameover->Uninit();
			m_pGameover = NULL;
			m_pSound->Stop();
		}
		break;
		//���U���g�̎�
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
			m_pSound->Stop();
		}
		break;
	}
	//mode�ϐ��Ɍ��݂̃��[�h������
	m_mode = mode;

	switch (mode)
	{
		//�^�C�g���̎�
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
			m_pUi = CUi::Create(D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR3(700.0f, 80.0f, 0.0f), CUi::TYPE_PRESS_ENTER);
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
			m_pUi = CUi::Create(D3DXVECTOR3(950.0f, 670.0f, 0.0f), D3DXVECTOR3(480.0f, 60.0f, 0.0f), CUi::TYPE_PRESS_ENTER);
		}
		break;
		//�Q�[���̎�
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
		break;
		//�Q�[���̎�
	case MODE_GAMEOVER:
		if (m_pGame == NULL)
		{
			m_pGameover = CGameover::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		//���U���g�̎�
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
	}
}
//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �g�V�L
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
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
//	�}�N����`
//-----------------------------------------------------------------------------
#define TEXTURE_PLAYER "data/texture/player1.png"	//�v���C���[�e�N�X�`��

#define PLAYER_LIFE_MAX 3							//�c�@��
#define PLAYER_LIFE_NUM 1							//���C�t
#define PLAYER_LIFE_DECREASE 1						//�c�@���鐔
#define PLAYER_DIE_POINT 5000						//����|�C���g��

#define CBULLET_COUNT 60							//�`���[�W�e�����܂鎞�Ԃ̃J�E���g�l
#define BULLET_SPEED 8.0f							//�e�̃X�s�[�h
#define CBULLET_SPEED 12.0f							//�`���[�W�e�̃X�s�[�h


//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;


//-----------------------------------------------------------------------------
//	�v���C���[�̃R���X�g���N�^
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
//	�v���C���[�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
//	�v���C���[�̐�������
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
//	�v���C���[�̏���������
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2d::Init(pos,size);
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);
	CScene2d::BindTexture(m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�v���C���[�̏I������
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	�v���C���[�̍X�V����
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{
	//VERTEX_2D *pVtx; //���_���ւ̃|�C���^
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
		//��
		if (pInputKeyBoard->GetKeyPress(DIK_W) == true)
		{
			m_pos.y -= MOVE_SPEED;

		}
		//��
		if (pInputKeyBoard->GetKeyPress(DIK_S) == true)
		{
			m_pos.y += MOVE_SPEED;

		}
		//��
		if (pInputKeyBoard->GetKeyPress(DIK_A) == true)
		{
			m_pos.x -= MOVE_SPEED;

		}
		//�E
		if (pInputKeyBoard->GetKeyPress(DIK_D) == true)
		{
			m_pos.x += MOVE_SPEED;

		}

		//��ʂ̒[�̓����蔻��
		//��
		//��
		if (m_pos.x - PLAYER_SIZE_X / 2 <= 0)
		{
			m_pos.x = 0.0f + PLAYER_SIZE_X / 2;
		}
		//�E
		if (m_pos.x + PLAYER_SIZE_X / 2 >= SCREEN_WIDTH)
		{
			m_pos.x = SCREEN_WIDTH - PLAYER_SIZE_X / 2;
		}

		//�c
		//��
		if (m_pos.y - PLAYER_SIZE_Y / 2 <= 75.0f)
		{
			m_pos.y = 75.0f + PLAYER_SIZE_Y / 2;
		}
		//��
		if (m_pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - 190.0f)
		{
			m_pos.y = (SCREEN_HEIGHT - 190.0f) - PLAYER_SIZE_Y / 2;
		}



		//����
		//�������Ŕ���
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
			//�`���[�W�e
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			CChargeBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE_PLAYER_X * 2, BULLET_SIZE_PLAYER_Y * 2,
				0.0f), D3DXVECTOR3(CBULLET_SPEED, 0.0f, 0.0f), CBullet::BULLETTYPE_PLAYER);
			m_nChageCount = 0;
			CCharge::Set();
		}
		else if (pInputKeyBoard->GetKeyRelease(DIK_SPACE) && m_nChageCount < CBULLET_COUNT)
		{
			//�ʏ�e
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
			CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZE_PLAYER_X, BULLET_SIZE_PLAYER_Y, 0.0f), D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f), CBullet::BULLETTYPE_PLAYER);
			m_nChageCount = 0;
			CCharge::Set();
		}
	}

	SetPos(m_pos);
}

//-----------------------------------------------------------------------------
//	�v���C���[�̕`�揈��
//-----------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	���@�̃_���[�W
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
			//�����̐���
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			//���@�̎c�@���[������Ȃ������@�𐶐�����
			pGame->SetGameState(CGame::GAMESTATE_NORMAL);
			//���@�̔j��
			Uninit();
		}
	}
}

//-----------------------------------------------------------------------------
//	�v���C���[�̏��̐ݒ�
//-----------------------------------------------------------------------------
void CPlayer::SetPlayer(bool bPlaying)
{
	m_bPlaying = bPlaying;
}

//-----------------------------------------------------------------------------
//	�v���C���[�̃e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�v���C���[�̃e�N�X�`���j���̏���
//-----------------------------------------------------------------------------
void CPlayer::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
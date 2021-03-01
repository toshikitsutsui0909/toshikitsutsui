//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : ���� �r�H
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
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
//	�}�N����`
//-----------------------------------------------------------------------------
#define TEXTURE_PATH_ENEMY_NORMAL	"data/texture/enemy1.png"	//NORMAL
#define TEXTURE_PATH_ENEMY_HARD		"data/texture/enemy2.png"	//HARD
#define TEXTURE_PATH_ENEMY_BOSS		"data/texture/boss1.png"	//boss
#define PATH_ENEMY_DATA				"data/file/enemydata.txt"

#define ENEMY_LIFE_NORMAL 1										//�ʏ�G�̗̑�
#define ENEMY_LIFE_HARD 3										//����G�̗̑�
#define ENEMY_LIFE_BOSS 300										//�{�X�̗̑�

#define ENEMY_MOVE_X -4.0f
#define ENEMY_MOVE_Y 1.0f

#define ENEMY_NORMAL_POINTUP 2000								//�ʏ�G��|�����Ƃ��̃|�C���g
#define ENEMY_HARD_POINTUP 6000									//����G��|�����Ƃ��̃|�C���g
#define ENEMY_BOSS_POINTUP 250000								//�{�X��|�����Ƃ��̃|�C���g

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[ENEMYTYPE::TYPE_MAX] = {};
//-----------------------------------------------------------------------------
//	�G�̃R���X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	//�e�ϐ��̏�����
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
//	�G�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::~CEnemy()
{
}

//-----------------------------------------------------------------------------
//	�G�̃e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	FILE*pFile = NULL;

	//�e�N�X�`���̓ǂݍ���
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
//	�G�̃e�N�X�`���j������
//-----------------------------------------------------------------------------
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < ENEMYTYPE::TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	�G�̐�������
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
//	�G�̏���������
//-----------------------------------------------------------------------------
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type)
{
	CScene2d::Init(pos, size);
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
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
	//2D�|���S���̐���
	CScene2d::BindTexture(m_apTexture[m_type]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�G�̏I������
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
 	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	�G�̍X�V����
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	m_pos = GetPosition();

	CSound *pSound
		= CManager::GetSound();

	//�Q�[���̏����擾
	CGame *pGame = CManager::GetGame();

	m_nCount++;
	//�_���[�W�����������_�ł�����
	if (m_bDamege)
	{
		m_nCntCol++;
		CScene2d::SetColor(D3DXCOLOR(1, 0, 0, 1));
		//�J�E���g��5�s������_���[�W���������
		if (m_nCntCol >= 5)
		{
			CScene2d::SetColor(D3DXCOLOR(1, 1, 1, 1));
			m_nCntCol = 0;
			m_bDamege = false;
		}
	}
	//�G�̈ړ�
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
				//�����������̂����@�������ꍇ
				if (objtype == CScene::OBJTYPE_PLAYER)
				{
					D3DXVECTOR3 PosPlayer = ((CScene2d*)pScene)->GetPosition();
					D3DXVECTOR3 SizePlayer = ((CScene2d*)pScene)->GetSize();
					////�����蔻��
					if (PosPlayer.x + SizePlayer.x / 2 >= m_pos.x
						&& PosPlayer.x - SizePlayer.x / 2 <= m_pos.x
						&& PosPlayer.y + SizePlayer.y / 2 >= m_pos.y
						&& PosPlayer.y - SizePlayer.y / 2 <= m_pos.y)
					{
						((CPlayer*)pScene)->Hit(m_nDamage);
						return;
					}
					//�Q�[���X�e�[�g�̏�����
					//pGame->SetGameState(CGame::GAMESTATE_NONE);
				}
			}
		}
	}
	//�G�̎�ނ��Ƃ̐ݒ�i�ړ����e�j
	switch (m_type)
	{
	//�ʏ�̓G
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

	//�ʏ�̓G�Q
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

	//�ʏ�̓G�R
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

	//�ʏ�̓G�S
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

	//�ʏ�̓G�T
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

	//���̓G
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

	//�{�X�G
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

	//�G����ʊO�ɏo�����������
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
//	�G�̕`�揈��
//-----------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	�_���[�W
//-----------------------------------------------------------------------------
void CEnemy::Hit(int nDamage)
{
	//�Q�[���̏����擾
	CGame *pGame = CManager::GetGame();
	//���y���̎擾
	CSound *pSound = CManager::GetSound();

	//���C�t�̃����o�ϐ��Ƀ_���[�W�̏�����
	m_nLife -= nDamage;
	m_bDamege = true;

	//���C�t���[���ɂȂ������i���񂾂Ƃ��j
	if (m_nLife <= 0)
	{
		//m_type�̏���
		switch (m_type)
		{
		//�ʏ�̓G
		case TYPE_NORMAL:
			//�X�R�A100����
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//�ʏ�̓G�Q
		case TYPE_NORMAL_2:
			//�X�R�A100����
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//�ʏ�̓G�R
		case TYPE_NORMAL_3:
			//�X�R�A100����
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//�ʏ�̓G�S
		case TYPE_NORMAL_4:
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//�ʏ�̓G�T
		case TYPE_NORMAL_5:
			CGame::GetScore()->AddScore(ENEMY_NORMAL_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//���̓G
		case TYPE_HARDTYPE:
			CGame::GetScore()->AddScore(ENEMY_HARD_POINTUP);
			CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
			Uninit();
			break;

		//�{�X�G
		case TYPE_BOSS:
			if (m_pos.y + BOSS_SIZE / 2 >= SCREEN_HEIGHT - 170.0f)
			{
				pGame->GetPlayer()->SetPlayer(false);
				//�X�R�A500�����Z
				CGame::GetScore()->AddScore(ENEMY_BOSS_POINTUP);
				//�����̐���
				CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE * 10, EXPLOSION_SIZE * 10, 0.0f));
				//�����̉�
				pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
				//�N���A�Ɉڍs
				pGame->SetGameState(CGame::GAMESTATE_CLEAR);
				Uninit();
			}
			break;
		}
	}
}
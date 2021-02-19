//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : ���� �r�H
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
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
//	�}�N����`
//-----------------------------------------------------------------------------
#define NORMAL_DAMAGE_NUM 1												//�̗́iNORMAL�j
#define HARD_DAMAGE_NUM 3												//�̗́iHARD�j

#define TEXTURE_PATH_BULLET_PLAYER "data/texture/bullet100.png"			//�e�e�N�X�`��
#define TEXTURE_PATH_BULLET_ENEMY1 "data/texture/enemy_bullet000.png"	//�G�l�~�[�e�e�N�X�`��
#define TEXTURE_PATH_BULLET_ENEMY2 "data/texture/enemy_bullet001.png"	//�G�l�~�[�e�e�N�X�`��

#define BULLET_DIE_POINT_RIGHT 100.0f									//�e��������|�C���g�i�E�j
#define BULLET_DIE_POINT_LEFT 100.0f									//�e��������|�C���g�i���j
#define BULLET_DIE_POINT_UP 60.0f										//�e��������|�C���g�i��j
#define BULLET_DIE_POINT_DOWN 170.0f									//�e��������|�C���g�i���j

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[BULLETTYPE::BULLETTYPE_MAX] = {};
int CBullet::m_nCount = 0;
bool CBullet::m_bDamage = true;

//-----------------------------------------------------------------------------
//	�e�̃R���X�g���N�^
//-----------------------------------------------------------------------------
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	//�e�̏��̏�����
	m_BulletType = BULLETTYPE_NONE;
	m_nDamage = 0;
	m_move = D3DXVECTOR3();
}

//-----------------------------------------------------------------------------
//	�e�̃f�X�g���N�^
//-----------------------------------------------------------------------------
CBullet::~CBullet()
{
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_PLAYER, &m_apTexture[BULLETTYPE_PLAYER]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_ENEMY1, &m_apTexture[BULLETTYPE_ENEMY]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BULLET_ENEMY2, &m_apTexture[BULLETTYPE_ENEMY_2]);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
void CBullet::UnLoad(void)
{
	for (int nCount = BULLETTYPE_PLAYER; nCount < BULLETTYPE_MAX; nCount++)
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
//	�e�̐�������
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
//	�e�̏���������
//-----------------------------------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CScene2d::Init(pos,size);
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);
	m_move = move;
	m_BulletType = type;
	//�_���[�W��
	SetBullet(NORMAL_DAMAGE_NUM);
	CScene2d::BindTexture(m_apTexture[type]);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�̏I������
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	�e�̍X�V����
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	//pos�̕ϐ�
	D3DXVECTOR3 pos;
	//�e�̈ʒu�����擾
	pos = GetPosition();

	//�T�E���h�����擾
	CSound *pSound
	= CManager::GetSound();

	//�ړ������ɒl�𑫂�
	pos.x += m_move.x;
	pos.y += m_move.y;

	SetPos(pos);

	//�e�e�̏���
	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		//�e�e�̏���
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene = GetScene(nPriority, nCntScene);
			CGame *pGame = CManager::GetGame();
			if (pScene != NULL)
			{
				OBJTYPE objtype;
				objtype = pScene->GetObjType();

				//�v���C���[�̒e
				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					//�����������̂��G�������ꍇ
					if (objtype == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 PosEnemy = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizeEnemy = ((CScene2d*)pScene)->GetSize();
						////�����蔻��
						if (PosEnemy.x + SizeEnemy.x / 2 >= pos.x
							&& PosEnemy.x - SizeEnemy.x / 2 <= pos.x
							&& PosEnemy.y + SizeEnemy.y / 2 >= pos.y
							&& PosEnemy.y - SizeEnemy.y / 2 <= pos.y)
						{
							((CEnemy*)pScene)->Hit(m_nDamage);
							//�e�̔j��
							Uninit();
							return;
						}
					}
				}

				//�G�l�~�[�̒e
				if (m_BulletType == BULLETTYPE_ENEMY || m_BulletType == BULLETTYPE_ENEMY_2)
				{
					//�����������̂����@�������ꍇ
					if (objtype == OBJTYPE_PLAYER)
					{
						D3DXVECTOR3 PosPlayer = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizePlayer = ((CScene2d*)pScene)->GetSize();
						////�����蔻��
						if (PosPlayer.x + SizePlayer.x / 2 >= pos.x
							&& PosPlayer.x - SizePlayer.x / 2 <= pos.x
							&& PosPlayer.y + SizePlayer.y / 2 >= pos.y
							&& PosPlayer.y - SizePlayer.y / 2 <= pos.y)
						{
							((CPlayer*)pScene)->Hit(m_nDamage);
							//�e�̔j��
							Uninit();
							return;
						}
					}
					//�c�@���Ȃ��Ȃ�����G�̒e����
					if (pGame->GetGameState() == CGame::GAMESTATE_CLEAR || pGame->GetGameState() == CGame::GAMESTATE_END)
					{
						//�e�̔j��
						Uninit();
						return;
					}
				}
			}
		}
	}
	//���C�t���[���ɂȂ�����
	//�E
	if (pos.x + PLAYER_SIZE_X >= SCREEN_WIDTH + BULLET_DIE_POINT_RIGHT)
	{
		Uninit();
		return;
	}
	//��
	if (pos.x - PLAYER_SIZE_X <= -BULLET_DIE_POINT_LEFT)
	{
		Uninit();
		return;
	}
	//��
	if (pos.y - PLAYER_SIZE_Y / 2 <= BULLET_DIE_POINT_UP)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
	//��
	if (pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - BULLET_DIE_POINT_DOWN)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
}

//-----------------------------------------------------------------------------
//	�e�̕`�揈��
//-----------------------------------------------------------------------------
void CBullet::Draw(void)
{
	CScene2d::Draw();
}

//-----------------------------------------------------------------------------
//	�e�̍U���͂̐ݒ�
//-----------------------------------------------------------------------------
void CBullet::SetBullet(int nDamage)
{
  	m_nDamage = nDamage;
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
CChargeBullet::CChargeBullet()
{
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
CChargeBullet::~CChargeBullet()
{

}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
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
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
HRESULT CChargeBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance)
{
	CBullet::Init(pos, size, move, type, distance);
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_CBULLET);
	m_move = move;
	m_BulletType = type;
	//�_���[�W��
 	SetBullet(HARD_DAMAGE_NUM);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
void CChargeBullet::Uninit(void)
{
	CBullet::Uninit();
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
void CChargeBullet::Update(void)
{
	D3DXVECTOR3 pos;
	pos = GetPosition();

	CSound *pSound
		= CManager::GetSound();

	//�ړ������ɒl�𑫂�
	pos.x += m_move.x;
	pos.y += m_move.y;

	SetPos(pos);

	for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		//�e�e�̏���
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene = GetScene(nPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objtype;
				objtype = pScene->GetObjType();

				//�v���C���[�̒e
				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					//�����������̂��G�������ꍇ
					if (objtype == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 PosEnemy = ((CScene2d*)pScene)->GetPosition();
						D3DXVECTOR3 SizeEnemy = ((CScene2d*)pScene)->GetSize();
						////�����蔻��
						if (PosEnemy.x + SizeEnemy.x / 2 >= pos.x
							&& PosEnemy.x - SizeEnemy.x / 2 <= pos.x
							&& PosEnemy.y + SizeEnemy.y / 2 >= pos.y
							&& PosEnemy.y - SizeEnemy.y / 2 <= pos.y)
						{
							((CEnemy*)pScene)->Hit(m_nDamage);
							//�����̐���
							pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

							return;
						}
					}
				}
			}
		}
	}
	//���C�t���[���ɂȂ�����
	//�E
	if (pos.x + PLAYER_SIZE_X >= SCREEN_WIDTH + BULLET_DIE_POINT_RIGHT)
	{
		Uninit();
		return;
	}
	//��
	if (pos.x - PLAYER_SIZE_X <= -BULLET_DIE_POINT_LEFT)
	{
		Uninit();
		return;
	}
	//��
	if (pos.y - PLAYER_SIZE_Y / 2 <= BULLET_DIE_POINT_UP)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
	//��
	if (pos.y + PLAYER_SIZE_Y / 2 >= SCREEN_HEIGHT - BULLET_DIE_POINT_DOWN)
	{
		CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f));
		Uninit();
		return;
	}
}

//-----------------------------------------------------------------------------
//	�e�̃e�N�X�`���̔j���̏���
//-----------------------------------------------------------------------------
void CChargeBullet::Draw(void)
{
	CScene2d::Draw();
}
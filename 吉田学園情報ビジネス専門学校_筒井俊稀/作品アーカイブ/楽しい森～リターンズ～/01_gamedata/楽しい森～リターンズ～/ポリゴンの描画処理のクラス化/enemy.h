//=============================================================================
//
// �G�̏��� [enemy.h]
// Author :	�g�V�L
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"
#include "main.h"

//=============================================================================
//	�O���錾
//=============================================================================
class CBullet;

//=============================================================================
//	�G�l�~�[�N���X�̍쐬�i�h���N���X�j
//=============================================================================
class CEnemy : public CScene2d
{
public:
	//�G�̃^�C�v
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,	// �ʏ�̓G
		TYPE_NORMAL_2,	// �ʏ�i�����Ⴂ�j
		TYPE_NORMAL_3,	// �ʏ�i�����Ⴂ�j
		TYPE_NORMAL_4,	// �ʏ�i�����Ⴂ�j
		TYPE_NORMAL_5,	// �ʏ�i�����Ⴂ�j
		TYPE_HARDTYPE,	// ���������G
		TYPE_BOSS,		// �{�X
		TYPE_MAX
	}ENEMYTYPE;

	//�����o�֐��錾
	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMYTYPE::TYPE_MAX];
	D3DXVECTOR3 m_pos;		//���W
	D3DXVECTOR3 m_size;		//�傫��
	D3DXVECTOR3 m_move;		//�ړ���
	ENEMYTYPE m_type;		//�G�^�C�v
	int m_nLife;			//�G�̑ϋv�l
	int m_nDamage;			//�_���[�W��
	int m_nCount;			//�G�̒e�̌��Ԋu
	float m_fSpeed;			//�ړ��X�s�[�h
	int m_nRandNumber;		//�e�̌��X�s�[�h�i�����Ǘ��j
	int m_Counter;			//�㉺�ړ��Ǘ�
	int m_nCntCol;			//�J���[�̕ύX
	bool m_bDamege;			//�_���[�W���
};



#endif //_ENEMY_H_
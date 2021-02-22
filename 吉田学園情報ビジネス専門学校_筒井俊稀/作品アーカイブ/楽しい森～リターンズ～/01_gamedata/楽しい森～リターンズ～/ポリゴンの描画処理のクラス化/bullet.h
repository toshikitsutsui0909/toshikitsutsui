//------------------------------------------
//
//	�e�̏���[bullet.h]
//	Author : ���� �r�H
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene2d.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CPlayer;

//------------------------------------------
//	�o���b�g�N���X
//------------------------------------------
class CBullet : public CScene2d
{
public:
	//�e�̎�ޕ���
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,		//�v���C���[�̒e
		BULLETTYPE_ENEMY,		//�G�̒e�P
		BULLETTYPE_ENEMY_2,		//�G�̒e�Q
		BULLETTYPE_MAX
	}BULLETTYPE;

	//�����o�֐��錾
	CBullet(int nPriority = OBJTYPE_BULLET);
	virtual ~CBullet();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3());
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetBullet(int nDamage);
	virtual D3DXVECTOR3 GetBullet(void) { return m_move; }
private:
	//�����o�ϐ��錾
	static int m_nCount;
protected:
	D3DXVECTOR3 m_move;						//�ړ���
	int m_nLife;							//�e�̈ړ��͈�
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLETTYPE::BULLETTYPE_MAX];//�e�N�X�`��
	BULLETTYPE m_BulletType;				//�e�̎��
	int m_nDamage;							//�e�̃_���[�W��
	static bool m_bDamage;					//�_���[�W��H�����������
};

//�`���[�W�e�N���X
class CChargeBullet : public CBullet
{
public:
	//�����o�֐��錾
	CChargeBullet();
	~CChargeBullet();
	static CChargeBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};


#endif // !_BULLET_H_

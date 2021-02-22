#pragma once
//------------------------------------------
//
//	�N���X�|���S���`��[player.h]
//	����
//
//------------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	�N���X
//-----------------------------------------------------------------------------
class CPlayer : public CScene2d
{
public:
	//�����o�֐��錾
	CPlayer(int nPriority = OBJTYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	void SetPlayer(bool bPlaying);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	//�����o�ϐ��錾
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	D3DXVECTOR3 m_pos;//���W
	D3DXVECTOR3 m_size;//�傫��
	int m_nChageCount;//�`���[�W�J�E���g
	int m_Count;//
	int m_nCntBullet;//�o���b�g�̌��Ԋu
	bool m_bPlaying;//�v���C���[���g���Ă��邩
	bool m_bIsDamage;//�_���[�W��H�������
	int m_nLife;//�v���C���[�̗�
	int m_nCountLife;//�c�@
};

#endif

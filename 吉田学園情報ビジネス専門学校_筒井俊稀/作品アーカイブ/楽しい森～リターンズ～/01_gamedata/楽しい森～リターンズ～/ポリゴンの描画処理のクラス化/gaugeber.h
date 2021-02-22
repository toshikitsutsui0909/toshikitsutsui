//------------------------------------------
//
//	�N���X�|���S���`��[player.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _GAUGEBER_H_
#define _GAUGEBER_H_

//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	�N���X
//-----------------------------------------------------------------------------
class CGaugeber : public CScene2d
{
public:
	//�����o�֐��錾
	CGaugeber(int nPriority = OBJTYPE_GAUGEBER);
	~CGaugeber();

	static CGaugeber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	//�����o�ϐ��錾
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	D3DXVECTOR3 m_pos;//���W
	D3DXVECTOR3 m_size;//�傫��
};

#endif

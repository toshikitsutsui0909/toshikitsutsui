//-------------------------------------
//
//	�t�F�[�h����[fade.h]
//	����
//
//-------------------------------------

//��d�C���N���[�h�h�~
#ifndef _FADE_H_
#define _FADE_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "manager.h"

//------------------------------------------
//	�t�F�[�h�̃N���X
//------------------------------------------
class CFade : public CScene
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,		//�t�F�[�h�C��
		FADE_OUT,		//�t�F�[�h�A�E�g
		FADE_MAX
	}FADE;

	//�����o�֐��錾
	CFade(int nPriority = OBJTYPE_FADE);
	~CFade();
	static CFade *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManager::MODE mode);
private:
	//�����o�ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//�o�b�t�@
	D3DXVECTOR3 m_pos;		//���W
	D3DXVECTOR3 m_size;		//�傫��
	FADE m_fade;			//�t�F�[�h�^�C�v
	D3DXCOLOR m_ColorFade;	//�F�̐ݒ�
	CManager::MODE m_mode;	//���[�h�ڍs���
};



#endif // !_FADE_H_

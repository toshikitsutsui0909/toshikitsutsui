//------------------------------------------
//
//	�Q�[�W�̏���[gauge.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _GAUGE_H_
#define _GAUGE_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"

//------------------------------------------
//	�Q�[�W�N���X
//------------------------------------------
class CGauge
{
public:
	//�����o�֐��錾
	CGauge();
	~CGauge();

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNum(int nNum);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
private:
	//�����o�ϐ��錾
	static LPDIRECT3DTEXTURE9	m_pTexture;//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;//���_�o�b�t�@
	D3DXVECTOR3					m_pos;	   //���W
	D3DXVECTOR3					m_size;	   //�傫��
	int							m_nNum;	   //�Q�[�W��

};

#endif // !_GAUGE_H_

//------------------------------------------
//
//	�w�i�̏���[bg.h]
//	Author : ���� �r�H
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _BG_H_
#define _BG_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CScene2d;

//------------------------------------------
//	�w�i�̃N���X
//------------------------------------------
class CBg : public CScene
{
public:
	//�����o�֐��錾
	CBg(int nPriority = OBJTYPE_NONE);
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	//�����o�ϐ��錾
	float m_fSpeedFast;								//�w�i�ړ��X�s�[�h
	float m_fSpeedSecond;							//�w�i�ړ��X�s�[�h
	float m_fSpeedThird;							//�w�i�ړ��X�s�[�h
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];	//�e�N�X�`��
	CScene2d *m_apScene2d[MAX_BG];					//Scene���
	D3DXVECTOR3 m_pos;								//���W
	D3DXVECTOR3 m_size;								//�傫��
};

#endif // !_BG_H_

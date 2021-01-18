//------------------------------------------
//
//	�w�i�̏���[bullet.h]
//	����
//
//------------------------------------------
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CPolygon;
class CRanking;
//------------------------------------------
//	�w�i�̃N���X
//------------------------------------------
class CGameover : public CScene
{
public:
	//�����o�֐��錾
	CGameover();
	~CGameover();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CGameover *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	//�����o�ϐ��錾
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;//���W
	D3DXVECTOR3 m_size;//�傫��
};

#endif // !_BG_H_

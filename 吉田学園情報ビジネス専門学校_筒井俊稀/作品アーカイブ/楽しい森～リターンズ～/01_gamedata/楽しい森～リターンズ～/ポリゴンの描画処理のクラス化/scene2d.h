//------------------------------------------
//
//	�N���X�|���S���`��[scene2d.h]
//	����
//
//------------------------------------------

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include"main.h"
#include"scene.h"

//------------------------------------------
//	scene2d�N���X
//------------------------------------------
class CScene2d : public CScene
{
public:
	typedef enum
	{
		FLASH_STATE_NONE=0,
		FLASH_STATE_IN,
		FLASH_STATE_OUT,
		FLASH_STATE_MAX
	}FLASH_STATE;
	CScene2d(int nPriority = OBJTYPE_NONE);
	~CScene2d();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetTex(D3DXVECTOR2* tex);
	void SetColor(D3DXCOLOR col);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//Bind�@���蓖�Ă�
	void Flashing(void);
	static CScene2d *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_size;
	D3DXVECTOR2				m_Texture;
	D3DXCOLOR				m_col;
	bool					m_bFlash;
	FLASH_STATE m_FlashState;
};


#endif //_SCENE2D_H_
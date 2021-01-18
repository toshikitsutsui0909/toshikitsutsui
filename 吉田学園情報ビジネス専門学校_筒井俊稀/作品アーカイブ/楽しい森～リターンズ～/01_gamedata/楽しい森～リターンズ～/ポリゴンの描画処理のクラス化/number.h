//------------------------------------------
//
//	�N���X�|���S���`��[player.h]
//	����
//
//------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"

//------------------------------------------
//	�N���X
//------------------------------------------
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Updata(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetPosition(void) { return m_Pos; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//�o�b�t�@
	D3DXVECTOR3				m_Pos;		//���W
	D3DXVECTOR3				m_Size;		//�傫��
	D3DXCOLOR				m_col;		//�J���[
};

#endif // !_NUMBER_H_

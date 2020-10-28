//------------------------------------------
//
//	�w�i�̏���[bullet.h]
//	����
//
//------------------------------------------
#ifndef _BG_H_
#define _BG_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "main.h"

class CScene2d;
//------------------------------------------
//	�w�i�̃N���X
//------------------------------------------
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	float m_fSpeed0;
	float m_fSpeed1;
	float m_fSpeed2;
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];
	CScene2d *m_apScene2d[MAX_BG];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif // !_BG_H_

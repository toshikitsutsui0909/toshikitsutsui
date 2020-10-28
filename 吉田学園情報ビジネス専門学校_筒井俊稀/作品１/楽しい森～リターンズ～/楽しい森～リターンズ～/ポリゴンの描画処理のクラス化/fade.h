//-------------------------------------
//
//	フェード処理[fade.h]
//	筒井
//
//-------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#include "scene.h"
#include "manager.h"

class CFade : public CScene
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade(int nPriority = 14);
	~CFade();
	static CFade *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManager::MODE mode);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	FADE m_fade;
	D3DXCOLOR m_ColorFade;
	CManager::MODE m_mode;
};



#endif // !_FADE_H_

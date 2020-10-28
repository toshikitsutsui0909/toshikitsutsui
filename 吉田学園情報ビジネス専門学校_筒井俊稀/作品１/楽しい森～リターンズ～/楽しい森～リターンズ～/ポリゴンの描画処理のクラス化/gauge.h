#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

class CGauge
{
public:
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
	static LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	D3DXVECTOR3					m_pos;
	D3DXVECTOR3					m_size;
	int							m_nNum;

};

#endif // !_GAUGE_H_

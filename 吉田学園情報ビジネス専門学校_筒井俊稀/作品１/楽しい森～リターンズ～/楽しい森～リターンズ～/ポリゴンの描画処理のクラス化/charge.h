#ifndef _CHARG_H_
#define _CHARG_H_

#include "scene.h"

class CGauge;

class CCharge : public CScene
{
public:
	CCharge(int nPriority = 12);
	~CCharge();

	static CCharge *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Add(void);
	static void Set(void);
private:
	static CGauge *m_pGauge;
	static int m_nCount;
};


#endif // !_CHARG_H_

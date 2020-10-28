//------------------------------------------
//
//	�N���X�|���S���`��[scene2d.h]
//	����
//
//------------------------------------------

#ifndef _LIFE_H_
#define _LIFE_H_

#include "scene.h"
#include "main.h"

class CNumber;

//------------------------------------------
//	�N���X
//------------------------------------------
class CLife : public CScene
{
public:
	CLife(int nPriority = 4);
	~CLife();

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SubtractLife(int nLife);
	int GetLife(void);
private:
	CNumber *m_pNumber;
	int m_nLife;
};




#endif
//------------------------------------------
//
//	�N���X�|���S���`��[scene2d.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _LIFE_H_
#define _LIFE_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CNumber;

//------------------------------------------
//	�N���X
//------------------------------------------
class CLife : public CScene
{
public:
	//�����o�֐��錾
	CLife(int nPriority = OBJTYPE_LIFE);
	~CLife();

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SubtractLife(int nLife);
	int GetLife(void);
private:
	//�����o�ϐ��錾
	CNumber *m_pNumber;
	int m_nLife;
};




#endif
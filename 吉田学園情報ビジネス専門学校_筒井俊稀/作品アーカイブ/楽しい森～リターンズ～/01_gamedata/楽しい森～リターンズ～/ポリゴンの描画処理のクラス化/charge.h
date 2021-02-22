//------------------------------------------
//
//	�`���[�W�Q�[�W�̏���[charg.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _CHARG_H_
#define _CHARG_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "scene.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CGauge;

//------------------------------------------
//	�`���[�W�Q�[�W�̃N���X
//------------------------------------------
class CCharge : public CScene
{
public:
	//�����o�֐��錾
	CCharge(int nPriority = OBJTYPE_CHARGE);
	~CCharge();

	static CCharge *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Add(void);
	static void Set(void);
private:
	//�����o�ϐ��錾
	static CGauge *m_pGauge;	//�Q�[�W���
	static int m_nCount;		//�Q�[�W�ʃJ�E���g
};


#endif // !_CHARG_H_

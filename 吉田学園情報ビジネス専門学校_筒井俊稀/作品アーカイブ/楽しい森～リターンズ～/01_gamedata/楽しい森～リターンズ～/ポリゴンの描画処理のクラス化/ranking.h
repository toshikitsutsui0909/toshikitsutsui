//------------------------------------------
//
//	�����L���O�̏���[ranking.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _RANKING_H_
#define _RANKING_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------
//	�O���錾
//------------------------------------------
class CNumber;

//------------------------------------------
//	�����L���O�N���X
//------------------------------------------
class CRanking : public CScene
{
public:
	CRanking();
	~CRanking();

	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber *m_apNumber[MAX_NUMBER][MAX_RANKING];//�i���o�[���
	int m_anRankingDate[MAX_RANKING];			//�����L���O���
	int m_nCount;								//
	int m_nRank;								//
};

#endif // !_RANKING_H_

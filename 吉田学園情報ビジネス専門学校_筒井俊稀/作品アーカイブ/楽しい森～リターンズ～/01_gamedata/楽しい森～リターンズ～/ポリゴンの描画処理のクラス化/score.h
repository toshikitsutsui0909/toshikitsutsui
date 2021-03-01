//------------------------------------------
//
//	�N���X�|���S���`��[scene2d.h]
//	����
//
//------------------------------------------

#ifndef _SCORE_H_
#define _SCORE_H_

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
class CScore : public CScene
{
public:
	CScore(int nPriority = OBJTYPE_SCORE);
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	static int GetScore(int nCount);
	void ReadFile(void);
	void WriteFile(void);
	int SaveScore(void);
private:
	CNumber *m_apNumber[MAX_NUMBER];
	int m_nScore;
	static int m_nRankingScore[MAX_RANKING];
	float m_fSize;
};




#endif
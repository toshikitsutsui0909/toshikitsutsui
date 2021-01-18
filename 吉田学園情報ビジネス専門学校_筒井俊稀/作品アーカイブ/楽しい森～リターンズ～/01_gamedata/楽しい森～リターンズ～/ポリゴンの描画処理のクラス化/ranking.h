//------------------------------------------
//
//	ランキングの処理[ranking.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _RANKING_H_
#define _RANKING_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CNumber;

//------------------------------------------
//	ランキングクラス
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
	CNumber *m_apNumber[MAX_NUMBER][MAX_RANKING];//ナンバー情報
	int m_anRankingDate[MAX_RANKING];			//ランキング情報
	int m_nCount;								//
	int m_nRank;								//
};

#endif // !_RANKING_H_

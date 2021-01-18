//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : トシキ
//
//=============================================================================
#include "ranking.h"
#include "number.h"
#include "score.h"
#include "game.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	for (int nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCntNumber][nCntRanking] = NULL;
		}
	}
	memset(m_anRankingDate, 0, sizeof(m_anRankingDate));
	m_nCount = 0;
	m_nRank = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CRanking *pRanking;
	pRanking = new CRanking;
	if (pRanking != NULL)
	{
		pRanking->Init(pos, size);
	}
	return pRanking;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore = CGame::GetScore();
	m_nRank = pScore->SaveScore();

	for (int nCount1 = 0; nCount1 < MAX_RANKING; nCount1++)
	{
		m_anRankingDate[nCount1] = CScore::GetScore(nCount1);

		for (int nCount2 = 0; nCount2 < MAX_NUMBER; nCount2++)
		{
			int nValue = (int)powf(10.0f, (float)MAX_NUMBER - (float)nCount2);
			int nScore2 = (int)powf(10.0f, (float)MAX_NUMBER - (float)nCount2 - 1.0f);
			int nAnswer = (m_anRankingDate[nCount1] % nValue) / nScore2;
			m_apNumber[nCount2][nCount1] = CNumber::Create(D3DXVECTOR3(pos.x + (size.x * nCount2), pos.y + ((size.y + 50.0f) * nCount1), 0.0f), size);
			m_apNumber[nCount2][nCount1]->SetNumber(nAnswer);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	for (int nCount1 = 0; nCount1 < MAX_RANKING; nCount1++)
	{
		for (int nCount2 = 0; nCount2 < MAX_NUMBER; nCount2++)
		{
			m_apNumber[nCount2][nCount1]->Uninit();
			delete m_apNumber[nCount2][nCount1];
			m_apNumber[nCount2][nCount1] = NULL;
		}
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	m_nCount++;
	for (int nCount1 = 0; nCount1 < MAX_RANKING; nCount1++)
	{
		for (int nCount2 = 0; nCount2 < MAX_NUMBER; nCount2++)
		{
			m_apNumber[nCount2][nCount1]->Updata();

			if (m_nRank < MAX_RANKING)
			{

				for (int nCount2 = 0; nCount2 < MAX_NUMBER; nCount2++)
				{
					if (m_nCount % 6 == 0)
					{
						m_apNumber[nCount2][m_nRank]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					}
					if (m_nCount % 12 == 0)
					{
						m_apNumber[nCount2][m_nRank]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCount1 = 0; nCount1 < MAX_RANKING; nCount1++)
	{
		for (int nCount2 = 0; nCount2 < MAX_NUMBER; nCount2++)
		{
			m_apNumber[nCount2][nCount1]->Draw();
		}
	}
}

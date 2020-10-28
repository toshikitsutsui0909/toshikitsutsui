//=============================================================================
//
// polygon処理 [scene2d.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "number.h"
#include "game.h"

int CScore::m_nRankingScore[MAX_RANKING] = {};
//=============================================================================
//	コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
	m_nScore = 0;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
//	生成処理
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore;
	pScore = new CScore;
	if (pScore != NULL)
	{
		pScore->Init(pos, size);
	}
	return pScore;
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + (size.x * nCount), 700.0f, 0.0f), size);
	}

	return S_OK;
}

//=============================================================================
//	終了処理　
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}

	Release();
}

//=============================================================================
//	更新処理
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
//	描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//	スコア加算する処理
//=============================================================================
void CScore::AddScore(int nValue)
{
	float fIndex;
	float fRadix = 10.0f;

   	m_nScore += nValue;
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}
	for (fIndex = 0; fIndex < MAX_NUMBER; fIndex++)
	{
		int nValue = (int)powf(fRadix, MAX_NUMBER - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_NUMBER - fIndex - 1);
		int nAnswer = (m_nScore % nValue) / nScore2;

		m_apNumber[(int)fIndex]->Updata();

 		m_apNumber[(int)fIndex]->SetNumber(nAnswer);
	}
}

//=============================================================================
//	スコアの取得
//=============================================================================
int CScore::GetScore(int nCount)
{
	return m_nRankingScore[nCount];
}

//=============================================================================
//	スコアの取得
//=============================================================================
void CScore::ReadFile(void)
{
	FILE * pFile;

	pFile = fopen("data/ranking/rankingdata.txt", "r");
	//NULLチェック
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fscanf(pFile, "%d", &m_nRankingScore[nCount]);
		}

		fclose(pFile);
	}
}

//=============================================================================
//	スコアの
//=============================================================================
void CScore::WriteFile(void)
{
	FILE * pFile = NULL;

	pFile = fopen("data/ranking/rankingdata.txt", "w");
	//NULLチェック
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", m_nRankingScore[nCount]);
		}
		fclose(pFile);
	}
}

//=============================================================================
//	スコアの保存
//=============================================================================
int CScore::SaveScore(void)
{
	int nCount;

	ReadFile();

	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//ランキングを更新する場所の判定
		if (m_nScore > m_nRankingScore[nCount])
		{
			//以降のランキングデータを後ろに移動
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				m_nRankingScore[nCntMove] = m_nRankingScore[nCntMove - 1];
			}
			m_nRankingScore[nCount] = m_nScore;

			break;
		}
	}
	WriteFile();

	return nCount;
}

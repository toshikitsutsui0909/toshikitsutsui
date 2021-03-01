//=============================================================================
//
// polygon���� [scene2d.cpp]
// Author : ���� �r�H
//
//=============================================================================
#include "score.h"
#include "number.h"
#include "game.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define RANKING_DATA_PATH "data/ranking/rankingdata.txt"	//�����L���O�e�L�X�g�p�X
#define NUMBER_POS 700.0f									//�i���o�[�̕\������Ԋu
#define NUMBER_RADIX 10.0f									//���f�B�b�N�X

//=============================================================================
//	�ÓI�����o�ϐ��錾������
//=============================================================================
int CScore::m_nRankingScore[MAX_RANKING] = {};

//=============================================================================
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
//	��������
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
//	����������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + ((size.x + m_fSize) * nCount), NUMBER_POS, 0.0f), size);
	}

	return S_OK;
}

//=============================================================================
//	�I�������@
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
//	�X�V����
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//	�X�R�A���Z���鏈��
//=============================================================================
void CScore::AddScore(int nValue)
{
	float fIndex;
	float fRadix = NUMBER_RADIX;

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
//	�X�R�A�̎擾
//=============================================================================
int CScore::GetScore(int nCount)
{
	return m_nRankingScore[nCount];
}

//=============================================================================
//	�X�R�A�̎擾
//=============================================================================
void CScore::ReadFile(void)
{
	FILE * pFile = NULL;

	pFile = fopen(RANKING_DATA_PATH, "r");
	//NULL�`�F�b�N
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
//	�X�R�A�̏�������
//=============================================================================
void CScore::WriteFile(void)
{
	FILE * pFile = NULL;

	pFile = fopen(RANKING_DATA_PATH, "w");
	//NULL�`�F�b�N
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
//	�X�R�A�̕ۑ�
//=============================================================================
int CScore::SaveScore(void)
{
	int nCount;

	ReadFile();

	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//�����L���O���X�V����ꏊ�̔���
		if (m_nScore > m_nRankingScore[nCount])
		{
			//�ȍ~�̃����L���O�f�[�^�����Ɉړ�
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

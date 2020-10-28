//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "main.h"

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = true;
CScene*CScene::m_apScene[PRIORITY][MAX_POLYGON] = {};

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_objType = OBJTYPE_NONE;
			m_nNum = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//	�I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objtype)
{
	m_objType = objtype;
}

//=============================================================================
//	�I�u�W�F�N�g�̎�ނ̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//	�S�̂̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	if (m_bPause == true)
	{
		for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
		{
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				if (m_apScene[nCountpriority][nCount] != NULL)
				{
					// �|���S���̍X�V����
					m_apScene[nCountpriority][nCount]->Update();
				}
			}
		}
	}
}

//=============================================================================
//	�S�̂̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				// �|���S���̕`�揈��
				m_apScene[nCountpriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
//	�S�̂̉������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				m_apScene[nCountpriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
//	�S�̂̉������
//=============================================================================
void CScene::ReleaseAllFade(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL && m_apScene[nCountpriority][nCount]->m_objType != OBJTYPE_FADE)
			{
				m_apScene[nCountpriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
//	�|�[�Y���̎擾
//=============================================================================
void CScene::Pause(bool bPause)
{
	m_bPause = bPause;
}

//=============================================================================
//	�������
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nNum] != NULL)
	{
		//m_nNum�̂܂܎g����delete�����
		//���ׂĂ�m_nNum�̒l��delete�����̂�
		//��ɕϐ��ɑ�����邱�Ƃł����j�~����
		int priority = m_nPriority;
		int nNum = m_nNum;
		delete m_apScene[priority][nNum];
		m_apScene[priority][nNum] = NULL;
		m_nNumAll--;
	}
}
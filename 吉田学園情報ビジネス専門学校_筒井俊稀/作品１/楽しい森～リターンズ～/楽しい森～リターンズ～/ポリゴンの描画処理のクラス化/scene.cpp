//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "main.h"

//=============================================================================
//	静的メンバ変数の初期化
//=============================================================================
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = true;
CScene*CScene::m_apScene[PRIORITY][MAX_POLYGON] = {};

//=============================================================================
//	コンストラクタ
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
//	デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//	オブジェクトの種類の設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objtype)
{
	m_objType = objtype;
}

//=============================================================================
//	オブジェクトの種類の取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//	全体の更新処理
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
					// ポリゴンの更新処理
					m_apScene[nCountpriority][nCount]->Update();
				}
			}
		}
	}
}

//=============================================================================
//	全体の描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				// ポリゴンの描画処理
				m_apScene[nCountpriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
//	全体の解放処理
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
//	全体の解放処理
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
//	ポーズ情報の取得
//=============================================================================
void CScene::Pause(bool bPause)
{
	m_bPause = bPause;
}

//=============================================================================
//	解放処理
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nNum] != NULL)
	{
		//m_nNumのまま使うとdeleteすると
		//すべてのm_nNumの値がdeleteされるので
		//先に変数に代入することでそれを阻止する
		int priority = m_nPriority;
		int nNum = m_nNum;
		delete m_apScene[priority][nNum];
		m_apScene[priority][nNum] = NULL;
		m_nNumAll--;
	}
}
//------------------------------------------
//
//	クラスポリゴン描画[scene2d.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _LIFE_H_
#define _LIFE_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "main.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CNumber;

//------------------------------------------
//	クラス
//------------------------------------------
class CLife : public CScene
{
public:
	//メンバ関数宣言
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
	//メンバ変数宣言
	CNumber *m_pNumber;
	int m_nLife;
};




#endif
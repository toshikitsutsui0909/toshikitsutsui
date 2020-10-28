#pragma once
//=============================================================================
//
// 敵の処理 [enemy.h]
// Author :	トシキ
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "scene2d.h"
#include "main.h"

class CBullet;
//=============================================================================
//	エネミークラスの作成（派生クラス）
//=============================================================================
class CEnemy : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_NORMAL_2,
		TYPE_NORMAL_3,
		TYPE_NORMAL_4,
		TYPE_NORMAL_5,
		TYPE_HARDTYPE,
		TYPE_BOSS,
		TYPE_MAX
	}ENEMYTYPE;

	CEnemy(int nPriority = 8);
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMYTYPE::TYPE_MAX];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;
	ENEMYTYPE m_type;
	int m_nLife;
	int m_nDamage;
	int m_nCount;
	float m_fSpeed;
	int m_nRandNumber;
	int m_Counter;
	int m_nCntCol;
	bool m_bDamege;
};



#endif //_ENEMY_H_
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

//=============================================================================
//	前方宣言
//=============================================================================
class CBullet;

//=============================================================================
//	エネミークラスの作成（派生クラス）
//=============================================================================
class CEnemy : public CScene2d
{
public:
	//敵のタイプ
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,	// 通常の敵
		TYPE_NORMAL_2,	// 通常（動き違い）
		TYPE_NORMAL_3,	// 通常（動き違い）
		TYPE_NORMAL_4,	// 通常（動き違い）
		TYPE_NORMAL_5,	// 通常（動き違い）
		TYPE_HARDTYPE,	// 少し強い敵
		TYPE_BOSS,		// ボス
		TYPE_MAX
	}ENEMYTYPE;

	//メンバ関数宣言
	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMYTYPE::TYPE_MAX];
	D3DXVECTOR3 m_pos;		//座標
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_move;		//移動量
	ENEMYTYPE m_type;		//敵タイプ
	int m_nLife;			//敵の耐久値
	int m_nDamage;			//ダメージ量
	int m_nCount;			//敵の弾の撃つ間隔
	float m_fSpeed;			//移動スピード
	int m_nRandNumber;		//弾の撃つスピード（乱数管理）
	int m_Counter;			//上下移動管理
	int m_nCntCol;			//カラーの変更
	bool m_bDamege;			//ダメージ情報
};



#endif //_ENEMY_H_
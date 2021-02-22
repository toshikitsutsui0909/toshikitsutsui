//------------------------------------------
//
//	弾の処理[bullet.h]
//	Author : 筒井 俊稀
//
//------------------------------------------

//二重インクルード防止
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene2d.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CPlayer;

//------------------------------------------
//	バレットクラス
//------------------------------------------
class CBullet : public CScene2d
{
public:
	//弾の種類分け
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,		//プレイヤーの弾
		BULLETTYPE_ENEMY,		//敵の弾１
		BULLETTYPE_ENEMY_2,		//敵の弾２
		BULLETTYPE_MAX
	}BULLETTYPE;

	//メンバ関数宣言
	CBullet(int nPriority = OBJTYPE_BULLET);
	virtual ~CBullet();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3());
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetBullet(int nDamage);
	virtual D3DXVECTOR3 GetBullet(void) { return m_move; }
private:
	//メンバ変数宣言
	static int m_nCount;
protected:
	D3DXVECTOR3 m_move;						//移動量
	int m_nLife;							//弾の移動範囲
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLETTYPE::BULLETTYPE_MAX];//テクスチャ
	BULLETTYPE m_BulletType;				//弾の種類
	int m_nDamage;							//弾のダメージ量
	static bool m_bDamage;					//ダメージを食らったか判定
};

//チャージ弾クラス
class CChargeBullet : public CBullet
{
public:
	//メンバ関数宣言
	CChargeBullet();
	~CChargeBullet();
	static CChargeBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};


#endif // !_BULLET_H_

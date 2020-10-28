#pragma once
//------------------------------------------
//
//	弾の処理[bullet.h]
//	筒井
//
//------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene2d.h"

class CPlayer;

//------------------------------------------
//	バレットクラス
//------------------------------------------
class CBullet : public CScene2d
{
public:
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,
		BULLETTYPE_ENEMY,
		BULLETTYPE_ENEMY_2,
		BULLETTYPE_MAX
	}BULLETTYPE;
	CBullet(int nPriority = 6);
	virtual ~CBullet();
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3());
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetBullet(int nDamage);
	virtual D3DXVECTOR3 GetBullet(void) { return m_move; }
private:
	static int m_nCount;
protected:
	D3DXVECTOR3 m_move;//移動量
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_apTexture[BULLETTYPE::BULLETTYPE_MAX];
	//D3DXVECTOR3 m_size;
	BULLETTYPE m_BulletType;
	float m_nDistance;
	int m_nDamage;
	static bool m_bDamage;
};

class CChargeBullet : public CBullet
{
public:
	CChargeBullet();
	~CChargeBullet();
	static CChargeBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLETTYPE type, D3DXVECTOR3 distance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_nCount;
};


#endif // !_BULLET_H_

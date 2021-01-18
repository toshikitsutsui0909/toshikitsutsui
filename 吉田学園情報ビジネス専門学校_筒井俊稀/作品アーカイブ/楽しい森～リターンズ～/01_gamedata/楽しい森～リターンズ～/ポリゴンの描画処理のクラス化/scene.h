//------------------------------------------
//
//	クラスポリゴン描画[scene.h]
//	筒井
//
//------------------------------------------

#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"

//------------------------------------------
//	オブジェクトクラス
//------------------------------------------
class CScene
{
public:
	//各種類の当たり判定の設定
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_PLAYER_RIGHT,
		OBJTYPE_PLAYER_LEFT,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_CBULLET,
		OBJTYPE_LIFE,
		OBJTYPE_ITEM,
		OBJTYPE_BG,
		OBJTYPE_FADE,
		OBJTYPE_CHARGE,
		OBJTYPE_GAUGEBER,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	void SetObjType(OBJTYPE objtype);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int priority, int nCountScene) { return m_apScene[priority][nCountScene]; }
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void ReleaseAllFade(void);
	static void Pause(bool bPause);
private:
	static CScene *m_apScene[PRIORITY][MAX_POLYGON];
	static int m_nNumAll;
	int m_nNum;
	OBJTYPE m_objType;	//オブジェクトの種類
	int m_nPriority;
	static bool m_bPause;

protected:
	void Release(void);
};
//virtualがないと派生クラスのデストラクタが呼び出されないためもし
//派生クラスのデストラクタにdelete処理が入っていたら呼び出されず
//メモリの開放ができないので大変なことになる。


#endif // !_SCENE_H_

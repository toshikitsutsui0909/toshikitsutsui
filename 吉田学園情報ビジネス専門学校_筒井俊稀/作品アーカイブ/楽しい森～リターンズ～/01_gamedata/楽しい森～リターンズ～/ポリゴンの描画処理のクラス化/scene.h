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
		OBJTYPE_BG,				//背景オブジェクト
		OBJTYPE_LIFE,			//ライフオブジェクト
		OBJTYPE_BULLET,			//バレットオブジェクト
		OBJTYPE_CBULLET,		//チャージバレットオブジェクト
		OBJTYPE_PLAYER,			//プレイヤーオブジェクト
		OBJTYPE_ENEMY,			//エネミーオブジェクト
		OBJTYPE_EXPLOSION,		//爆発オブジェクト
		OBJTYPE_SCORE,			//スコアオブジェクト
		OBJTYPE_CHARGE,			//チャージオブジェクト
		OBJTYPE_GAUGEBER,		//ゲージバーオブジェクト
		OBJTYPE_FADE,			//フェードオブジェクト
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_NONE);
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

//------------------------------------------
//
//	チャージゲージの処理[charg.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _CHARG_H_
#define _CHARG_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CGauge;

//------------------------------------------
//	チャージゲージのクラス
//------------------------------------------
class CCharge : public CScene
{
public:
	//メンバ関数宣言
	CCharge(int nPriority = OBJTYPE_CHARGE);
	~CCharge();

	static CCharge *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Add(void);
	static void Set(void);
private:
	//メンバ変数宣言
	static CGauge *m_pGauge;	//ゲージ情報
	static int m_nCount;		//ゲージ量カウント
};


#endif // !_CHARG_H_

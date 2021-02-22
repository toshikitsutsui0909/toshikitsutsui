//-------------------------------------
//
//	フェード処理[fade.h]
//	筒井
//
//-------------------------------------

//二重インクルード防止
#ifndef _FADE_H_
#define _FADE_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "manager.h"

//------------------------------------------
//	フェードのクラス
//------------------------------------------
class CFade : public CScene
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,		//フェードイン
		FADE_OUT,		//フェードアウト
		FADE_MAX
	}FADE;

	//メンバ関数宣言
	CFade(int nPriority = OBJTYPE_FADE);
	~CFade();
	static CFade *Create(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos = D3DXVECTOR3(), D3DXVECTOR3 size = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CManager::MODE mode);
private:
	//メンバ変数宣言
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//バッファ
	D3DXVECTOR3 m_pos;		//座標
	D3DXVECTOR3 m_size;		//大きさ
	FADE m_fade;			//フェードタイプ
	D3DXCOLOR m_ColorFade;	//色の設定
	CManager::MODE m_mode;	//モード移行情報
};



#endif // !_FADE_H_

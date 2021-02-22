//------------------------------------------
//
//	背景の処理[ui.h]
//	筒井
//
//------------------------------------------
#ifndef _UI_H_
#define _UI_H_

//------------------------------------------
//	マクロ定義
//------------------------------------------
#define MAX_UI (TYPE_MAX)

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "scene.h"
#include "scene2d.h"
#include "main.h"

//------------------------------------------
//	背景のクラス
//------------------------------------------
class CUi : public CScene2d
{
public:
	typedef enum 
	{
		TYPE_NONE = 0,
		TYPE_DOWNUI,		//下の黒い場所
		TYPE_LIFE,			//プレイヤーライフ
		TYPE_WARNING,		//WARNING
		TYPE_PRESS_ENTER,	//PRESSENTER
		TYPE_MAX
	}UITYPE;

	CUi(int nPriority = OBJTYPE_NONE);
	~CUi();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move = D3DXVECTOR3());
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move = D3DXVECTOR3());
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_UI];
	UITYPE m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	bool m_bLoop;
	D3DXCOLOR m_col;
	int m_nCount;
};

#endif // !_BG_H_

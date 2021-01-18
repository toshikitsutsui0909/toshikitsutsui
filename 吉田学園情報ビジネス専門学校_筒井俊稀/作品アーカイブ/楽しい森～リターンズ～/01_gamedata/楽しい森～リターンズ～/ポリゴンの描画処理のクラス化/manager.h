//------------------------------------------
//
//	マネージャー処理[manager.h]
//	筒井
//
//------------------------------------------

#ifndef _MANAGER_H_
#define _MANAGER_H_

//------------------------------------------
//	前方宣言
//------------------------------------------
class CInputKeyBoard;
class CRenderer;
class CSound;
class CScore;
class CEnemy;
class CTitle;
class CResult;
class CGame;
class CFade;
class CTutorial;
class CScene;
class CScore;
class CUi;
class CGameover;
class CBasemode;
//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include<Windows.h>

//------------------------------------------
//	マネージャークラス
//------------------------------------------
class CManager
{
public:
	//ゲームの移行
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_GAMEOVER,
		MODE_END,
		MODE_MAX
	}MODE;
	//メンバ関数宣言
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Updata(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CFade *GetFade(void) { return m_pFade; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyBoard *GetInputKeyBoard(void) { return m_pInputKeyBoard; }
	static CSound *GetSound(void) { return m_pSound; }
	static CGame *GetGame(void) { return m_pGame; }
	static CScene *GetScene(void) { return m_pScene; }
	static CScore *GetScore(void) { return m_pScore; }
	static CUi *GetUi(void) { return m_pUi; }
	static CGameover *GetGameover(void) { return m_pGameover; }
	static CBasemode *GetBasemode(void) { return m_pBasemode; }
private:
	//メンバ変数宣言
	static CRenderer *m_pRenderer;
	static CInputKeyBoard *m_pInputKeyBoard;
	static CSound *m_pSound;
	static CScore *m_pScore;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static MODE m_mode;
	static CFade *m_pFade;
	static CScene *m_pScene;
	static CUi *m_pUi;
	static CGameover *m_pGameover;
	static CBasemode *m_pBasemode;
};



#endif
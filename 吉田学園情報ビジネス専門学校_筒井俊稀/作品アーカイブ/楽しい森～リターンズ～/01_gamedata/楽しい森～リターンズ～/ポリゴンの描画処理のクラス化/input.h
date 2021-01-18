//------------------------------------------
//
//	入力処理[input.h]
//	筒井
//
//------------------------------------------

//二重インクルード防止
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------
//	マクロ定義
//------------------------------------------
#define MAX_KEY_NUM 256

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include <Windows.h>
#include "main.h"

//------------------------------------------
//	基本クラス（入力処理）
//------------------------------------------
class CInput
{
public:
	//メンバ関数宣言
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	//メンバ変数宣言
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard; //入力デバイス(キーボード)へのポインタ
};

//キーボードクラス
class CInputKeyBoard : public CInput
{
public:
	//メンバ関数宣言
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyPress(int nKey);
	bool GetKeyTregger(int nKey);
	bool GetKeyRelease(int nKey);
private:
	//メンバ変数宣言
	BYTE m_aKeyState[MAX_KEY_NUM];			//基本ステート
	BYTE m_aKeyStateTrigger[MAX_KEY_NUM];	//トリガーステート
	BYTE m_aKeyStateRelease[MAX_KEY_NUM];	//リリースステート

};

#endif
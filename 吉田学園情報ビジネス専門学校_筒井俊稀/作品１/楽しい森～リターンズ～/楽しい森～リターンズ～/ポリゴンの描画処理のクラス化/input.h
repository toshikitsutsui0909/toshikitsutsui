//------------------------------------------
//
//	入力処理[input.h]
//	筒井
//
//------------------------------------------

#ifndef _INPUT_H_
#define _INPUT_H_

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
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard; //入力デバイス(キーボード)へのポインタ
};

class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyPress(int nKey);
	bool GetKeyTregger(int nKey);
	bool GetKeyRelease(int nKey);
private:
	BYTE m_aKeyState[MAX_KEY_NUM];
	BYTE m_aKeyStateTrigger[MAX_KEY_NUM];
	BYTE m_aKeyStateRelease[MAX_KEY_NUM];

};

#endif
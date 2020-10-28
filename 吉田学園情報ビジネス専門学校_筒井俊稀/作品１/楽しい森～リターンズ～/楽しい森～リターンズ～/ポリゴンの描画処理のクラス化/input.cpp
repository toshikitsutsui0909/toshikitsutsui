//=============================================================================
//
// 入力処理 [input.cpp]
// Author : トシキ
//
//=============================================================================
#include "input.h"

//静的メンバ宣言
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevKeyboard = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの作成
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の開放
	if (m_pDevKeyboard != NULL)
	{
		//キーボードのアクセス権を開放(入力制御終了)
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
	//Directinputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// キーボードのコンストラクタ
//=============================================================================
CInputKeyBoard::CInputKeyBoard()
{
	//m_aKeyState[MAX_KEY_NUM];
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
}

//=============================================================================
// キーボードのデストラクタ
//=============================================================================
CInputKeyBoard::~CInputKeyBoard()
{
}

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の作成
	m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL);

	//データフォーマットを作成
	m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	//協調モードを設定(フォアグラウンド&非排他モード)
	m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	//キーボードのアクセス権を獲得
	m_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY_NUM] = {}; //キーボードの入力情報

	int nCntKey;
	//デバイスからデータを取得
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY_NUM; nCntKey++)
		{
			//キープレス情報を保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];

		}
	}
	//キーボードの更新処理
	else
	{
		//キーボードへのアクセス権を取得
		m_pDevKeyboard->Acquire();
	}
}

//=============================================================================
// キーボードの押された時の処理（Press）
//=============================================================================
bool CInputKeyBoard::GetKeyPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの押された時の処理（Trigger）
//=============================================================================
bool CInputKeyBoard::GetKeyTregger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの押された時の処理（Trigger）
//=============================================================================
bool CInputKeyBoard::GetKeyRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

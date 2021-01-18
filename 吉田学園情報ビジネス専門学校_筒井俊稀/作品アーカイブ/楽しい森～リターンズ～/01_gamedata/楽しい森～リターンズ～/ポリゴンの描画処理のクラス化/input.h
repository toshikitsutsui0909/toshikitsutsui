//------------------------------------------
//
//	���͏���[input.h]
//	����
//
//------------------------------------------

//��d�C���N���[�h�h�~
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------
//	�}�N����`
//------------------------------------------
#define MAX_KEY_NUM 256

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include <Windows.h>
#include "main.h"

//------------------------------------------
//	��{�N���X�i���͏����j
//------------------------------------------
class CInput
{
public:
	//�����o�֐��錾
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	//�����o�ϐ��錾
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

//�L�[�{�[�h�N���X
class CInputKeyBoard : public CInput
{
public:
	//�����o�֐��錾
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyPress(int nKey);
	bool GetKeyTregger(int nKey);
	bool GetKeyRelease(int nKey);
private:
	//�����o�ϐ��錾
	BYTE m_aKeyState[MAX_KEY_NUM];			//��{�X�e�[�g
	BYTE m_aKeyStateTrigger[MAX_KEY_NUM];	//�g���K�[�X�e�[�g
	BYTE m_aKeyStateRelease[MAX_KEY_NUM];	//�����[�X�X�e�[�g

};

#endif
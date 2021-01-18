//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �g�V�L
//
//=============================================================================
#include "input.h"

//�ÓI�����o�錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevKeyboard = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̍쐬
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevKeyboard != NULL)
	{
		//�L�[�{�[�h�̃A�N�Z�X�����J��(���͐���I��)
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
	//Directinput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//=============================================================================
CInputKeyBoard::CInputKeyBoard()
{
	//m_aKeyState[MAX_KEY_NUM];
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
}

//=============================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//=============================================================================
CInputKeyBoard::~CInputKeyBoard()
{
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̍쐬
	m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL);

	//�f�[�^�t�H�[�}�b�g���쐬
	m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	//�������[�h��ݒ�(�t�H�A�O���E���h&��r�����[�h)
	m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	//�L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY_NUM] = {}; //�L�[�{�[�h�̓��͏��

	int nCntKey;
	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY_NUM; nCntKey++)
		{
			//�L�[�v���X����ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];

		}
	}
	//�L�[�{�[�h�̍X�V����
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevKeyboard->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̉����ꂽ���̏����iPress�j
//=============================================================================
bool CInputKeyBoard::GetKeyPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̉����ꂽ���̏����iTrigger�j
//=============================================================================
bool CInputKeyBoard::GetKeyTregger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̉����ꂽ���̏����iTrigger�j
//=============================================================================
bool CInputKeyBoard::GetKeyRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

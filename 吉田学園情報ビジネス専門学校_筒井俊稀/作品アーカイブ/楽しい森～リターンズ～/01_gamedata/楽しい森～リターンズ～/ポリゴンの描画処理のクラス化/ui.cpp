//=============================================================================
//
// �w�i�̏��� [ui.cpp]
// Author : ���� �r�H
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "ui.h"
#include "renderer.h"
#include "manager.h"

//-----------------------------------------------------------------------------
//	�}�N����`
//-----------------------------------------------------------------------------
#define RATE (0.005f)

#define TEXTURE_PATH_DOWNUI			"data/texture/carbon.png"		//���̍����ꏊ
#define TEXTURE_PATH_LIFE			"data/texture/playerlife.png"	//�v���C���[���C�t
#define TEXTURE_PATH_WARNING		"data/texture/WARNING.png"		//WARNING�\�L
#define TEXTURE_PATH_PRESS_ENTER	 "data/texture/prese_enter.png"	//PRESSENTER�\�L

#define PRESS_ENTER_FLASING_SPEED_1 20								//�͂���
#define PRESS_ENTER_FLASING_SPEED_2 40								//�I���

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_apTexture[UITYPE::TYPE_MAX] = {};

//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
CUi::CUi(int nPriority) : CScene2d(nPriority)
{
	m_type = CUi::TYPE_NONE;
	m_bLoop = true;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCount = 0;
}

//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
CUi::~CUi()
{

}

//-----------------------------------------------------------------------------
//	�e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_DOWNUI, &m_apTexture[CUi::TYPE_DOWNUI]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_LIFE, &m_apTexture[CUi::TYPE_LIFE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_WARNING, &m_apTexture[CUi::TYPE_WARNING]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_PRESS_ENTER, &m_apTexture[CUi::TYPE_PRESS_ENTER]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�N�X�`���j���̏���
//-----------------------------------------------------------------------------
void CUi::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	��������
//-----------------------------------------------------------------------------
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move)
{
	CUi *pUi;
	pUi = new CUi;
	if (pUi != NULL)
	{
		pUi->Init(pos, size, type);
	}
	return pUi;
}

//-----------------------------------------------------------------------------
//	����������
//-----------------------------------------------------------------------------
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type, D3DXVECTOR3 move)
{
	CScene2d::Init(pos, size);
	SetObjType(CScene::OBJTYPE_NONE);
	m_type = type;
	CScene2d::BindTexture(m_apTexture[m_type]);
	CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void CUi::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void CUi::Update(void)
{
	m_nCount++;
	//WARNING����
	if (m_type == TYPE_WARNING)
	{
		CScene2d::Flashing();
	}
	//PRESSENTER����
	if (m_type == TYPE_PRESS_ENTER)
	{
		if (m_nCount % PRESS_ENTER_FLASING_SPEED_1 == 0)
		{
			CScene2d::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		if (m_nCount % PRESS_ENTER_FLASING_SPEED_2 == 0)
		{
			CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void CUi::Draw(void)
{
	CScene2d::Draw();
}

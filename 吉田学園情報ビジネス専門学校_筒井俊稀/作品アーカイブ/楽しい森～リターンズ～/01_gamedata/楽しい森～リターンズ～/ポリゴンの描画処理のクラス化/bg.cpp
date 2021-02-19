//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : ���� �r�H
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "scene2d.h"

//-----------------------------------------------------------------------------
//	�}�N����`
//-----------------------------------------------------------------------------
#define SPEED_FAST		0.003f	// �w�i�̓����X�s�[�h�i���j
#define SPEED_SECOND	0.002f	// �w�i�̓����X�s�[�h�i�^�񒆁j
#define SPEED_THIRD		0.005f	// �w�i�̓����X�s�[�h�i�O�j

#define TEXTURE_PATH_BG_0 "data/texture/bg104.png"	// ��
#define TEXTURE_PATH_BG_1 "data/texture/bg101.png"	// �^��
#define TEXTURE_PATH_BG_2 "data/texture/bg111.png"	// �O

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
CBg::CBg(int nPriority) : CScene(nPriority)
{
	//�ϐ��̏�����
	m_apScene2d[0] = NULL;
	m_apScene2d[1] = NULL;
	m_apScene2d[2] = NULL;
	
	m_fSpeedFast = 0;
	m_fSpeedSecond = 0;
	m_fSpeedThird = 0;
}

//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
CBg::~CBg()
{
}

//-----------------------------------------------------------------------------
//	�e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	////�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BG_0, &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BG_1, &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_BG_2, &m_apTexture[2]);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�N�X�`���j���̏���
//-----------------------------------------------------------------------------
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
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
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBg *pBg;
	pBg = new CBg;
	if (pBg != NULL)
	{
		pBg->Init(pos, size);
	}
	return pBg;
}

//-----------------------------------------------------------------------------
//	����������
//-----------------------------------------------------------------------------
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		m_apScene2d[nCount] = new CScene2d;
		if (m_apScene2d[nCount] != NULL)
		{
			m_apScene2d[nCount]->Init(pos, size);
			m_apScene2d[nCount]->BindTexture(m_apTexture[nCount]);
			m_apScene2d[nCount]->SetObjType(OBJTYPE_BG);
		}
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2d[nCount] != NULL)
		{
			m_apScene2d[nCount]->Uninit();
			m_apScene2d[nCount] = NULL;
		}
	}

	Release();
}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void CBg::Update(void)
{
	D3DXVECTOR2 tex[4];

	//�ړ��ʂ����߂�
	m_fSpeedFast += SPEED_FAST;
	m_fSpeedSecond += SPEED_SECOND;
	m_fSpeedThird += SPEED_THIRD;

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeedFast, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeedFast, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeedFast, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeedFast, 1.0f);

	m_apScene2d[0]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeedSecond, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeedSecond, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeedSecond, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeedSecond, 1.0f);

	m_apScene2d[1]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeedThird, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeedThird, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeedThird, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeedThird, 1.0f);

	m_apScene2d[2]->SetTex(tex);

}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void CBg::Draw(void)
{
}

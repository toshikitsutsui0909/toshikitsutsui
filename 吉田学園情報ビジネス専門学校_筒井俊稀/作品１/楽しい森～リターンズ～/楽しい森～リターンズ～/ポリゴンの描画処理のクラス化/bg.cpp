//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �g�V�L
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
	
	m_fSpeed0 = 0;
	m_fSpeed1 = 0;
	m_fSpeed2 = 0;
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
	D3DXCreateTextureFromFile(pDevice, "data/texture/bg104.png", &m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice, "data/texture/bg101.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data/texture/bg111.png", &m_apTexture[2]);

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

	m_fSpeed0 += 0.003f;
	m_fSpeed1 += 0.007f;
	m_fSpeed2 += 0.001f;

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed0, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed0, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed0, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed0, 1.0f);

	m_apScene2d[0]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed1, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed1, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed1, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed1, 1.0f);

	m_apScene2d[1]->SetTex(tex);

	tex[0] = D3DXVECTOR2(0.0f + m_fSpeed2, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f + m_fSpeed2, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f + m_fSpeed2, 1.0f);
	tex[3] = D3DXVECTOR2(1.0f + m_fSpeed2, 1.0f);

	m_apScene2d[2]->SetTex(tex);

}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void CBg::Draw(void)
{
}

//=============================================================================
//
// �e�̔����̏��� [explosion.cpp]
// Author : �g�V�L
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//-----------------------------------------------------------------------------
//	�e�̔����̃R���X�g���N�^
//-----------------------------------------------------------------------------
CExplosion::CExplosion(int nPriority) : CScene2d(nPriority)
{
	//�����o�ϐ��̏�����
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
}

//-----------------------------------------------------------------------------
//	�e�̔����̃f�X�g���N�^
//-----------------------------------------------------------------------------
CExplosion::~CExplosion()
{
}

//-----------------------------------------------------------------------------
//	�e�̔����̃e�N�X�`�����[�h����
//-----------------------------------------------------------------------------
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/texture/explosion000.png", &m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�̔����̃e�N�X�`���j������
//-----------------------------------------------------------------------------
void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
//	�e�̔����̐�������
//-----------------------------------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, size);
	}
	return pExplosion;
}

//-----------------------------------------------------------------------------
//	�e�̔����̏���������
//-----------------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	D3DXVECTOR2 tex[4];
	// �e�N�X�`�����W��ݒ�
	tex[0] = D3DXVECTOR2(0.125f, 0.0f);
	tex[1] = D3DXVECTOR2(0.125f + 0.125f, 0.0f);
	tex[2] = D3DXVECTOR2(0.125f, 1.0f);
	tex[3] = D3DXVECTOR2(0.125f + 0.125f, 1.0f);;

	CScene2d::Init(pos ,size);
	CScene2d::BindTexture(m_pTexture);
	//�e�N�X�`�����W�X�V
	CScene2d::SetTex(tex);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�̔����̏I������
//-----------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
//	�e�̔����̍X�V����
//-----------------------------------------------------------------------------
void CExplosion::Update(void)
{
	D3DXVECTOR2 tex[4];
	//�J�E���^�[�X�V
	m_nCounterAnim++;
	if (m_nCounterAnim % 4 == 0)
	{
		//�p�^�[���X�V
		m_nPatternAnim++;
		// �e�N�X�`�����W��ݒ�
		tex[0] = D3DXVECTOR2((float)m_nPatternAnim*0.125f, 0.0f);
		tex[1] = D3DXVECTOR2((float)m_nPatternAnim*0.125f + 0.125f, 0.0f);
		tex[2] = D3DXVECTOR2((float)m_nPatternAnim*0.125f, 1.0f);
		tex[3] = D3DXVECTOR2((float)m_nPatternAnim*0.125f + 0.125f, 1.0f);

		//�e�N�X�`�����W�X�V
		CScene2d::SetTex(tex);
	}
	//�A�j���[�V�����I��
	if (m_nPatternAnim >= 8)
	{
		Uninit();
	}
}

//-----------------------------------------------------------------------------
//	�e�̔����̕`�揈��
//-----------------------------------------------------------------------------
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

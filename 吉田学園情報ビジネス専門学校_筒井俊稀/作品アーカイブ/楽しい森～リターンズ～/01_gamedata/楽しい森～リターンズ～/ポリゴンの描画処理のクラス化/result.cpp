//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �g�V�L
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "ranking.h"
#include "score.h"

//-----------------------------------------------------------------------------
//�@�}�N����`
//-----------------------------------------------------------------------------
#define TEXTURE_PATH_RESULT "data/texture/���U���g.jpg"	//���U���g�e�N�X�`��

#define RANKING_POS_X 460.0f
#define RANKING_POS_Y 220.0f
#define RANKING_SIZE_X 50.0f
#define RANKING_SIZE_Y 50.0f

//-----------------------------------------------------------------------------
//	�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pVtxBuff = NULL;
	m_pRank = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
HRESULT CResult::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_RESULT, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
void CResult::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CResult *pResult;
	pResult = new CResult;
	if (pResult != NULL)
	{
		pResult->Init(pos, size);
	}
	return pResult;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�E��

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�(�l��1.0�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	m_pRank = CRanking::Create(D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f), D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	//�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pRank != NULL)
	{
		m_pRank->Uninit();
		m_pRank = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

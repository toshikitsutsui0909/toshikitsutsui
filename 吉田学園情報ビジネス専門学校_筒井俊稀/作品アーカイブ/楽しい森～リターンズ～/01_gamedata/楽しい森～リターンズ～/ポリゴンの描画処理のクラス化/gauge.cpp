//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : ����
//
//=============================================================================
#include "gauge.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CGauge::CGauge()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
//	��������
//=============================================================================
CGauge * CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CGauge *pGauge;
	pGauge = new CGauge;
	if (pGauge != NULL)
	{
		pGauge->Init(pos, size);
	}
	return pGauge;
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	m_size = size;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x * m_nNum)), m_pos.y, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, (m_pos.y + m_size.y), 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x * m_nNum)), (m_pos.y + m_size.y), 0.0f);//�E��

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
	pVtx[0].col = D3DCOLOR_RGBA(90, 90, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(90, 90, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(90, 90, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(90, 90, 255, 255);


	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CGauge::Uninit(void)
{
	//�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CGauge::Update(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CGauge::Draw(void)
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

//=============================================================================
//	�傫����ς��鏈��
//=============================================================================
void CGauge::SetNum(int nNum)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	m_nNum = nNum;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x * m_nNum)), m_pos.y, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, (m_pos.y + m_size.y), 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x * m_nNum)), (m_pos.y + m_size.y), 0.0f);//�E��

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}
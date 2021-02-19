//=============================================================================
//
// �����̏��� [number.cpp]
// Author : �g�V�L
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "number.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NUMBER "data/texture/number000.png"

//=============================================================================
//	�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	//�e�����o�ϐ��̏�����
	m_pVtxBuff = NULL;
	m_Pos = D3DXVECTOR3();
	m_Size = D3DXVECTOR3();
	m_col = D3DXCOLOR(255,255,255,255);
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//	�e�N�X�`�����[�h����
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NUMBER, &m_pTexture);

	return S_OK;
}

//=============================================================================
//	�e�N�X�`���j��
//=============================================================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//	��������
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	if (pNumber != NULL)
	{
		pNumber->Init(pos, size);
	}
	return pNumber;
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_Pos = pos;

	m_Size = size;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_Pos.x - m_Size.x / 2), (m_Pos.y - m_Size.y / 2), 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + m_Size.x / 2), (m_Pos.y - m_Size.y / 2), 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3((m_Pos.x - m_Size.x / 2), (m_Pos.y + m_Size.y / 2), 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + m_Size.x / 2), (m_Pos.y + m_Size.y / 2), 0.0f);//�E��

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

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

	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CNumber::Uninit(void)
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
void CNumber::Updata(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CNumber::Draw(void)
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
//	������ݒ肷�鏈��
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2((float)nNumber*0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)nNumber*0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)nNumber*0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)nNumber*0.1f + 0.1f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�J���[��ݒ�
//=============================================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

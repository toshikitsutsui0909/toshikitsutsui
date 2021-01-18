//=============================================================================
//
// polygon���� [scene2d.cpp]
// Author : 
//
//=============================================================================
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

#define FLASH_RATE 0.05f
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	//���������悤
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	//���S��POS�����߂�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_size = D3DXVECTOR3();
	m_col = D3DXCOLOR();
	m_bFlash = true;
	m_FlashState = FLASH_STATE_IN;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CScene2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//�E��

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
	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CScene2d::Uninit(void)
{
	//�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CScene2d::Update(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CScene2d::Draw(void)
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
//	�`�悵�����ꏊ�̍��W�����߂鏈��
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
                                                                                                                                                                                                                                                                                                                                                                                                                                                                         	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	m_pos = pos;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//�E��

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�`�悵�����ꏊ�̑傫�������߂鏈��
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
//	�`�悵�����ꏊ�̃e�N�X�`�������߂鏈��
//=============================================================================
void CScene2d::SetTex(D3DXVECTOR2* tex)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = tex[0];
 	pVtx[1].tex = tex[1];
	pVtx[2].tex = tex[2];
	pVtx[3].tex = tex[3];

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�`�悵�����ꏊ�̃e�N�X�`�������߂鏈��
//=============================================================================
void CScene2d::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	m_col = col;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�e�N�X�`���𕪂��鏈��
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	�e�N�X�`���t���b�V������
//=============================================================================
void CScene2d::Flashing(void)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	if (m_FlashState == FLASH_STATE_IN)
	{
  		m_col.a -= FLASH_RATE;
		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_FlashState = FLASH_STATE_OUT;
		}
	}
	else if (m_FlashState == FLASH_STATE_OUT)
	{
		m_col.a += FLASH_RATE;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_FlashState = FLASH_STATE_IN;
		}
	}
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//	��������
//=============================================================================
CScene2d * CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2d *pScene2D;
	pScene2D = new CScene2d;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, size);
	}
	return pScene2D;
}


//=============================================================================
//
// �t�F�[�h�̏��� [fade.cpp]
// Author : ���� �r�H
//
//=============================================================================
//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
//	�}�N����`
//-----------------------------------------------------------------------------
#define FADE_RATE (0.1f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_NONE;
	m_mode = CManager::MODE_TITLE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ��������
//=============================================================================
CFade * CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFade *pFade;
	pFade = new CFade;
	if (pFade != NULL)
	{
		pFade->Init(pos, size);
	}
	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	CScene::SetObjType(OBJTYPE_FADE);

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
	pVtx[0].col = m_ColorFade;
	pVtx[1].col = m_ColorFade;
	pVtx[2].col = m_ColorFade;
	pVtx[3].col = m_ColorFade;


	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	m_fade = FADE_OUT;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
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
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_ColorFade.a -= FADE_RATE;
			if (m_ColorFade.a <= 0.0f)
			{
				m_ColorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_ColorFade.a += FADE_RATE;
			if (m_ColorFade.a >= 1.0f)
			{
				m_ColorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_mode);
			}
		}
	}
	//���_�o�b�t�@�͈̔͂����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].col = m_ColorFade;
	pVtx[1].col = m_ColorFade;
	pVtx[2].col = m_ColorFade;
	pVtx[3].col = m_ColorFade;

	//���_�f�[�^�̂��A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_OUT;
	m_mode = mode;
}
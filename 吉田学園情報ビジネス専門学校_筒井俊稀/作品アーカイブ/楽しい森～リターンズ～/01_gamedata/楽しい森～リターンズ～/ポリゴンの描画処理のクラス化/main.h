//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"
#include "dinput.h"
#include <stdlib.h>
#include <xaudio2.h>
#include <stdio.h>

//*****************************************************************************
//�O������
//*****************************************************************************
//class CRenderer;
//class CScene;

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SCREEN_WIDTH (1280)//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)//�E�B���h�E�̍���
#define NUM_VERTEX (4) //���_��
#define NUM_POLYGON (2) //�|���S����
#define MAX_POLYGON (256)
#define PRIORITY (15)
#define MAX_ENEMY (150)
#define MAX_ENEMY_PLA (5)
#define MAX_BG (3)
#define MAX_TEXTURE (3)
#define PLAYER_SIZE_X (80.0f)
#define PLAYER_SIZE_Y (40.0f)
#define ENEMY_SIZE_X (25.0f)
#define ENEMY_SIZE_Y (25.0f)
#define ENEMY_SIZE (50.0f)
#define BOSS_SIZE (200.0f)
#define BULLET_SIZE (20.0f)
#define BULLET_SIZE_PLAYER_X (20.0f)
#define BULLET_SIZE_PLAYER_Y (5.0f)
#define NUMBER_SIZE (30.0f)
#define EXPLOSION_SIZE (50.0f)
#define MOVE_SPEED (5.5f)
#define ENEMY_LIFE (5)
#define MAX_NUMBER (8)
#define SCREEN_WIDTH_SIDE (700.0f)//�E�B���h�E�̕�
#define MAX_RANKING (5)
#define WINDOW_POS_X (0)
#define WINDOW_POS_Y (0)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

int GetFPS(void);

#endif
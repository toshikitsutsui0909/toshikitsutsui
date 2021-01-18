//=============================================================================
//
// メイン処理 [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"
#include "dinput.h"
#include <stdlib.h>
#include <xaudio2.h>
#include <stdio.h>

//*****************************************************************************
//前方処理
//*****************************************************************************
//class CRenderer;
//class CScene;

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SCREEN_WIDTH (1280)//ウィンドウの幅
#define SCREEN_HEIGHT (720)//ウィンドウの高さ
#define NUM_VERTEX (4) //頂点数
#define NUM_POLYGON (2) //ポリゴン数
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
#define SCREEN_WIDTH_SIDE (700.0f)//ウィンドウの幅
#define MAX_RANKING (5)
#define WINDOW_POS_X (0)
#define WINDOW_POS_Y (0)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //座標変換用係数(1.0fで固定)
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

int GetFPS(void);

#endif
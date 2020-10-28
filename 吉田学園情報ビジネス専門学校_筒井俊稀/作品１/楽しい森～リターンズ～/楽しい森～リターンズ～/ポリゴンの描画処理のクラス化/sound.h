#pragma once
//=============================================================================
//
// サウンド処理 [sound.h]
// Author : HOGE FUGA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// 音楽のクラス
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_SE_SHOT = 0,		// SHOT
		SOUND_LABEL_SE_EXPLOSION,	// EXPLOSION
		SOUND_LABEL_SE_ENTER,
		SOUND_LABEL_BGM_TITLE,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_BOSS,
		SOUND_LABEL_BGM_ALARM,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif

//------------------------------------------
//
//	�N���X�|���S���`��[scene.h]
//	����
//
//------------------------------------------

#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"

//------------------------------------------
//	�I�u�W�F�N�g�N���X
//------------------------------------------
class CScene
{
public:
	//�e��ނ̓����蔻��̐ݒ�
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_PLAYER_RIGHT,
		OBJTYPE_PLAYER_LEFT,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_CBULLET,
		OBJTYPE_LIFE,
		OBJTYPE_ITEM,
		OBJTYPE_BG,
		OBJTYPE_FADE,
		OBJTYPE_CHARGE,
		OBJTYPE_GAUGEBER,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	void SetObjType(OBJTYPE objtype);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int priority, int nCountScene) { return m_apScene[priority][nCountScene]; }
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void ReleaseAllFade(void);
	static void Pause(bool bPause);
private:
	static CScene *m_apScene[PRIORITY][MAX_POLYGON];
	static int m_nNumAll;
	int m_nNum;
	OBJTYPE m_objType;	//�I�u�W�F�N�g�̎��
	int m_nPriority;
	static bool m_bPause;

protected:
	void Release(void);
};
//virtual���Ȃ��Ɣh���N���X�̃f�X�g���N�^���Ăяo����Ȃ����߂���
//�h���N���X�̃f�X�g���N�^��delete�����������Ă�����Ăяo���ꂸ
//�������̊J�����ł��Ȃ��̂ő�ςȂ��ƂɂȂ�B


#endif // !_SCENE_H_

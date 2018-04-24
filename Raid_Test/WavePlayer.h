// WavePlayer.h: interface for the CWavePlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_)
#define AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*****************************************************************************
*                                                                            *
*							  ����:������                                    *
*							  QQ:1206908474                                  *
*							  ����:1206908474@qq.com                         *
*						      ����:2014��3��20��                             *
*                                                                            *
*****************************************************************************/

#include <MMSystem.h>
#include "Digitalv.h"
#pragma comment(lib, "winmm.lib")


class CWavePlayer  
{
public:
	CWavePlayer(CString s);
	virtual ~CWavePlayer();
public:
	/*��Ա����*/
	CString m_strFilePath;		//��ǰ�ļ���·��
	int m_nFileLength;			//��ǰ�ļ��ĳ���
	int m_nVolume;				//��ǰ����
	bool m_bIsPlaying;			//�Ƿ����ڲ���
	MCIDEVICEID m_nElementID;	//��ǰ�����豸ID��Ϊ0ʱ������û�в���
	bool m_bPause;				//����ͣ
	bool m_bSetPosPause;		//�����ò���λ�ö���ͣ

public:
	/*��Ա����*/
	int GetFileLength();						//��õ�ǰ�ļ��ĳ���
	void Pause();								//��ͣ
	void SetPos(int nPos,bool bPlayNow=true);	//���ò���λ�ã�bPlayNow��ʾ�Ƿ���������
	void Stop();								//ֹͣ����
	void Play();								//����
	void Resume();								//��ͣ��ָ�����
	int GetCurrentVolume();						//��õ�ǰ����
	void SetVolume(int nVolume);				//��������
	int GetCurrentPos();						//��õ�ǰ����λ��
};

#endif // !defined(AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_)

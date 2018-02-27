#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

/*!
 * \file SplashWindow.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <QSplashScreen>
//#include "UIs/Activity.h"
#include "Common/qtxml_com.h"
#include <QtCore/QThread>
class Activity;
class QLabel;
class QPixmap;
class sl_Timer;

/*!
 * \class SplashWindow
 *
 * \brief ��������
 *
 * \author ����
 * \date ���� 2016
 */
class QTXML_EXPORT SplashWindow:public QSplashScreen
{
	Q_OBJECT
public:
	//���캯��
	//��������
	//����ֵ����
	SplashWindow(void);
	//��������
	//��������
	//����ֵ����
	~SplashWindow(void);
	//������ʱ����ʱ��
	//������
	//		duration:��ʱ����ʱ��
	//����ֵ����
	void setDelay(int duration);
	//���ù����Ĵ���
	//������
	//		activity:������ָ�봰��
	//����ֵ����
	/*void setActivity(Activity* activity)
	{
	_relateActivity = activity;
	if (_relateActivity)
	_relateActivity->_splashWindow = this;
	}*/
	//��ʼ����
	//��������
	//����ֵ����
	//bool start();
	//�����������ڵĲ�������
	//������
	//		layout_filename:�����ļ�·��
	//����ֵ����
	void setContentView(const char* layout_filename);
	//�ر���ʱ
	//��������
	//����ֵ����
	//void disableDelay(){_bDelay =false;}
	//������ʱ
	//��������
	//����ֵ����
	//void enableDelay(){_bDelay = true;}
	//������ʾ��Ϣ���ı��ؼ�ID
	//������
	//		szMessageID:�ı��ؼ�ID
	//����ֵ���Ƿ����óɹ�
	bool setMessageLabelID(const char* szMessageID);
	//������ʾ��Ϣ
	//������
	//		szMessage:��ʾ��Ϣ
	//����ֵ����
	void showMessage(const char* szMessage);

	void setBackground(const char* szFileName);
protected:

protected slots:
	//void activeRelatedActivity();
private:
	//20150925
	Activity* _contentActivity;
	Activity* _relateActivity;
	sl_Timer* _delay;
	bool _bDelay;
	bool _activeSuccess;
	QLabel* _pMessage;
};

#endif

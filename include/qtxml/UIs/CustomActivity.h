/*!
 * \file CustomActivity.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef CUSTOMACTIVITY_H
#define CUSTOMACTIVITY_H

#pragma once
#include "UIs/Activity.h"
#include "Common/qtframework_com.h"

class TitleBar;
class QTimer;
/*!
 * \class CustomActivity
 *
 * \brief CustomActivity��
 *
 * \author ����
 * \date ���� 2016
 */
class QTFRAMEWORK_EXPORT CustomActivity : public Activity
{
	Q_OBJECT
public:
	//�������
	enum MouseArea
	{
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Other
	};
	////���캯��
	//��������
	//����ֵ����
	CustomActivity(void);
	////���캯��
	//��������
	//����ֵ����
	CustomActivity(SplashWindow* pSplashWindow);
	//������ʾģʽ
	//������
	//		mode:��ʾģʽ
	//����ֵ����Դ
	void setShowMode(ShowMode mode);
	//��������
	//��������
	//����ֵ����
	~CustomActivity(void);
	//��С���¼�
	//��������
	//����ֵ����
	virtual void minimizeActivityEvent();
	//����¼�
	//��������
	//����ֵ����
	virtual void maximizeActivityEvent();
	//�ر��¼�
	//��������
	//����ֵ����
	virtual void closeActivityEvent();
	////��д�Ŵ���С����
	//��ʾ�¼�
	//��������
	//����ֵ����
	virtual void showEvent(QShowEvent *e);
	//�����¼�
	//��������
	//����ֵ����
    virtual void hideEvent(QHideEvent *e);
	//����
	//��������
	//����ֵ������ɹ�����true,���򷵻�false
    virtual bool active();
private slots:
	//��С������
	//��������
	//����ֵ����
	void minimizeActivity();
	//��󻯴���
	//��������
	//����ֵ����
	void maximizeActivity();
	//�رմ���
	//��������
	//����ֵ����
	void closeActivity();
	//�ض�λ���
	//��������
	//����ֵ����
	void regionMouse();
protected:
	//�����¼�
	//������
	//		event:�¼�
	//����ֵ����
	void paintEvent(QPaintEvent *);
	virtual void installContent();
	//����ƶ��¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mouseMoveEvent(QMouseEvent *event);
	//��갴���¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mousePressEvent(QMouseEvent *event);
	//����ɿ��¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mouseReleaseEvent(QMouseEvent *event);	
	//�뿪�����¼�
	//������
	//		event:�¼�
	//����ֵ����
	void leaveEvent(QEvent *event);
	//���봰���¼�
	//������
	//		event:�¼�
	//����ֵ����
	void enterEvent(QEvent *event);
	//ѡ���¼�
	//������
	//		event:�¼�
	//����ֵ����
    void focusInEvent(QFocusEvent *event);
	//���뽹���¼�
	//������
	//		event:�¼�
	//����ֵ����
    void focusOutEvent(QFocusEvent * event);
	//���ڴ���֮ǰ����Ϊ
	//��������
	//����ֵ���ɹ�����true,���򷵻�false
	bool actionBeforeCreated();
	//���ڴ���֮�����Ϊ
	//��������
	//����ֵ���ɹ�����true,���򷵻�false
	bool actionAfterActived();
	

	TitleBar* _titleBar;
private:
	void relateTitleBar();

	MouseArea _mouseArea;
	bool _dragging;
	int _curMouseX;
	int _curMouseY;
	int _preWidth;
	int _preHeight;
	int _preX;
    int _preY;
	ShowMode _preShowMode;
	QTimer* _timer;
};

#endif

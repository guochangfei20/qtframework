/*!
 * \file Listener.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <QtCore/QObject>
class ui_node;
/*!
 * \class Listener
 *
 * \brief ������
 *
 * \author ����
 * \date ���� 2016
 */
class Listener :public QObject
{
	Q_OBJECT
public:
	//���캯��
	//��������
	//����ֵ����
	Listener(void);
	//��������
	//��������
	//����ֵ����
	~Listener(void);
	public slots:
		//����
		//��������
		//����ֵ����
		virtual void trigger();
protected:
	ui_node* _sender;
};


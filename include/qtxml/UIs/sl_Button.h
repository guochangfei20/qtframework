/*!
 * \file sl_Button.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef SL_BUTTON_H
#define SL_BUTTON_H

#pragma once
#include <QPushButton>
#include "Common/qtframework_com.h"
class ClickListenser;
/*!
 * \class sl_Button
 *
 * \brief sl_Button��
 *
 * \author ����
 * \date ���� 2016
 */
class QTFRAMEWORK_EXPORT sl_Button :
	/*public ui_node,*/ public QPushButton
{
	Q_OBJECT
public:
	//���캯��
	//��������
	//����ֵ����
	sl_Button();
	////��������
	//��������
	//����ֵ����
	~sl_Button();
	//��Ӽ�����
	//������
	//		listenser:������
	//����ֵ����
	void addClickListener(ClickListenser* listenser);
	//�Ƴ�������
	//������
	//		listenser:������
	//����ֵ����
	void removeClickListenser(ClickListenser* listenser);
	//���ð�ť��ʽ
	//������
	//		style:��ʽ
	//����ֵ����
	void setStyle(const char* style);
	//���ð�ť��ʽ
	//������
	//		style:��ʽ
	//����ֵ����
	void setStyle(std::string style);
	//���ð�ťicon
	//������
	//		icon:icon·��
	//����ֵ����
	void setIcon(const char* icon);
	//���ð�ť����ͼƬ
	//������
	//		resImg:ͼƬ·��
	//����ֵ����
	void setBackgroundImage(const char* resImg);
	//���ð�ť�Ƿ������Ӧ����
	//������
	//		b:�Ƿ������Ӧ����
	//����ֵ����
	void setAvailable(bool b)
	{
		_bAvailable=b;
		if (!_bAvailable)
		{
			emit availabled();
		}
	}
	//��ð�ť�Ƿ������Ӧ����
	//��������
	//����ֵ��������Ӧ����true,���򷵻�false
	bool availlabe(){return _bAvailable;}
	//��ð�ť�Ƿ���Ҫȷ�϶Ի���
	//��������
	//����ֵ����Ҫ����true,���򷵻�false
	bool needToConfirm(){return _bNeedToConfirm;}
	//���ð�ť�Ƿ���Ҫȷ�϶Ի���
	//������
	//		b:�Ƿ���Ҫȷ�϶Ի���
	//����ֵ����
	void setNeedToConfirm(bool b)
	{
		_bNeedToConfirm = b;
	}
	//��ð�ť�Ƿ��Ѿ���ȷ��
	//��������
	//����ֵ����ȷ�Ϸ���true,���򷵻�false
	bool confirmed(){return _bConfirmed;}
	//���ð�ť�Ƿ��Ѿ���ȷ��
	//������
	//		b:�Ƿ��Ѿ���ȷ��
	//����ֵ����
	void setConfirmed(bool b)
	{
		_bConfirmed = b;
	}
	//shisx���Է��������ͬ��Ļ��ⰴť��ʽ
	//���ð�ťΪ���ⰴť
	//������
	//����ֵ����
	void SetMutexButton(){_bMutexButton = true;}
	//��ð�ť�Ƿ�Ϊ���ⰴť
	//������
	//����ֵ���ǻ��ⰴť����true,���򷵻�false
	bool IsMutexButton(){return _bMutexButton;}
	//���ð�ť�Ļ�������
	//������
	//		box:��������ָ��
	//����ֵ����
	void SetMutexBox(void* box){_pMutexBox = box;}
	//��ð�ť�Ļ�������
	//������
	//����ֵ����ť�Ļ�������ָ��
	void* GetMutexBox(){return _pMutexBox;}
signals:
	void availabled();
private:
	bool _bAvailable;
	bool _bNeedToConfirm;
	bool _bConfirmed;
	//shisx
	bool _bMutexButton;
	void* _pMutexBox;
};

#endif


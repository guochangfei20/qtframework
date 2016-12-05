/*!
 * \file sl_MutexButtonBox.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <vector>
#include <string>
#include "Common/qtframework_com.h"
//#include <QWidget>

using namespace std;
class sl_Button;
class ui_node;
class QWidget;
class TriStateBtnClickListener;
/*!
 * \class sl_MutexButtonBox
 *
 * \brief ���ⰴť����
 *
 * \author ����
 * \date ���� 2016
 */
class QTFRAMEWORK_EXPORT  sl_MutexButtonBox
{
public:
	//���캯��
	//��������
	//����ֵ����
	sl_MutexButtonBox(void);
	//��������
	//��������
	//����ֵ����
	~sl_MutexButtonBox(void);
	//����Ӱ�ť
	//������
	//		index:�Ӱ�ť����
	//����ֵ���԰�ťָ��
	sl_Button* getChildButton(int index)
	{
		return _childs.at(index);
	}
	//��ť����
	//��������
	//����ֵ����ť����
	int buttonNum(){return _childs.size();}
	//����Ӱ�ť
	//������
	//		w:��ťָ��
	//����ֵ����
	void addChildButton(sl_Button* w);
	//��ʼ������
	//��������
	//����ֵ����
	void init();
	//���ü�����
	//������
	//		listener:������
	//����ֵ����
	void setListener(TriStateBtnClickListener* listener){_listener = listener;}
	//����Ӱ�ť�б�
	//��������
	//����ֵ���Ӱ�ť�б�
	sl_Button** getChildren(){return _childs.data();}
	//���ð�ť�������ʽ
	//������
	//		style:��ť�������ʽ
	//����ֵ����
	void setButtonActivatedStyle(const char* style);
	//���ð�ť��������ʽ
	//������
	//		style:��ť��������ʽ
	//����ֵ����
	void setButtonNormalStyle(const char* style);
	//���ð�ť���ѡ�����ʽ
	//������
	//		style:��ť��ѡ�����ʽ
	//����ֵ����
	void setButtonSelectedStyle(const char* style);
	void setCurrentButton();
	
	sl_Button* selectedButton();
private:
	typedef vector<sl_Button*> ButtonVectorType;
	ButtonVectorType _childs;
	TriStateBtnClickListener* _listener;
	std::string _btnActivatedStyle;
	std::string _btnNormalStyle;
	std::string _btnSelectedStyle;
};


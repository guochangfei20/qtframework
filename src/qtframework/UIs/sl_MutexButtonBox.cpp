#include "UIs/sl_MutexButtonBox.h"
#include "TriStateBtnClickListener.h"
#include "UIs/sl_Button.h"
#include "Res/R.h"
#include "Utils/util.h"
//���캯��
//��������
//����ֵ����
sl_MutexButtonBox::sl_MutexButtonBox(void):_listener(NULL)
{
	_btnSelectedStyle = R::Instance()->getStyleResource("BlueButtonStyle");
	_btnNormalStyle = "";
	_btnActivatedStyle = R::Instance()->getStyleResource("GreenButtonStyle");
}

//��������
//��������
//����ֵ����
sl_MutexButtonBox::~sl_MutexButtonBox(void)
{
}
//���ð�ť�������ʽ
//������
//		style:��ť�������ʽ
//����ֵ����
void sl_MutexButtonBox::setButtonActivatedStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnActivatedStyle = stylesheet;
	}
}
//���ð�ť��������ʽ
//������
//		style:��ť��������ʽ
//����ֵ����
void sl_MutexButtonBox::setButtonNormalStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnNormalStyle = stylesheet;
	}
	
}
//���ð�ť���ѡ�����ʽ
//������
//		style:��ť��ѡ�����ʽ
//����ֵ����
void sl_MutexButtonBox::setButtonSelectedStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnSelectedStyle = stylesheet;
	}
}
//����Ӱ�ť
//������
//		w:��ťָ��
//����ֵ����
void sl_MutexButtonBox::addChildButton(sl_Button* w)
{
	_childs.push_back(w);
	w->SetMutexBox((void*)this);
	w->SetMutexButton();
	if (_listener)
	{
		w->addClickListener(_listener);
	}
}
//��ʼ������
//��������
//����ֵ����
void sl_MutexButtonBox::init()
{
	if (!_listener)
	{
		_listener = new TriStateBtnClickListener(this);
		_listener->setButtonActivedStyle(_btnActivatedStyle.c_str());
		_listener->setButtonNormalStyle(_btnNormalStyle.c_str());
		_listener->setButtonSelectedStyle(_btnSelectedStyle.c_str());
	}
}


sl_Button* sl_MutexButtonBox::selectedButton()
{
	return _listener->selectedBtn();
}
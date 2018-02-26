#include <UIs/sl_Button.h>
#include <UIs/ClickListenser.h>
#include <string.h>
#include <QtGui>
#include <Utils/util.h>
#include <Common/app_env.h>
//���캯��
//��������
//����ֵ����
sl_Button::sl_Button():QPushButton(),_bAvailable(true),_bNeedToConfirm(false),_bConfirmed(false)
{
	_bMutexButton = false;
}

////��������
//��������
//����ֵ����
sl_Button::~sl_Button()
{
}
//��Ӽ�����
//������
//		listenser:������
//����ֵ����
void sl_Button::addClickListener(ClickListenser* listenser)
{
	QObject::connect(this,SIGNAL(clicked()),listenser,SLOT(trigger()));
}
//�Ƴ�������
//������
//		listenser:������
//����ֵ����
void sl_Button::removeClickListenser(ClickListenser* listenser)
{
	this->disconnect(listenser);
}
//���ð�ť��ʽ
//������
//		style:��ʽ
//����ֵ����
void sl_Button::setStyle(const char* style)
{
	setStyleSheet(style);
}

void sl_Button::setStyle(std::string style)
{
	setStyle(style.c_str());
}

//���ð�ťicon
//������
//		icon:icon·��
//����ֵ����
void sl_Button::setIcon(const char* icon)
{
	string iconStr = icon;
	std::string url;
	if (iconStr.find("@icon/")!=std::string::npos)
	{
		getResIconUrl(url,iconStr.c_str());
		
	}
	else if (iconStr.find("@image/")!=std::string::npos)
	{
		getResImageUrl(url,iconStr.c_str());
	}
	else
	{
		url = app_env::getImageResDir();
		url.append(icon);
	}
	if (!url.empty())
	{
		QPushButton::setIcon(QIcon(url.c_str()));
	}
}
//���ð�ť����ͼƬ
//������
//		resImg:ͼƬ·��
//����ֵ����
void sl_Button::setBackgroundImage(const char* resImg)
{

}

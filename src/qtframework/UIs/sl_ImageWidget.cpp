#include <UIs/sl_ImageWidget.h>
#include "Utils/util.h"
//���캯��
//��������
//����ֵ����
sl_ImageWidget::sl_ImageWidget(void):_filename(""),_width(20),_height(20)
{
	setWidth(_width);
	setHeight(_height);
}
//���캯��
//������
//		imgFileName��ͼƬ·��
//����ֵ����
sl_ImageWidget::sl_ImageWidget(const char* imgFileName):_filename(imgFileName),_width(20),_height(20)
{
	setWidth(_width);
	setHeight(_height);
	setImage(_filename.c_str());
}
//���캯��
//������
//		w��ͼƬ���
//		h��ͼƬ�߶�
//����ֵ����
sl_ImageWidget::sl_ImageWidget(int w,int h):_filename(""),_width(w),_height(h)
{
	setWidth(_width);
	setHeight(_height);
}
//���캯��
//������
//		imgFileName��ͼƬ·��
//		w��ͼƬ���
//		h��ͼƬ�߶�
//����ֵ����
sl_ImageWidget::sl_ImageWidget(const char* imgFileName,int w,int h):_filename(imgFileName),_width(w),_height(h)
{
	setWidth(_width);
	setHeight(_height);
	setImage(_filename.c_str());
}

////��������
//��������
//����ֵ����
sl_ImageWidget::~sl_ImageWidget(void)
{
}
//����image·��������setImage("@image/***.png")����setImage("res/images/***.png")
	//������
	//		imgFileName��ͼƬ·��
	//����ֵ����
void sl_ImageWidget::setImage(const char* imgFileName)
{
	std::string url;
	getResImageOrIconUrl(url,imgFileName);
	if (!url.empty())
	{
		this->setPixmap(QPixmap(url.c_str()).scaled(_width,_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}else
	{
		this->setPixmap(QPixmap(imgFileName).scaled(_width,_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	
}
//����image���
//������
//		w��ͼƬ���
//����ֵ����
void sl_ImageWidget::setWidth(int w)
{
	_width = w;
	setFixedWidth(_width);
}
//����image�߶�
//������
//		h��ͼƬ�߶�
//����ֵ����
void sl_ImageWidget::setHeight(int h)
{
	_height = h;
	setFixedHeight(_height);
}

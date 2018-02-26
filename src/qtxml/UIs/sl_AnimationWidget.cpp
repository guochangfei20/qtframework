#include <UIs/sl_AnimationWidget.h>
#include <QMovie>
#include "Utils/util.h"
#include "Utils/Log.h"
//���캯��
//��������
//����ֵ����
sl_AnimationWidget::sl_AnimationWidget(void):_filename(""),_width(50),_height(50),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
}
//���캯��
//������
//		filename:�����ļ�·��
//����ֵ����
sl_AnimationWidget::sl_AnimationWidget(const char* filename):_filename(filename),_width(50),_height(50),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
	setAnimation(_filename.c_str());
}
//���캯��
//������
//		w���������
//		h�������߶�
//����ֵ����
sl_AnimationWidget::sl_AnimationWidget(int w,int h):_filename(""),_width(w),_height(h),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
}
//���캯��
//������
//		imgFileName������·��
//		w���������
//		h�������߶�
//����ֵ����
sl_AnimationWidget::sl_AnimationWidget(const char* filename,int w,int h):_filename(filename),_width(w),_height(h),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
	setAnimation(_filename.c_str());
}
////��������
//��������
//����ֵ����
sl_AnimationWidget::~sl_AnimationWidget(void)
{
}
//���ö���·��������setAnimation("@image/***.gif")����setAnimation("res/images/***.gif")
	//������
	//		filename������·��
	//����ֵ����
void sl_AnimationWidget::setAnimation(const char* filename)
{
	std::string url;
	getResImageOrIconUrl(url,filename);
	_movie->setFileName(url.c_str());
	if (_movie->isValid())
	{
		_movie->setCacheMode(QMovie::CacheAll);
		setMovie(_movie);
		_movie->start();
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Could not find plugin to read %s\n",url.c_str());
		printf(szMsg);
	}
	_bAnimationLoaded = true;
}
//���ö������
//������
//		w���������
//����ֵ����
void sl_AnimationWidget::setWidth(int w)
{
	_width = w;
	setFixedWidth(_width);
	QSize size = _movie->scaledSize();
	_movie->setScaledSize(QSize(_width,size.height()));
	if (_bAnimationLoaded)
	{
		setAnimation(_filename.c_str());
	}

}
//���ö����߶�
//������
//		h�������߶�
//����ֵ����
void sl_AnimationWidget::setHeight(int h)
{
	_height = h;
	setFixedHeight(_height);
	QSize size = _movie->scaledSize();
	_movie->setScaledSize(QSize(size.width(),_height));
	if (_bAnimationLoaded)
	{
		setAnimation(_filename.c_str());
	}
}
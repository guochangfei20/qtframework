/*!
 * \file sl_AnimationWidget.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#pragma once
#include <QLabel>

class QMovie;
/*!
 * \class sl_AnimationWidget
 *
 * \brief sl_AnimationWidget��
 *
 * \author ����
 * \date ���� 2016
 */
class sl_AnimationWidget:public QLabel
{
public:
	//���캯��
	//������
	//		filename:�����ļ�·��
	//����ֵ����
	sl_AnimationWidget(const char* filename);
	//���캯��
	//������
	//		w���������
	//		h�������߶�
	//����ֵ����
	sl_AnimationWidget(int w,int h);
	//���캯��
	//������
	//		imgFileName������·��
	//		w���������
	//		h�������߶�
	//����ֵ����
	sl_AnimationWidget(const char* filename,int w,int h);
	//���캯��
	//��������
	//����ֵ����
	sl_AnimationWidget(void);
	////��������
	//��������
	//����ֵ����
	~sl_AnimationWidget(void);
	//���ö���·��������setAnimation("@image/***.gif")����setAnimation("res/images/***.gif")
	//������
	//		filename������·��
	//����ֵ����
	void setAnimation(const char* filename);
	//���ö������
	//������
	//		w���������
	//����ֵ����
	void setWidth(int w);
	//���ö����߶�
	//������
	//		h�������߶�
	//����ֵ����
	void setHeight(int h);
	//��ö������
	//��������
	//����ֵ���������
	int getWidth(){return _width;}
	//��ö����߶�
	//��������
	//����ֵ�������߶�
	int getHeight(){return _height;}
private:
	int _width;
	int _height;
	std::string _filename;
	QMovie* _movie;
	bool _bAnimationLoaded;
};

#endif


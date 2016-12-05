/*!
 * \file sl_ImageWidget.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef SL_IMAGEWIDGET_H
#define SL_IMAGEWIDGET_H

#pragma once
#include <QLabel>
#include "Common/qtframework_com.h"
/*!
 * \class sl_ImageWidget
 *
 * \brief ͼƬ�ؼ�
 *
 * \author ����
 * \date ���� 2016
 */
class QTFRAMEWORK_EXPORT sl_ImageWidget : public QLabel
{
public:
	//���캯��
	//������
	//		imgFileName��ͼƬ·��
	//����ֵ����
	sl_ImageWidget(const char* imgFileName);
	//���캯��
	//������
	//		w��ͼƬ���
	//		h��ͼƬ�߶�
	//����ֵ����
	sl_ImageWidget(int w,int h);
	//���캯��
	//������
	//		imgFileName��ͼƬ·��
	//		w��ͼƬ���
	//		h��ͼƬ�߶�
	//����ֵ����
	sl_ImageWidget(const char* imgFileName,int w,int h);
	//���캯��
	//��������
	//����ֵ����
	sl_ImageWidget(void);
	////��������
	//��������
	//����ֵ����
	~sl_ImageWidget(void);
	//����image·��������setImage("@image/***.png")����setImage("res/images/***.png")
	//������
	//		imgFileName��ͼƬ·��
	//����ֵ����
	void setImage(const char* imgFileName);
	//����image���
	//������
	//		w��ͼƬ���
	//����ֵ����
	void setWidth(int w);
	//����image�߶�
	//������
	//		h��ͼƬ�߶�
	//����ֵ����
	void setHeight(int h);
	//���image���
	//��������
	//����ֵ��ͼƬ���
	int getWidth(){return _width;}
	//���image�߶�
	//��������
	//����ֵ��ͼƬ�߶�
	int getHeight(){return _height;}
private:
	int _width;
	int _height;
	std::string _filename;
};

#endif


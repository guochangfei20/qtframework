/*!
 * \file qt_context.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef QT_CONTEXT_H
#define QT_CONTEXT_H

#pragma once
#include <vector>
#include "Common/qtxml_com.h"
struct sl_Rect
{
	int x0;
	int y0;
	int x1;
	int y1;
	int w;
	int h;
};

class QApplication;
class QTranslator;
/*!
 * \class qt_context
 *
 * \brief qt_context��
 *
 * \author ����
 * \date ���� 2016
 */
class QTXML_EXPORT qt_context
{
public:
	//���캯��
	//������app QApplicationָ��
	//����ֵ����
	qt_context(QApplication* app);
	//��������
	~qt_context(void);
	//getter
	//�����Ļ����
	//��������
	//����ֵ����Ļ����
	static int getScreenNum(){return _screenNum;}
	//�����Ļ��С
	//������
	//		i: ��Ļ����
	//����ֵ����Ļ��С
	static sl_Rect* getScreenRect(int i){return _screenRects.at(i);}
	//�����Ļ���
	//������
	//		i: ��Ļ����
	//����ֵ����Ļ���
	static int getScreenWidth(int i);
	//�����Ļ�߶�
	//������
	//		i: ��Ļ����
	//����ֵ����Ļ�߶�
	static int getScreenHeight(int i);
	//����application�����ʽ
	//������
	//		coding: �����ʽ
	//����ֵ���Ƿ����óɹ�
	static bool setApplicationCoding(const char* coding);
	//����applicationĬ������
	//������
	//		languageStr: ��������
	//����ֵ���Ƿ����óɹ�
	static bool setDefaultLanguage(const char* languageStr);
	//����application��ʽ
	//������
	//		style: ��ʽ
	//����ֵ����
	static void setApplicationStyle(const char* style);
	//��Ӷ�̬�����Ŀ¼
	//������
	//		path�� ·��
	//����ֵ����
	static void addLibraryPath(const char* path);
private:
	static int _screenNum; //��Ļ����
	static int _primaryScreen; //����Ļ
	static std::vector<sl_Rect*> _screenRects; //��Ļ�ߴ�����
	static QTranslator* _translator; //������
};

#endif


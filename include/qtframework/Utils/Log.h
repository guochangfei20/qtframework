/*!
 * \file Log.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef LOG_H
#define LOG_H

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "Common/qtframework_com.h"
using namespace std;
/*!
 * \class Log
 *
 * \brief Log��
 *
 * \author ����
 * \date ���� 2016
 */
class QTFRAMEWORK_EXPORT Log
{
public:
	//��־����
	enum LOG_TYPE
	{
		LOG_WARN,  //����
		LOG_ERROR, //����
		LOG_INFO   //��Ϣ
	};
	//дlog
	//������
	//	type:��־����
	//	fmt :��־����
	//����ֵ����
	void log(LOG_TYPE type,const char* fmt,...);
	//��ʼ��log�ļ�
	//��������
	//����ֵ����
	bool init();
	//����Ƿ���log
	//��������
	//����ֵ����������true�����򷵻�false
	bool getEnabled(){return _bEnabled;}
	//�����Ƿ���log
	//������
	//		b:�Ƿ���log
	//����ֵ����
	void setEnabled(bool b){_bEnabled = b;}
	//���Logʵ��
	//��������
	//����ֵ��ʵ��ָ��
	static Log* Instance()
	{
		if (_log == 0)
		{
			_log = new Log;
		}
		return _log;
	}
	
public:
	 //���������������ʵ��
	class Garbo
	{
	public:
		//���캯��
		Garbo(){}
		//��������
		~Garbo()
		{
			if (_log)
			{
				delete _log; //ɾ��Logʵ��
			}
		}
	};
private:
	//���캯��
	//��������
	//����ֵ����
	Log(void);
	//��������
	//��������
	//����ֵ����
	~Log(void);
	//���Ϊ�ַ���
	//������
	//		value:����
	//����ֵ���ַ���
	template<typename T> string valueToStr(T value)
	{
		ostringstream ost;
		ost<<value;
		return ost.str();
	}
	//���ʱ���ַ���
	//������
	//		ts:ʱ���ַ���
	//����ֵ����
	void getTimeStr(string& ts);
	//����Ƿ��log�ļ�
	//��������
	//����ֵ���򿪷���true�����򷵻�false
	bool getOpened(){return _bOpened;}
	//�����Ƿ��log�ļ�
	//������
	//		b:�Ƿ��log�ļ�
	//����ֵ����
	void setOpened(bool b){_bOpened = b;}
	//��log�ļ�
	//��������
	//����ֵ����
	bool open();
	//�ر�log�ļ�
	//��������
	//����ֵ����
	void close();
	bool _bEnabled;
	bool _bOpened;
	std::ofstream _oLogFile;
	string _logFilename;

	static Log* _log;
	static Garbo _garbo;
};

#endif

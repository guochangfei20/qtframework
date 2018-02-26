/*!
 * \file res_string.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include "Res/xml_res_base.h"
#include <vector>
using namespace std;
/*!
 * \class res_string
 *
 * \brief res_string��
 *
 * \author ����
 * \date ���� 2016
 */
class res_string  :public xml_res_base
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_string(void);
	//��������
	//��������
	//����ֵ����
	~res_string(void);
	//���String��Դ
	//������id ID
	//����ֵ����Դ
	const char* getStringRes(const char* id);
	vector<string> getStringListRes(const char* id);
private:
    virtual void releaseResource();
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	void parseXML(const char* filename);
	typedef map<string,string> StringMapType;
	typedef map< string,vector<string> > StringListMapType;
	StringMapType _res_map;
	StringListMapType _resList_map;
};


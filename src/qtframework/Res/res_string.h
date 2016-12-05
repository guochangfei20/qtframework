/*!
 * \file res_string.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <map>
#include <string>
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
class res_string
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
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	const char* parseStringXML(const char* filename);
	typedef map<string,string> StringMapType;
	typedef map< string,vector<string> > StringListMapType;
	StringMapType _res_map;
	StringListMapType _resList_map;
};


/*!
 * \file res_config.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <map>
#include <string>
using namespace std;
class variant;
//class ui_node;
/*!
 * \class res_config
 *
 * \brief res_config��
 *
 * \author ����
 * \date ���� 2016
 */
class res_config
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_config(void);
	//��������
	//��������
	//����ֵ����
	~res_config(void);
	//��������ļ��е�������Դ
	//������
	//		id:ID
	//����ֵ����Դ
	variant* getConfigRes(const char* id);
	//���������ļ��е�������Դ
	//������
	//		id��ID
	//		v:ֵ
	//����ֵ���Ƿ����óɹ�
	bool setConfigRes(const char* id,variant* v);
	//��������ļ��е�������Դ
	//������
	//		id��ID
	//		v:ֵ
	//����ֵ���Ƿ���ӳɹ�
	void addConfigRes(const char* id,variant* v);
	//����Config��Դ
	//��������
	//����ֵ����
	void writeConfigFile();
private:
	//���������ļ�xml
	//������
	//	filename:�ļ�·��
	//����ֵ����
	const char* parseConfigXML(const char* filename);
	typedef map<string,variant*> ConfigPropertyMapType;
	ConfigPropertyMapType _res_map;
	ConfigPropertyMapType _change_map;
	//ui_node* _res_root;
};


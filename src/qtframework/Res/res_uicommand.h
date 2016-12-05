/*!
 * \file res_uicommand.h
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

class xml_node;
/*!
 * \class res_uicommand
 *
 * \brief res_uicommand��
 *
 * \author ����
 * \date ���� 2016
 */
class res_uicommand
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_uicommand(void);
	//��������
	//��������
	//����ֵ����
	~res_uicommand(void);
	//���UICommand��Դ
	//������id ID
	//����ֵ����Դ
	xml_node* getUICommandRes(const char* id);

private:
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	void parseUICommandXML(const char* filename);
	map<string,xml_node*> _res_map;
};

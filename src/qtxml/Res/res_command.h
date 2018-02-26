/*!
 * \file res_uicommand.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include "Res/xml_res_base.h"
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
class res_command :public xml_res_base
{
public:
	//���캯��
	//��������
	//����ֵ����
    res_command(void);
	//��������
	//��������
	//����ֵ����
	~res_command(void);
	//���UICommand��Դ
	//������id ID
	//����ֵ����Դ
    xml_node* getCommandRes(const char* id);
    virtual void releaseResource();
    
private:
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	void parseXML(const char* filename);
    typedef   map< string, xml_node* > XMLNodeMapType;
    XMLNodeMapType _res_map;
    
};

/*!
 * \file xml_ui_paser.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <string>
#include <Utils/tinyxml2.h>
//#include "ui_node.h"

class ui_node;
/*!
 * \class xml_ui_paser
 *
 * \brief xml_ui_paser��
 *
 * \author ����
 * \date ���� 2016
 */
class xml_ui_paser
{
public:
	//���캯��
	//��������
	//����ֵ����
	xml_ui_paser();
	//��������
	//��������
	//����ֵ����
	~xml_ui_paser();
	//����xml�ļ�
	//��������
	//����ֵ���Ƿ�����ɹ�
	static bool parserXML(const char* filename,ui_node* root);
protected:
	//��ýڵ���
	//������
	//		node: xmlNodePtr�ڵ�
	//		uinode: ui_node�ڵ�
	//����ֵ����
	static void getXMLList(tinyxml2::XMLNode* node,ui_node* uinode);

private:
    static std::string _currentFileName;
};


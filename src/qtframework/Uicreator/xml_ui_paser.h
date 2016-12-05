/*!
 * \file xml_ui_paser.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <string>
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
	//���캯��
	//������
	//		filename: �������ļ�·��
	//����ֵ����
	xml_ui_paser(const char* filename);
	//��������
	//��������
	//����ֵ����
	~xml_ui_paser();
	//����xml�ļ�
	//��������
	//����ֵ���Ƿ�����ɹ�
	bool parserXML();
	//��ýڵ������ڵ�
	//��������
	//����ֵ���ڵ������ڵ�ָ��
	ui_node* getRoot();
	//���ýڵ������ڵ�
	//������
	//		root:�ڵ������ڵ�ָ��
	//����ֵ����
	void setRoot(ui_node* root){_root = root; };
	//���ý�����xml�ļ�
	//������
	//		filename:������xml�ļ�·��
	//����ֵ����
	void setFileName(const char* filename){_filename=filename;}
protected:
	//��ýڵ���
	//������
	//		node: xmlNodePtr�ڵ�
	//		uinode: ui_node�ڵ�
	//����ֵ����
	void getXMLList(xmlNodePtr node,ui_node* uinode);
	//����xmlNodePtr�ڵ�� ui_node�ڵ�
	//������
	//		node: xmlNodePtr�ڵ�
	//		uinode: ui_node�ڵ�
	//����ֵ����
	void relateXMLNodeAndUINode(xmlNodePtr xmlnode,ui_node* uinode);
private:
	std::string _filename;
	ui_node* _root;
	ui_node* _curnode;
};


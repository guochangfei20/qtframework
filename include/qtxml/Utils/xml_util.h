/*!
 * \file xml_util.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include "Utils/tinyxml2.h"
#include <Uicreator/ui_node.h>
using namespace std;
/*!
 * \class class xml_util
 *
 * \brief class xml_util��
 *
 * \author ����
 * \date ���� 2016
 */
class xml_util
{
public:
	//���캯��
	//��������
	//����ֵ����
	xml_util(void);
	//��������
	//��������
	//����ֵ����
	~xml_util(void);
	//ת��Ϊxml�ڵ���
	//������
	//		root:ui_node�ڵ���ָ��
	//		xmlRoot:xmlNode�ڵ���ָ��
	//����ֵ����
	static void convertToXMLDoc(ui_node* root,tinyxml2::XMLDocument& xmlDoc);
	//����ui_node��xmlNodeָ��
	//������
	//		node:ui_node�ڵ���ָ��
	//		xmlNode:xmlNode�ڵ���ָ��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool relate(ui_node* node, tinyxml2::XMLNode* xmlNode);
	//��xmlNode�ڵ�������xml�ļ�
	//������
	//		xmlRoot:xmlNode�ڵ���ָ��
	//		filename:xml�ļ�·��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool writeToFile(tinyxml2::XMLDocument& xmlDoc,const char* filename);
	//��ui_node�ڵ�������xml�ļ�
	//������
	//		xmlRoot:ui_node�ڵ���ָ��
	//		filename:xml�ļ�·��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool writeToFile(ui_node* root,const char* filename);


    //���xml�ļ����ڵ�
    //������
    //	filename:xml�ļ�·��
    //	root:xml���ڵ�
    //����ֵ����óɹ�����true,���򷵻�false
    static bool getXMLFileRoot(const char* filename, xml_node* root);
protected:
	//�����ڵ���
	//������
	//		node:ui_node�ڵ���ָ��
	//		xmlNode:xmlNode�ڵ���ָ��
	//����ֵ����
	static void parseTree(ui_node* node, tinyxml2::XMLNode* xmlNode, tinyxml2::XMLDocument& xmlDoc);
};

/*!
 * \file xml_util.h
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
	//���XPath����ָ��
	//������
	//		doc:�ĵ�ָ��
	//		xpath:�ĵ�·��
	//����ֵ��XPath����ָ��
	friend inline xmlXPathObjectPtr getXmlNodeSet(xmlDocPtr doc,const xmlChar* xpath);
	//ת��Ϊxml�ڵ���
	//������
	//		root:ui_node�ڵ���ָ��
	//		xmlRoot:xmlNode�ڵ���ָ��
	//����ֵ����
	static void convertToXMLTree(ui_node* root,xmlNodePtr xmlRoot);
	//����ui_node��xmlNodeָ��
	//������
	//		node:ui_node�ڵ���ָ��
	//		xmlNode:xmlNode�ڵ���ָ��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool relate(ui_node* node,xmlNodePtr xmlNode);
	//��xmlNode�ڵ�������xml�ļ�
	//������
	//		xmlRoot:xmlNode�ڵ���ָ��
	//		filename:xml�ļ�·��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool writeToFile(xmlNodePtr xmlRoot,const char* filename);
	//��ui_node�ڵ�������xml�ļ�
	//������
	//		xmlRoot:ui_node�ڵ���ָ��
	//		filename:xml�ļ�·��
	//����ֵ�������ɹ�����true,���򷵻�false
	static bool writeToFile(ui_node* root,const char* filename);
protected:
	//�����ڵ���
	//������
	//		node:ui_node�ڵ���ָ��
	//		xmlNode:xmlNode�ڵ���ָ��
	//����ֵ����
	static void parseTree(ui_node* node,xmlNodePtr xmlNode);
};

xmlXPathObjectPtr getXmlNodeSet(xmlDocPtr doc,const xmlChar* xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(doc);
	if (context==NULL)
	{
		return NULL;
	}
	result = xmlXPathEvalExpression(xpath,context);
	xmlXPathFreeContext(context);
	if (result==NULL)
	{
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
		return NULL;
	}
	return result;
}
#include "xml_ui_paser.h"
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include <iostream>
#include <string.h>
#include "Utils/util.h"
//���캯��
//��������
//����ֵ����
xml_ui_paser::xml_ui_paser()
{	
}
//���캯��
//������
//		filename: �������ļ�·��
//����ֵ����
xml_ui_paser::xml_ui_paser(const char* filename)
	:_filename(std::string(filename)),_root(NULL)

{
}
//��������
//��������
//����ֵ����
xml_ui_paser::~xml_ui_paser()
{
    _root->release();//���������ڵ� 20150925
}

//����xml�ļ�
//��������
//����ֵ���Ƿ�����ɹ�
bool xml_ui_paser::parserXML()
{

	xmlKeepBlanksDefault(0);
	xmlDocPtr doc;
	logFileOrPathExist(_filename.c_str(),Log::LOG_ERROR);
	doc = xmlReadFile(_filename.c_str(),"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return false;
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (!curXMLNode)
	{
		return false;
	}
	if (!_root)
	{
		_root = new ui_node;
	}
	_curnode = _root;
	//relateXMLNodeAndUINode(curXMLNode,_curnode);
	_curnode->relateXMLNode(curXMLNode);
	getXMLList(curXMLNode,_curnode);
	xmlFreeDoc(doc);
	return true;
}
//����xmlNodePtr�ڵ�� ui_node�ڵ�
//������
//		node: xmlNodePtr�ڵ�
//		uinode: ui_node�ڵ�
//����ֵ����
void xml_ui_paser::relateXMLNodeAndUINode(xmlNodePtr xmlnode,ui_node* uinode)
{
	xmlAttr* attr = xmlnode->properties;
	uinode->setName((const char*)xmlnode->name);
	
	while(attr!=NULL)
	{
		uinode->addAttribute((const char*)attr->name,(const char*)attr->children->content);
		attr = attr->next;
	}
}
//��ýڵ���
//������
//		node: xmlNodePtr�ڵ�
//		uinode: ui_node�ڵ�
//����ֵ����
void xml_ui_paser::getXMLList(xmlNodePtr node,ui_node* uinode)
{
	if (node->children != NULL)
	{
		xmlNodePtr child = node->children;
		for (;child;child = child->next)
		{
			
			if (child->type == XML_ELEMENT_NODE)
			{
				ui_node* un = new ui_node;
				//relateXMLNodeAndUINode(child,un);  //����
				un->relateXMLNode(child);
				//�����Holder��ȥ��Դ�����ö�Ӧ�Ľڵ���������������������ֹassembler���洦��Holder���ֵݹ���ҵ�����
				if (strcmp(un->getName(),"Holder")==0&&un->hasAttribute("id")) 
				{
					std::string res = un->getAttribute("id");
					int i = res.find_first_of("@ui/");
					res = res.substr(i+4);
					ui_node* node = R::Instance()->getUIResource(res.c_str());
					if (node)
					{
						un->clone(node);
					}	
				}
				uinode->addChild(un);
				std::string content = (char*)xmlNodeGetContent(child);
				getXMLList(child,un);
			}
		}
	}
}
//��ýڵ������ڵ�
//��������
//����ֵ���ڵ������ڵ�ָ��
ui_node* xml_ui_paser::getRoot()
{
	return _root;
}


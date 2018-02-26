#include "xml_ui_paser.h"
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include <iostream>
#include <string.h>
#include "Utils/util.h"
//���캯��
//��������
//����ֵ����

std::string xml_ui_paser::_currentFileName = "";
xml_ui_paser::xml_ui_paser()
{	
}
//��������
//��������
//����ֵ����
xml_ui_paser::~xml_ui_paser()
{
}

//����xml�ļ�
//��������
//����ֵ���Ƿ�����ɹ�
bool xml_ui_paser::parserXML(const char* filename, ui_node* root)
{
    if (!root)
    {
        return false;
    }
    tinyxml2::XMLDocument doc;
	logFileOrPathExist(filename);
    tinyxml2::XMLError error=doc.LoadFile(filename);
	if (error != tinyxml2::XML_SUCCESS)
	{
        std::cout << "Load xml file " << filename << " failed! " << "Error code: " << doc.ErrorStr() << std::endl;
		return false;
	}
    _currentFileName = filename;
    tinyxml2::XMLNode* curXMLNode = doc.RootElement();
	if (!curXMLNode)
	{
		return false;
	}
    root->relateXMLNode(curXMLNode);
	getXMLList(curXMLNode, root);
    
    _currentFileName = "";
	return true;
}
//��ýڵ���
//������
//		node: xmlNodePtr�ڵ�
//		uinode: ui_node�ڵ�
//����ֵ����
void xml_ui_paser::getXMLList(tinyxml2::XMLNode* node,ui_node* uinode)
{
	if (!node->NoChildren())
	{
		tinyxml2::XMLNode* child = node->FirstChild();
		for (;child;child = child->NextSiblingElement())
		{
			ui_node* un = new ui_node;
			un->relateXMLNode(child);
            un->setFilename(_currentFileName.c_str());
            if (child->ToElement())
            {
                //�����Holder��ȥ��Դ�����ö�Ӧ�Ľڵ���������������������ֹassembler���洦��Holder���ֵݹ���ҵ�����
                if (strcmp(un->getName(), "Holder") == 0 && un->hasAttribute("id"))
                {
                    std::string res = un->getAttribute("id");
                    int i = res.find_first_of("@ui/");
                    res = res.substr(i + 4);
                    ui_node* node = R::Instance()->getUIResource(res.c_str());
                    if (node)
                    {
                        un->clone(node);
                    }
                }
            }
			uinode->addChild(un);
			getXMLList(child,un);
		}
	}
}


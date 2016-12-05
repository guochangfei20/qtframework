#include "xml_node.h"
//���캯��
//��������
//����ֵ����
xml_node::xml_node(void):_parent(NULL)
{
	
}

//��������
//��������
//����ֵ����
xml_node::~xml_node(void)
{
}
//�ͷŽڵ㼰�ӽڵ�
//��������
//����ֵ����
void xml_node::release()
{//20150925
	for (list<xml_node*>::iterator itor = _childs.begin();itor!=_childs.end();itor++ )
	{
		xml_node* child = *itor;
		if (child !=NULL)
		{
			child->release();
		}
	}
	delete this;
}
//�������
//������
//		key: ��ֵ
//����ֵ�������ַ���
const char* xml_node::getAttribute(const char* key)
{
	map<string,string>::iterator it = _attributes.find(key);
	if (it!=_attributes.end())
	{
		return it->second.c_str();
	}else
	{
		return "";
	}
}
//�Ƿ��������
//������
//		key: ��ֵ
//����ֵ������key���Է���true�����򷵻�false
bool xml_node::hasAttribute(const char* key)
{
	if (_attributes.count(key))
	{
		return true;
	}else
	{
		return false;
	}
}
//����ӽڵ�
//������
//		node: �ӽڵ�ָ��
//����ֵ����
void xml_node::addChild(xml_node* node)
{
	_childs.push_back(node);
	node->setParent(this);
}
//����ӽڵ�
//������
//		index: �ӽڵ�����
//����ֵ���ӽڵ�ָ��
xml_node* xml_node::getChild(int index)
{
	list<xml_node*>::iterator itor = _childs.begin();
	while(index !=0 )
	{
		itor++;
		index--;
	}
	if (*itor!=NULL)
	{
		return *itor;
	}else
	{
		return NULL;
	}
}
//���ø��ڵ�
//������
//		node: ���ڵ�ָ��
//����ֵ����
void xml_node::setParent(xml_node* node)
{
	_parent = node;
}
//��ø��ڵ�
//��������
//����ֵ�����ڵ�ָ��
xml_node* xml_node::getParent()
{
	return _parent;
}
//�������
//������
//		key: ��ֵ
//		value: ֵ
//����ֵ����
void xml_node::addAttribute(const char* key,const char* value) 
{
	_attributes[key] = value;
}
//���ڵ���xmlNode�ڵ�������������
//������
//		xmlNode: xmlNode�ڵ�ָ��
//����ֵ����
void xml_node::relateXMLNode(xmlNode* xmlnode)
{
	_xmlNode = xmlnode;
	xmlAttr* attr = xmlnode->properties;
	setName((const char*)xmlnode->name);
	setContent((char*)xmlNodeGetContent(xmlnode));
	while(attr!=NULL)
	{
		addAttribute((const char*)attr->name,(const char*)attr->children->content);
		attr = attr->next;
	}
	_id = hasAttribute("id")?getAttribute("id"):"NULL";
}
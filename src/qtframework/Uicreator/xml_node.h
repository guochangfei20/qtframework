/*!
 * \file xml_node.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <string>
#include <map>
#include <list>
#include <libxml/tree.h>
#include <Utils/variant.h>
using namespace std;
/*!
 * \class xml_node
 *
 * \brief xml_node��
 *
 * \author ����
 * \date ���� 2016
 */
class xml_node
{
public:
	//�������Ա�����
	typedef std::map<string,string> AttributeMapType;
    typedef std::map<string, variant> ParameterMapType;
	//���캯��
	//��������
	//����ֵ����
	xml_node(void);
	//��������
	//��������
	//����ֵ����
	~xml_node(void);
	//�ͷŽڵ㼰�ӽڵ�
	//��������
	//����ֵ����
	virtual void release();//20150925
	//����ӽڵ�
	//������
	//		node: �ӽڵ�ָ��
	//����ֵ����
	virtual void addChild(xml_node* node);
	//����ӽڵ�
	//������
	//		index: �ӽڵ�����
	//����ֵ���ӽڵ�ָ��
	virtual xml_node* getChild(int index);
	//����ӽڵ�����
	//��������
	//����ֵ���ӽڵ�����
	virtual int getChildNum(){return _childs.size();}
	//���ø��ڵ�
	//������
	//		node: ���ڵ�ָ��
	//����ֵ����
	virtual void setParent(xml_node* node);
	//��ø��ڵ�
	//��������
	//����ֵ�����ڵ�ָ��
	virtual xml_node* getParent();

	//���ýڵ�����
	//������
	//		name: �ڵ�����
	//����ֵ����
	virtual void setName(const char* name){_name = name;}
	//��ýڵ�����
	//��������
	//����ֵ���ڵ�����
	virtual const char* getName(){return _name.c_str();}
	//���ýڵ�����
	//������
	//		content: �ڵ�����
	//����ֵ����
	virtual void setContent(const char* content){_content = content;}
	//��ýڵ�����
	//��������
	//����ֵ���ڵ�����
	virtual const char* getContent(){return _content.c_str();}

	//�������
	//������
	//		key: ��ֵ
	//����ֵ�������ַ���
	virtual const char* getAttribute(const char* key);
	//�Ƿ��������
	//������
	//		key: ��ֵ
	//����ֵ������key���Է���true�����򷵻�false
	virtual bool hasAttribute(const char* key);
	//�������
	//������
	//		key: ��ֵ
	//		value: ֵ
	//����ֵ����
	virtual void addAttribute(const char* key,const char* value);
	//������Ա�
	//��������
	//����ֵ�����Ա�
	virtual AttributeMapType& getAttributeMap(){return _attributes;}
	//���ڵ���xmlNode�ڵ�������������
	//������
	//		xmlNode: xmlNode�ڵ�ָ��
	//����ֵ����
	virtual void relateXMLNode(xmlNode* xmlnode);
	//���xmlNode�ڵ�
	//��������
	//����ֵ��xmlNode�ڵ�ָ��
	xmlNode* getXMLNode(){return _xmlNode;}

    virtual void addParameter(const char* key, const variant& parameter);
    virtual ParameterMapType& getParameters() { return _parameters; }
protected:
	string _name;
	string _id;
	string _content;
	list<xml_node*> _childs; 
	xml_node* _parent;
	AttributeMapType _attributes;
    ParameterMapType _parameters;
	xmlNode* _xmlNode;
};


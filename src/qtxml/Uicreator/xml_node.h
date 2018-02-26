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
#include <Utils/variant.h>
#include "Utils/tinyxml2.h"
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
    enum XMLNodeType
    {
          ELEMENT,
          COMMENT,
          UNKNOWN
    };
	//�������Ա�����
	typedef std::map<std::string, std::string> AttributeMapType;
    typedef std::map<std::string, variant> ParameterMapType;
	//���캯��
	//��������
	//����ֵ����
	xml_node(void);
    //���ƹ��캯��
    //��������
    //����ֵ����
    xml_node(const xml_node& node);
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
	virtual void relateXMLNode(tinyxml2::XMLNode* xmlnode);

    virtual void setParameter(const char* key, const variant& parameter);
    virtual ParameterMapType& getParameters() { return _parameters; }
    virtual variant& getParameter(const char* key);


    int getLineNumber() { return _lineNum; }
    void setFilename(const char* filename) { _filename = filename; }
    const char* getFilename() { return _filename.c_str(); }

    //xml�ڵ�����
    XMLNodeType TypeOfXMLNode;
protected:
	std::string _name;
    std::string _id;
    std::string _content;
    std::list<xml_node*> _childs;
	xml_node* _parent;
	AttributeMapType _attributes;
    ParameterMapType _parameters;
    
    int _lineNum;
    std::string _filename;
    
};


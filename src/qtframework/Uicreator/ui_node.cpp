#include "ui_node.h"
//���캯��
//��������
//����ֵ����
ui_node::ui_node():_object(NULL),_uiParent(NULL)
{

}
//��������
//��������
//����ֵ����
ui_node::~ui_node()
{
	//if (_object!=NULL)
	//{
	//	delete _object;
	//	_object = NULL;
	//}
}
//�ͷŽڵ㼰�ӽڵ�
//��������
//����ֵ����
void ui_node::release()
{
	for (list<ui_node*>::iterator itor = _uiChildren.begin();itor!=_uiChildren.end();itor++ )
	{
		ui_node* child = *itor;
		if (child !=NULL)
		{
			child->release();
		}
	}
	delete this;
}
//�ϲ��������Ա�
//������
//		ta: Ŀ�����Ա�
//		fa: Դ���Ա�
//����ֵ����
void ui_node::mergeAttributes(AttributeMapType& ta,AttributeMapType& fa)
{
	typedef AttributeMapType::iterator ItorType;

	for (ItorType faItor = fa.begin();faItor!=fa.end();++faItor)
	{
		ta[faItor->first]=faItor->second;
	}
}
//���ƽڵ�
//������
//		node: Ҫ���ƵĽڵ�ָ��
//����ֵ����
void ui_node::clone(ui_node* node)
{
	this->_uiChildren = node->_uiChildren;
	this->_uiParent = node->_uiParent;
	this->_type = node->_type;
	this->_object = node->_object;
	this->_name = node->_name;
	this->_id = node->_id;
	//this->_attributes = node->_attributes;
	mergeAttributes(this->_attributes,node->_attributes); //�ϲ��������Լ����ظ������Ժ���ĻḲ��ǰ���
}
//����ӽڵ�
//������
//		node: �ӽڵ�ָ��
//����ֵ����
void ui_node::addChild(ui_node* node)
{
	_uiChildren.push_back(node);
	node->setParent(this);
}
//����ӽڵ�
//������
//		index: �ӽڵ�����
//����ֵ���ӽڵ�ָ��
ui_node* ui_node::getChild(int index)
{
	list<ui_node*>::iterator itor = _uiChildren.begin();
	//shisx ɾ��comboboxitem����ѭ��
	while(index > 0 )
	//while(index !=0 )
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
void ui_node::setParent(ui_node* node)
{
	_uiParent = node;
}
//��ø��ڵ�
//��������
//����ֵ�����ڵ�ָ��
ui_node* ui_node::getParent()
{
	return _uiParent;
}



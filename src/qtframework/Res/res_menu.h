/*!
 * \file res_menu.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <map>
#include <string>
using namespace std;
class ui_node;
/*!
 * \class res_menu
 *
 * \brief res_menu��
 *
 * \author ����
 * \date ���� 2016
 */
class res_menu
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_menu(void);
	//��������
	//��������
	//����ֵ����
	~res_menu(void);
	//����Ҽ��˵���Դ
	//������id ID
	//����ֵ�����ڵ�ָ��
	ui_node* getMenuRes(const char* id);
private:
	typedef map<string,ui_node*> ResMapType;
	ResMapType _res_map;
};


/*!
 * \file res_ui.h
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
 * \class res_ui
 *
 * \brief res_ui��
 *
 * \author ����
 * \date ���� 2016
 */
class res_ui
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_ui();
	//��������
	//��������
	//����ֵ����
	~res_ui();
	//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
	//������id ID
	//����ֵ���ڵ�ָ��
	ui_node* getUIRes(const char* id);
private:
	typedef map<string,ui_node*> ResMapType;
	ResMapType _res_map;
};


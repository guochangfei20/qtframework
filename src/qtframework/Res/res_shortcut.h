/*!
 * \file res_shortcut.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;
class xml_node;
/*!
 * \class res_shortcut
 *
 * \brief res_shortcut��
 *
 * \author ����
 * \date ���� 2016
 */
class res_shortcut
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_shortcut(void);
	//���캯��
	//��������
	//����ֵ����
	~res_shortcut(void);
	//��ÿ�ݼ���Դ
	//������name ID
	//����ֵ����Դ
	xml_node* getShortcutRes(const char* name);

private:
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	void parseShortcutXML(const char* filename);
	//ȫ��������
	//������inVec ��������, outVec �������, s ��ʼλ��, e��С
	//����ֵ����
	void perm(vector<string>& inVec,vector<string>& outVec,int s,int e);
	//�����ַ���
	//������s1 ����1, s2 ����2
	//����ֵ����
	void swap(string& s1,string& s2);
	//��ÿ�ݼ���Դ
	//������name ID
	//����ֵ����Դ
	xml_node* findRes(const char* name);
	typedef map<string,xml_node*> ShortcutMapType;
	ShortcutMapType _res_map;
	
	xml_node* _found_shortcut;
};


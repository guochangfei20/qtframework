#pragma once
#include <map>
#include <string>
using namespace std;

class res_style
{
public:
	//���캯��
	//��������
	//����ֵ����
	res_style(void);
	//��������
	//��������
	//����ֵ����
	~res_style(void);
	//���Style��Դ
	//������id ID
	//����ֵ����Դ
	const char* getStyleRes(const char* id);
	//���Application����ʽ
	//��������
	//����ֵ����Դ
	const char* getMainStyle();
private:
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	const char* parseStyleXML(const char* filename);
	//�����ڵ�Name
	//������str �ڵ�Name
	//����ֵ������ַ�
	const char* parseName(const char* str);
	//��������
	//������icontent ��������, ocontent �������, name �ڵ�Name
	//����ֵ������ַ�
	const char* parseContent(string& ocontent,const char* icontent,const char* name);
	typedef map<string,string> StyleMapType;
	StyleMapType _res_map;
};


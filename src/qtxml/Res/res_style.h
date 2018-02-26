#pragma once
#include "Res/xml_res_base.h"
using namespace std;

class res_style:public xml_res_base
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
    virtual void releaseResource();
	//���������ļ�xml
	//������filename �ļ�·��
	//����ֵ����
	void parseXML(const char* filename);
	//�����ڵ�Name
	//������str �ڵ�Name
	//����ֵ������ַ�
	const char* parseName(const char* str);
	//��������
	//������icontent ��������, ocontent �������, name �ڵ�Name
	//����ֵ������ַ�
	const char* parseContent(string& ocontent,const char* icontent,const char* name);

    void parseQSSResource();

	typedef map<string,string> StyleMapType;
	StyleMapType _res_map;
};


/*!
 * \file util.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <QString>
#include <QStringList>
#include <QObject>
#include <string>
#include <vector>
#include "Utils/Log.h"

class xml_node;
class ui_node;
/*
һЩ���õ�ȫ�ֺ����������ַ����Ĳ�������Դ�Ķ�ȡת����
*/

/////////�ַ���ת��

//���ַ���ת��ΪBOOL��
//������
//	str:�����ַ�
//����ֵ��true����false
bool atob(const char* str);

std::pair<int, int> atoip(const char* str);

//���ַ�����";;"������ַ�����
//������
//	str:�����ַ�
//����ֵ���ַ�����
QStringList atosv(const char* str);

//����ַ���Դ
//������
//	str:�����ַ�
//����ֵ���ַ���Դ
const char* getResText(const char* str);

//�����ʽ��Դ
//������
//	str:�����ַ�
//����ֵ����ʽ��Դ
const char* getResStyle(const char* str);

//���resĿ¼��imageĿ¼�µ�ͼƬ·��
//������
//	url:resĿ¼��imageĿ¼�µ�ͼƬ·��
//	istr: �����ַ�
//����ֵ����
void getResImageUrl(std::string& url,const char* istr);

//���resĿ¼��qmlĿ¼�µ�ͼƬ·��
//������
//	url:resĿ¼��imageĿ¼�µ�qml·��
//	istr: �����ַ�
//����ֵ����
void getResQmlUrl(std::string& url,const char* istr);


//���resĿ¼��iconĿ¼�µ�ͼƬ·��
//������
//	url:resĿ¼��iconĿ¼�µ�ͼƬ·��
//	istr: �����ַ�
//����ֵ����
void getResIconUrl(std::string& url,const char* istr);

//���resĿ¼��imagesĿ¼����iconsĿ¼�µ�ͼƬ·��
//������
//	url:resĿ¼��imagesĿ¼����iconsĿ¼�µ�ͼƬ·��
//	istr: �����ַ�
//����ֵ����
void getResImageOrIconUrl(std::string& url,const std::string& istr);

/******************** �ַ���ת�� **************************/
#define STR_TO_INT(str) atoi(str)  //�ַ���������
#define STR_TO_DOUBLE(str) atof(str)  //�ַ�����double
#define STR_TO_BOOL(str)  atob(str)  //�ַ�����bool
#define STR_TO_ALIGN(str)  atoalign(str)  //�ַ�����Qt::Aligment
#define STR_TO_STR_VECTOR(str) atosv(str)  //�ַ�����QStringList
#define STR_TO_RES_TEXT(str) getResText(str)  //�ַ�������Դ�ַ���
#define STR_TO_RES_STYLE(str) getResStyle(str)  //�ַ�������Դ��Style
#define STR_TO_INT_PAIR(str) atoip(str)

/*********************** ui_node�ڵ���� *********************/
//��Object�л��ui_node�ڵ�
//������
//	object:Object����
//����ֵ��ui_nodeָ��
void* getUINodeFromObject(void* object);

//���QVariant�е�ui_nodeָ��
//������
//	variant:Variant����
//����ֵ��ui_nodeָ��
void* getUINodeFromVariant(void* variant);

//���xml�ļ����ڵ�
//������
//	filename:xml�ļ�·��
//	root:xml���ڵ�
//����ֵ����óɹ�����true,���򷵻�false
bool getXMLFileRoot(const char* filename,xml_node* root);


/****************** �ַ������� ********************/
//�ָ�,C++ʵ��
//���ַ���ͨ���ض��ַ��ָ�
//������
//	inStr:�����ַ���
//	outStrVec:����ַ�����
//	sep:�ָ���
//����ֵ����
void splitString(std::string& inStr,std::vector<std::string>& outStrVec,std::string sep);

//���ַ�����ĳ���ַ�ȫ���滻
//������
//	str:�����ַ���
//	old_value:���ַ���
//	new_value:���ַ���
//����ֵ����
std::string&  str_replace_all(std::string&  str,const std::string&  old_value,const std::string&  new_value);


/******************* Ŀ¼���� *********************/
//ȥ���ļ�����չ����
//������
//	filename:�ļ���
//����ֵ����
void removeExtension(std::string& filename);

//�Ƿ�����ļ������ļ���·��
//������
//	path:·��
//����ֵ�����ڷ���true,���򷵻�false
bool fileOrPahtExist(const char* path);

//����Ŀ¼�������ݹ鴴��
//������
//	path:Ŀ¼·��
//	recurseFlag:�Ƿ�ع񴴽�
//	perm:Ŀ¼����Ȩ��
//����ֵ���ɹ�����true,���򷵻�false
bool createDirectory(const char* path, bool recurseFlag = true, int perm = 0775);

//��·���ַ�������ȡ������(eg:"D:")��·��(eg:"D:/a/b/c/"),�ļ���(eg:"exename"),��׺(eg:"exe")
//������
//	path:·���ַ���
//	drive:�̷�
//	dir:Ŀ¼·��
//	fname:�ļ���
//	ext:�ļ���׺
//����ֵ����
void splitpath(const char*path,  std::string& drive, std::string& dir, std::string& fname, std::string& ext);

//��ȡ�ļ����������ļ����ļ���
//������
//	path:Ŀ¼·��
//	files:�ļ�������
//	filter:���������ļ���׺
//����ֵ����
void getAllFilesInCurrentDir(std::string path,std::vector<std::string>& files,std::string filter="");

/******************* ����任 *********************/
//Gb2312�����ַ�ת��ΪUTF8 �ַ�
//������
//	szOut:����ַ���
//	szIn:�����ַ���
//����ֵ����
void Gb2312ToUTF8(char *szOut, const char *szIn);



//һЩר����־���
//�ж��ļ�����·���Ƿ����
//������
//	path:·��
//	type:�����־����
//����ֵ����
void logFileOrPathExist(const char* path,Log::LOG_TYPE type=Log::LOG_WARN,bool autoCreate = false);



bool bindQObjectAndNode(QObject* object,ui_node* node);
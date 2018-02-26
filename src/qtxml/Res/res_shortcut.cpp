#include "res_shortcut.h"
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "Uicreator/xml_node.h"
#include "Common/app_env.h"
#include "Utils/util.h"

//���캯��
//��������
//����ֵ����
res_shortcut::res_shortcut(void)
{
    _res_map.clear();
    _found_shortcut = NULL;
    parseResourceXML(app_env::getDir(app_env::SHORTCUT_RESOURCE));
}
//��������
//��������
//����ֵ����
res_shortcut::~res_shortcut(void)
{
}

void res_shortcut::releaseResource()
{
    xml_res_base::releaseResource();
    _res_map.clear();
}
//ȫ��������
//������inVec ��������, outVec �������, s ��ʼλ��, e��С
//����ֵ����
void res_shortcut::perm(vector<string>& inVec,vector<string>& outVec,int s,int e)
{
	int i;
	if (s>=e)
	{
		std::string combinedKeyString;
		for (i=0;i<=e;i++)
		{
			combinedKeyString.append(inVec[i]+"+");
		}
		combinedKeyString.append(inVec[e+1]);
		outVec.push_back(combinedKeyString);
	}
	else
	{
		for (i=s;i<=e;i++)
		{
			if (i!=s)
				swap(inVec[s],inVec[i]);
			perm(inVec,outVec,s+1,e);
			if (i!=s)
				swap(inVec[s],inVec[i]);
		}
	}
}
//�����ַ���
//������s1 ����1, s2 ����2
//����ֵ����
void res_shortcut::swap(string& s1,string& s2)
{
	string temp = s1;
	s1 = s2;
	s2 = temp;
}
//��ÿ�ݼ���Դ
//������name ID
//����ֵ����Դ
xml_node* res_shortcut::findRes(const char* name)
{
	ShortcutMapType::iterator it = _res_map.find(name);
	if (it != _res_map.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}
//��ÿ�ݼ���Դ
//������name ID
//����ֵ����Դ
xml_node* res_shortcut::getShortcutRes(const char* name)
{
    CHECK_FILES_CHANGED(SHORTCUT_RESOURCE)
	_found_shortcut = findRes(name);
	if (_found_shortcut)
	{
		return _found_shortcut;
	}
	std::string keyString = name;
	if (keyString.find("+")!=std::string::npos) //�������ϼ������ȫ���У�����xml�в����Ƿ���ڣ������򷵻ض�Ӧ�Ľڵ�
	{
		std::vector<std::string> keys;
		std::vector<string> outv;  //���ȫ�������
		splitString(keyString,keys,"+");
		int modifierNum = keys.size()-2; //�������һ��ǰ���ȫ����
		perm(keys,outv,0,modifierNum);
		for (int i=0;i<outv.size();i++)
		{
			_found_shortcut = findRes(outv[i].c_str());
			if (_found_shortcut)
			{
				return _found_shortcut;
			}
		}
	}
	return NULL;
}
//���������ļ�xml
//������filename �ļ�·��
//����ֵ����
void res_shortcut::parseXML(const char* filename)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename);
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s failed! Error code: %s \n", filename, doc.ErrorStr());
        return;
    }
    tinyxml2::XMLElement* curXMLNode = doc.RootElement();
	if (strcmp(curXMLNode->Name(),"Shortcuts")==0)
	{
        tinyxml2::XMLElement* str = curXMLNode->FirstChildElement();
		while(str!=NULL)
		{
			if (strcmp(str->Name(),"Shortcut")==0)
			{
				xml_node strNode;
				strNode.relateXMLNode(str);
				if (strNode.hasAttribute("name"))
				{
					_res_map[strNode.getAttribute("name")] = strNode;
				}
			}
			str = str->NextSiblingElement();
		}
	}
	else
	{
		return;
	}
}
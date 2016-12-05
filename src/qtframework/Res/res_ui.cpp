#include "res_ui.h"
#include "Uicreator/xml_ui_paser.h"
#include "Utils/util.h"
#include "Common/app_env.h"
#include "Uicreator/ui_node.h"
//���캯��
//��������
//����ֵ����
res_ui::res_ui()
{
	string uiResDir = app_env::getDir(app_env::UI_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(uiResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = uiResDir;
		filepath.append(*it);
		xml_ui_paser* parser = new xml_ui_paser(filepath.c_str());
		if (parser->parserXML())
		{
			if (parser->getRoot()->hasAttribute("id"))
			{
				string id = parser->getRoot()->getAttribute("id");
				if (!_res_map.count(id.c_str()))
				{
					_res_map[id] = parser->getRoot();
				}
			}	
		}
	}
}

//��������
//��������
//����ֵ����
res_ui::~res_ui()
{
}
//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
//������id ID
//����ֵ���ڵ�ָ��
ui_node* res_ui::getUIRes(const char* id)
{
	ResMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
	
}

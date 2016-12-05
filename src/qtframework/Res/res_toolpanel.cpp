#include "res_toolpanel.h"
#include "Uicreator/xml_ui_paser.h"
#include "Utils/util.h"
#include "Common/app_env.h"
#include "Uicreator/ui_node.h"
res_toolpanel::res_toolpanel(void)
{
	string panelResDir = app_env::getDir(app_env::TOOLPANEL_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(panelResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = panelResDir;
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


res_toolpanel::~res_toolpanel(void)
{
}

//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
//������id ID
//����ֵ���ڵ�ָ��
ui_node* res_toolpanel::getToolpanelRes(const char* id)
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
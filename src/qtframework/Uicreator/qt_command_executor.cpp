#include "qt_command_executor.h"
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
#include "Common/app_env.h"
//#include "gise_config.h"
//#include "main/igis_main.h"


#include <string.h>

#include <QMessageBox>
#include <QtCore/QVariant>

//using namespace gise;
//���캯��
//��������
//����ֵ����
qt_command_executor::qt_command_executor(void):QObject()
{
}

//��������
//��������
//����ֵ����
qt_command_executor::~qt_command_executor(void)
{
}
//ִ��ui_node��������
//������node ui_node����ָ��
//����ֵ���Ƿ�ִ�гɹ�
bool qt_command_executor::executeCommand(ui_node* node)
{
	xml_node* xmlNode = static_cast<xml_node*>(node);
	return executeCommand(xmlNode);
	
}
//ִ��xml_node��������
//������node xml_node����ָ��
//����ֵ���Ƿ�ִ�гɹ�
bool qt_command_executor::executeCommand(xml_node* node)
{
	//gise::IGIS_Main* pMain = (gise::IGIS_Main*)app_env::getMainPtr();
	//if (!pMain)
	//{
	//	char szMsg[1024];
	//	if (node->hasAttribute("command")||node->hasAttribute("msgcommand")||node->hasAttribute("toolcommand"))
	//	{
	//		sprintf(szMsg, "QtFrameWork ERROR: Execute command of node \"%s\" %s failed! Because IGIS_Main is not initialized!\n",node->getName(),node->hasAttribute("id")?node->getAttribute("id"):"");
	//		printf(szMsg);
	//	}
	//	return false;
	//}
	//if (node->hasAttribute("command"))
	//{
	//	string command = node->getAttribute("command");
	//	int icommand = STR_TO_INT(command.c_str());
	//	if (pMain->ExecuteCommand(icommand, 0, 0))
	//	{
	//		return true;
	//	}else
	//		return false;
	//}
	////ssx
	//if (node->hasAttribute("msgcommand"))
	//{
	//	string command = node->getAttribute("msgcommand");
	//	int icommand = STR_TO_INT(command.c_str());
	//	pMain->SendMessage(icommand, 0, (void*)node->getAttribute("id"));		
	//}
	//if (node->hasAttribute("toolcommand"))
	//{
	//	string sToolID = node->getAttribute("toolcommand");
	//	int iToolID = STR_TO_INT(sToolID.c_str());
	//	if (pMain->SelectTool(iToolID))
	//	{
	//		return true;
	//	}else
	//		return false;
	//}
	return false;
}
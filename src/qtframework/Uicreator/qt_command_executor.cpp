#include "qt_command_executor.h"
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
#include "Common/app_env.h"
#include "Res/R.h"
#include "Utils/variant.h"
#include "Utils/qt_standard.h"
#include "qfmain/iqf_main.h"

#include <string.h>
#include <iostream>
#include <QtCore/QVariant>
#include <QObject>

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
    QF::IQF_Main* pMain = (QF::IQF_Main*)app_env::getMainPtr();
    if (node->hasAttribute("msgcommand"))
    {
        string command = node->getAttribute("msgcommand");

        VarientMap vm = node->getParameters();
        if (node->hasAttribute("property")||node->hasAttribute("itemProperty"))
        {
            if (node->hasAttribute("property"))
            {
                QObject* obj = (QObject*)node->getObject();
                std::string propertyStr = node->getAttribute("property");
                QVariant qProperty = obj->property(propertyStr.c_str());
                if (qProperty.isValid())
                {
                    variant v;
                    if (qt_standard::exchangProperty(qProperty, v))
                    {
                        vm[propertyStr] = v;                        
                    }
                }
            }
            if (node->hasAttribute("itemProperty"))
            {
                std::string propertyStr = node->getAttribute("itemProperty");
                int i = propertyStr.find(":");
                if (i != std::string::npos)
                {
                    std::string id = propertyStr.substr(0, i);
                    std::string propertyName = propertyStr.substr(i + 1, propertyStr.length() - 1 - i);
                    QObject* obj = (QObject*)R::Instance()->getObjectFromGlobalMap(id.c_str());
                    QVariant qProperty = obj->property(propertyName.c_str());
                    if (qProperty.isValid())
                    {
                        variant v;
                        if (qt_standard::exchangProperty(qProperty, v))
                        {
                            vm[propertyName] = v;
                        }
                    }
                }
            }     
        }
        if (vm.size()>0)
        {
            pMain->SendMessage(command.c_str(), 0, (void*)&vm);
        }
        else
        {
            pMain->SendMessage(command.c_str(), 0, (void*)node->getAttribute("id"));
        }
        std::cout << "Execute Command " << command << std::endl;
        return true;
    }
    return true;

    //xml_node* xmlNode = static_cast<xml_node*>(node);
	//return executeCommand(xmlNode);
	
}
//ִ��xml_node��������
//������node xml_node����ָ��
//����ֵ���Ƿ�ִ�гɹ�
bool qt_command_executor::executeCommand(xml_node* node)
{
	QF::IQF_Main* pMain = (QF::IQF_Main*)app_env::getMainPtr();
    /*if (!pMain)
    {
        char szMsg[1024];
        if (node->hasAttribute("command")||node->hasAttribute("msgcommand")||node->hasAttribute("toolcommand"))
        {
            sprintf(szMsg, "QtFrameWork ERROR: Execute command of node \"%s\" %s failed! Because IGIS_Main is not initialized!\n",node->getName(),node->hasAttribute("id")?node->getAttribute("id"):"");
            printf(szMsg);
        }
        return false;
    }
    if (node->hasAttribute("command"))
    {
        string command = node->getAttribute("command");
        int icommand = STR_TO_INT(command.c_str());
        if (pMain->ExecuteCommand(icommand, 0, 0))
        {
            return true;
        }else
            return false;
    }*/
	if (node->hasAttribute("msgcommand"))
	{
		string command = node->getAttribute("msgcommand");
        pMain->SendMessage(command.c_str(), 0, (void*)node->getAttribute("id"));
	}
    /*if (node->hasAttribute("toolcommand"))
    {
        string sToolID = node->getAttribute("toolcommand");
        int iToolID = STR_TO_INT(sToolID.c_str());
        if (pMain->SelectTool(iToolID))
        {
            return true;
        }else
            return false;
    }*/
	return false;
}
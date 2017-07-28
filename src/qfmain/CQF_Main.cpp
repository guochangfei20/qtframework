#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
#include <windows.h>
#include <winnt.h>
#else
line.append(".so");
#endif  


#include "CQF_Main.h"

#include "IQF_Component.h"
#include "IQF_Activator.h"
#include "IQF_Command.h"
#include "IQF_Message.h"
#include <direct.h>
#include "qf_eventdef.h"

#include "internal/qf_interfacedef.h"

//std
#include "QF_String.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::string&  str_replace_all(std::string& str, const std::string&  old_value, const std::string&  new_value)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
    {
        if ((pos = str.find(old_value, pos)) != std::string::npos)
            str.replace(pos, old_value.length(), new_value);
        else   break;
    }
    return   str;
}

void splitString(std::string& inStr, std::vector<std::string>& outStrVec, std::string sep)
{
    std::string temp = inStr.c_str();
    char* result = NULL;
    result = strtok((char*)temp.data(), (char*)sep.data());
    while (result != NULL)
    {
        outStrVec.push_back(result);
        result = strtok(NULL, (char*)sep.data());
    }
}

void splitpath(const char*path, std::string& drive, std::string& dir, std::string& fname, std::string& ext)
{
    std::string temp = path;
    str_replace_all(temp, "\\", "/");
    std::vector<std::string> v;
    splitString(temp, v, "/");
    int size = v.size();
    if (size <= 1)
    {
        dir = temp;
        fname = "";
        ext = "";
    }
    else
    {
        fname = v.at(size - 1);
        if (fname.find(".") != std::string::npos)
        {
            int index = fname.find_first_of(".");
            ext = fname.substr(index + 1, fname.size() - 1);
            fname = fname.substr(0, index);
        }
        if (temp.find(":") != std::string::npos)
        {
            int i = temp.find_first_of(":");
            drive = temp.substr(0, i + 1);
        }
        else
        {
            drive = "";
        }
        dir = temp;
        if (temp.find("/") != std::string::npos)
        {
            int j = dir.find_last_of("/");
            dir = dir.substr(0, j + 1);
        }
    }
}

QF_BEGIN_NAMESPACE(QF)

typedef IQF_Component* (*componentFunc)(IQF_Main*);
typedef IQF_Activator* (*activatorFunc)(IQF_Main*);


bool CheckValid(std::string& line)
{
    if (line.compare(0, 2, "//") == 0||
        line.compare(0, 1, "#") == 0||
        line.empty())
    {
        return false;
    }
    return true;
}

CQF_Main::CQF_Main(const char* szEnterName)
{
    m_pSubject = QF_CreateSubjectObject();
    {
        if (strcmp(szEnterName,"")==0)
        {
            char buffer[MAX_PATH];
            getcwd(buffer, MAX_PATH);
            m_configPath = buffer;
        }
        else
        {
            std::string drive;
            std::string dir;
            std::string fname;
            std::string ext;
            splitpath(szEnterName, drive, dir, fname, ext);
            m_configPath = dir.substr(0, dir.find_last_of("/") - 1);
            m_configPath = m_configPath.substr(0, m_configPath.find_last_of("/") + 1);
            m_configPath.append("qfconfig/"+fname);
            std::ifstream test(m_configPath +"/components.cfg", std::ios::in);
            if (!test)
            {
                m_configPath = dir + "qfconfig/" + fname;
            }
            test.close();
        }     
        
        std::string componentsFile = m_configPath + "/components.cfg";
        std::ifstream finComponents(componentsFile, std::ios::in);
        if (!finComponents)
        {
            std::cerr << "The components file can not be opened! Please check if it exists!" << std::endl;
            return;
        }
        std::string line;
        while (!finComponents.eof()) {
            std::getline(finComponents, line);
            if (CheckValid(line))
            {
                RegisterLibrary(line.c_str());
            }
        }
        finComponents.close();
    }

    {
        std::string pluginsFile = m_configPath + "/plugins.cfg";
        std::ifstream finPlugins(pluginsFile, std::ios::in);
        if (!finPlugins)
        {
            std::cerr << "The plugins file can not be opened! Please check if it exists!" << std::endl;
            return;
        }
        std::string line;
        while (!finPlugins.eof()) {
            std::getline(finPlugins, line);
            if (CheckValid(line))
            {
                RegisterLibrary(line.c_str());
            }
        }
        finPlugins.close();
    }

}


CQF_Main::~CQF_Main()
{
#ifndef _DEBUG
    try
    {
#endif

        this->SendMessage(QF_MESSAGE_MAIN_DELETE, 0, this);

        //delete message order
        for (TQF_CharToIntMap::iterator it_mainmessage_order = m_messageOrder.begin(); it_mainmessage_order != m_messageOrder.end(); it_mainmessage_order++)
        {
            char * p_str = (char *)it_mainmessage_order->first;
            delete[]p_str;
        }

        //delete message list
        for (QF_MainMessageListMap::iterator it_message = m_messagelists.begin(); it_message != m_messagelists.end(); it_message++)
        {
            QF_MessageComponentList * p_list = it_message->second;
            if (p_list)
                delete p_list;
        }

        // delete components
        for (QF_MainComponentMap::iterator it_component = m_components.begin(); it_component != m_components.end(); it_component++)
        {
            std::string str = it_component->first;
#ifndef _DEBUG
            try
            {
#endif
                it_component->second->Release();

#ifndef _DEBUG
            }
            catch (...)
            {
                char msg[2000];
                sprintf(msg, "Exception Occurs When Delete Component [%s] !", str.c_str());
            }
#endif
        }

        QF_ReleaseSubjectObject(m_pSubject);

#ifndef _DEBUG
    }
    catch (...)
    {
        
    }

#endif
}

const char* CQF_Main::GetConfigPath()
{
    return m_configPath.c_str();
}

void CQF_Main::RegisterLibrary(const char* szDllName)
{
    std::string line = szDllName;
    int foundExt = line.find_first_of(".");
    if (foundExt != std::string::npos)
    {
        line = line.substr(0, foundExt);
    }
#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
    line.append(".dll");
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    std::string dllPath = buffer;
    dllPath.append("\\");
    dllPath.append(line);
    
    HINSTANCE hdll = LoadLibrary((wchar_t*)s2ws(dllPath).c_str());
    
    if (hdll != NULL)
    {
        componentFunc pf = (componentFunc)GetProcAddress(hdll, "QF_CreateComponentObject");
        if (pf)
        {
            RegisterComponent(pf(this));
            std::cout << "Load component " << dllPath << std::endl;
        }
        activatorFunc af = (activatorFunc)GetProcAddress(hdll, "QF_CreatePluginActivator");
        if (af)
        {
            RegisterActivator(af(this));
            std::cout << "Load component " << dllPath << std::endl;
        }

    }
    else
    {
        std::cout << "Load component failed: " << dllPath <<" . ";
        TCHAR szBuf[80];
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        std::cout << "Error Code:" << dw<<std::endl;

    }
#else
    line.append(".so");
#endif  
}

bool CQF_Main::RegisterComponent(IQF_Component* pComponent)
{
#ifndef _DEBUG
    try
    {
#endif
        if (!pComponent)
        {
            char sz_msg[1024];
            sprintf(sz_msg, "pComponent == NULL");
            assert(false && "Illegal Component ! ");
            return false;
        }
        const char* component_id = pComponent->GetComponentID();
        if (!component_id)
        {
            char sz_msg[1024];
            sprintf(sz_msg, "component_id == NULL");
            assert(false && "Illegal Component ID !");
            return false;
        }

        if (!pComponent->Init())
        {
            assert(false && "Component Init Failed!");
            std::cout << "Component " << pComponent->GetComponentID() << " Init Failed!" << std::endl;
            return false;
        }

        char* p_str = new char[strlen(component_id) + 1];
        strcpy(p_str, component_id);
        m_components[p_str] = pComponent;

        //register interfaces
        for (int i = 0; i < pComponent->GetInterfaceCount(); i++)
        {
            std::string interface_id = pComponent->GetInterfaceID(i);

            if (interface_id.empty())
            {
                assert(false && "Illegal Interface ID!");
                continue;
            }
            if (m_interfaces.find(interface_id) != m_interfaces.end())
            {
                assert(false && "Interface Name has already exist! Please Rename!");
                std::cout << "Interface Name " << interface_id << " has already exist! Please Rename!" << std::endl;
            }
            m_interfaces[interface_id] = pComponent->GetInterfacePtr(interface_id.c_str());
        }

        // Register Commands
        IQF_Command * p_interface_command = (IQF_Command *)pComponent->GetInterfacePtr(QF_INTERFACE_MAIN_COMMAND);
        if (p_interface_command != NULL)
        {
            for (int i = 0; i < p_interface_command->GetCommandCount(); i++)
            {
                std::string command_id = p_interface_command->GetCommandID(i);

                if (command_id.empty())
                {
                    assert(false && "Illegal Command ID");
                    continue;
                }

                if (m_commands.find(command_id) != m_commands.end())
                {
                    assert(false && "Command ID Repeat");
                    printf("Command ID[%s] Repeat，Please Choose Another ID.\n", command_id);
                }
                m_commands[command_id] = p_interface_command;
            }
        }

        // Register message component
        IQF_Message * p_interface_message = (IQF_Message*)pComponent->GetInterfacePtr(QF_INTERFACE_MAIN_MESSAGE);
        if (p_interface_message != NULL)
        {
            QF_MainMessageListMap::iterator it;
            int i_count = p_interface_message->GetMessageCount();
            for (int i = 0; i < i_count; i++)
            {
                // record id
                const std::string sz_message_id = p_interface_message->GetMessageID(i);
                if (sz_message_id.empty())
                {
                    assert(false && "Illegal Message ID");
                    continue;
                }

                // scan if already has the message
                it = m_messagelists.find(sz_message_id);

                QF_MessageComponentList * p_list = NULL;
                // if message exist
                if (it != m_messagelists.end())
                {
                    p_list = it->second;
                }
                // if not, new one
                else
                {
                    p_list = new QF_MessageComponentList;
                    m_messagelists[sz_message_id] = p_list;
                }

                TQF_CharToIntMap::iterator it_order = m_messageOrder.find(component_id);

                // 找到
                if (it_order != m_messageOrder.end())
                {
                    int i_index = it_order->second;

                    int i_order;
                    for (i_order = 0; i_order < p_list->size(); i_order++)
                    {
                        IQF_Message * p_message = (*p_list)[i_order];
                        TQF_IntToIntMap::iterator it_message_order = m_messageInterfaceOrder.find((int)p_message);
                        if (it_message_order == m_messageInterfaceOrder.end())
                        {
                            char sz_msg[1024];
                            sprintf(sz_msg, "Message send order error !");
                            std::cout << "CGIS_Main::RegisterComponent "<<sz_msg << std::endl;
                            assert(false);
                            m_messageInterfaceOrder[(int)p_interface_message] = -1;
                            p_list->push_back(p_interface_message);
                            break;
                        }
                        else
                        {
                            int i_message_order = it_message_order->second;
                            if ((i_message_order == -1) || (i_message_order > i_index))
                            {
                                p_list->insert(p_list->begin() + i_order, p_interface_message);
                                break;
                            }
                        }
                    }
                    // 没有插入
                    if (i_order >= p_list->size())
                    {
                        p_list->push_back(p_interface_message);
                    }
                    m_messageInterfaceOrder[(int)p_interface_message] = i_index;
                }
                // 没找到
                else
                {
                    m_messageInterfaceOrder[(int)p_interface_message] = -1;
                    p_list->push_back(p_interface_message);
                }
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
        char sz_msg[1024] = "";
        sprintf(sz_msg, "Register Component %s error !", pComponent->GetComponentID());
    }
#endif
    return true;
}

void CQF_Main::RegisterActivator(IQF_Activator* pActivator)
{
    if (!pActivator->Init())
    {
        assert(false && "Component Init Failed!");
        std::cout << "Component " << pActivator->GetID() << " Init Failed!" << std::endl;
        return;
    }
    m_activators[pActivator->GetID()] = pActivator;
}

void CQF_Main::Attach(IQF_Observer* pObserver, const char* szMessage)
{
    m_pSubject->Attach(pObserver);
}

void CQF_Main::Detach(IQF_Observer* pObserver, const char* szMessage)
{
    m_pSubject->Detach(pObserver);
}

void CQF_Main::DetachAll()
{
    m_pSubject->DetachAll();
}

void CQF_Main::Notify(const char* szMessage, int iValue, void* pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

//Observer Function
void CQF_Main::Update(const char* szMessage, int iValue, void* pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

//Main Function
void CQF_Main::Release()
{
    delete this;
}

bool CQF_Main::ExecuteCommand(const char* szCommandID, IQF_PropertySet* pInParam, IQF_PropertySet* pOutParam)
{
    QF_MainCommandMap::iterator it_command;


    it_command = m_commands.find(szCommandID);
    if (it_command == m_commands.end())
    {
        assert(false && "Can not find the component for command");
        return false;
    }

    IQF_Command * p_command = it_command->second;

#ifndef _DEBUG
    try
    {
#endif
        return p_command->ExecuteCommand(szCommandID, pInParam, pOutParam);
#ifndef _DEBUG
    }
    catch (...)
    {
        char msg[2000];
        sprintf(msg, "An Exception Occurs  When Execute Command [%d] .", szCommandID);
        return false;
    }
#endif
}

void CQF_Main::SendMessage(const char* szMessage, int iValue, void *pValue)
{
#ifndef _DEBUG
    try
    {
#endif
        m_pSubject->Notify(szMessage, iValue, pValue);

        QF_MainMessageListMap::iterator it = m_messagelists.find(szMessage);
        // message does not exist
        if (it == m_messagelists.end())
            return;

        // scan message list
        QF_MessageComponentList * p_list = it->second;
        int i;
        for (i = 0; i < p_list->size(); i++)
        {
            IQF_Message * p_message = (*p_list)[i];
            if (p_message)
            {
                p_message->OnMessage(szMessage, iValue, pValue);
            }
            else
            {
                assert(false && "Illegal message interface! ");
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
        assert(false && "Exception" && "Illegal message interface! ");
    }
#endif
}

void CQF_Main::SendMessageQf(const char* szMessage, int iValue, void *pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

void* CQF_Main::GetInterfacePtr(const char* szInterfaceID)
{
    QF_MainInterfaceMap::iterator it_interface = m_interfaces.find(szInterfaceID);
    if (it_interface == m_interfaces.end())
    {
#ifndef _DEBUG
        std::cout << "Get interface "<< szInterfaceID <<" failed ! Please check if the interface exists or the related component is registered ! "<< std::endl;
#endif
        return NULL;
    }
    return it_interface->second;
}

void CQF_Main::RegisterResource(R* pR)
{
    for (QF_MainActivatorMap::iterator it = m_activators.begin();it != m_activators.end();it++)
    {
        it->second->Register(pR);
    }
}

void CQF_Main::ResourceConstructed(R* pR)
{
    for (QF_MainActivatorMap::iterator it = m_activators.begin();it != m_activators.end();it++)
    {
        it->second->Constructed(pR);
    }
}

QF_END_NAMESPACE
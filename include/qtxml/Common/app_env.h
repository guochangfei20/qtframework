/*!
 * \file app_env.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef APP_ENV_H
#define APP_ENV_H

#pragma once
#include <string>
#include "Common/qtxml_com.h"
using namespace std;
//����ָ������
typedef void IQF_Main_Ext;

/*!
 * \class app_env
 *
 * \brief app_env��
 *
 * \author ����
 * \date ���� 2016
 */
class QTXML_EXPORT app_env
{
public:
	//Ŀ¼����
	enum DirType
	{
		WORKSPACE,			//qtframework����Ŀ¼
		RESOURCE,			//��ԴĿ¼
		LAYOUT,				//������ԴĿ¼
		LOG,				//��־Ŀ¼
		STRING_RESOURCE,	//�ַ���ԴĿ¼
		STYLE_RESOURCE,		//��ʽ��ԴĿ¼
		UI_RESOURCE,		//ui��ԴĿ¼
		COMMAND_RESOURCE,	//uicommand��ԴĿ¼
		MENU_RESOURCE,		//�˵���ԴĿ¼
		CONFIG_RESOURCE,	//������ԴĿ¼
		IMAGE_RESOURCE,		//ͼƬ��ԴĿ¼
		ICON_RESOURCE,		//icon��ԴĿ¼
		SHORTCUT_RESOURCE,	//��ݼ���ԴĿ¼
		LANGUAGE_RESOURCE,	//������ԴĿ¼
		TOOLPANEL_RESOURCE
	};
	//��������
	enum Language
	{
		CHINESE,		//��������
		CHINESE_TW,		//��������
		ENGLISH			//Ӣ��
	};
	//���캯��
	//������
	//		wDir:qtframework����·��
	//����ֵ����
	app_env(const char *wkDir);
	//��������
	~app_env(void);
	//setter
	//ָ��qtframework����·������res,log,plugins����ԴĿ¼���ڵ�Ŀ¼����C:/qtframe_ui/app_name/
	//������
	//		wDir: ·��
	//����ֵ����
	static void setWorkDir(const char* wDir);
	//getter
	//���г������ڹ���Ŀ¼
	//��������
	//����ֵ��·��
	static const char* getAppDir(){return _appDir.c_str();}
	//qtframework�Ĺ���Ŀ¼
	//��������
	//����ֵ��·��
	static const char* getWorkDir(){return _workDir.c_str();}
	//���г��������
	//��������
	//����ֵ��·��
	static const char* getExeName(){return _exeName.c_str();}
	//��ԴĿ¼ "res/"
	//��������
	//����ֵ��·��
	static const char* getResDir(){return _resDir.c_str();}
	//layoutĿ¼ "res/layout"
	//��������
	//����ֵ��·��
	static const char* getLayoutDir(){return _layoutDir.c_str();}
	//�⻯�ַ���Ŀ¼ "res/strings"
	//��������
	//����ֵ��·��
	static const char* getStringResDir(){return _stringResDir.c_str();}
	//��ʽĿ¼ "res/styles"
	//��������
	//����ֵ��·��
	static const char* getStyleResDir(){return _styleResDir.c_str();}
	//Ƕ��ʽUI��Դ����Ŀ¼ "res/ui"
	//��������
	//����ֵ��·��
	static const char* getUIResDir(){return _uiResDir.c_str();}
    //Ƕ��ʽUI��Դ����Ŀ¼ "res/ui"
    //��������
    //����ֵ��·��
    static const char* getToolpanelResDir() { return _toolpanelDir.c_str(); }
	//uicommand����Ŀ¼ "res/uicommands"
	//��������
	//����ֵ��·��
	static const char* getCommandResDir(){return _commandResDir.c_str();}
	//Menu��Դ����Ŀ¼ "res/menu"
	//��������
	//����ֵ��·��
	static const char* getMenuResDir(){return _menuResDir.c_str();}
	//�����ļ�����Ŀ¼ "res/config"
	//��������
	//����ֵ��·��
	static const char* getConfigResDir(){return _configResDir.c_str();}
	//ͼƬ�ļ�����Ŀ¼ "res/images"
	//��������
	//����ֵ��·��
	static const char* getImageResDir(){return _imageResDir.c_str();}
	//icon�ļ�����Ŀ¼ "res/icons"
	//��������
	//����ֵ��·��
	static const char* getIconResDir(){return _iconResDir.c_str();}
	//�����ļ�����Ŀ¼ "res/language"
	//��������
	//����ֵ��·��
	static const char* getLanguageDir(){return _languageDir.c_str();}
	//��ݼ��ļ�����Ŀ¼ "res/shortcut"
	//��������
	//����ֵ��·��
	static const char* getShortcutDir(){return _shortcutDir.c_str();}
	//log�ļ�����Ŀ¼ "log/"
	//��������
	//����ֵ��·��
	static const char* getLogDir(){return _logDir.c_str();}
	//qml�ļ�����Ŀ¼ "qml/"
	//��������
	//����ֵ��·��
	static const char* getQmlResDir(){return _qmlResDir.c_str();}

	//���·��
	//������
	//		type:·������
	//����ֵ��·��
	static const char* getDir(DirType type);
	//��������ļ�
	//������
	//		language:��������
	//����ֵ���ļ�
	static const char* getLanguageFile(Language language);
	//��������ļ�
	//������
	//	languageStr:��������
	//����ֵ���ļ�
	static const char* getLanguageFile(const char* languageStr);
	//��ȡ����ָ��
	//��������
	//����ֵ������ָ��
	static IQF_Main_Ext* getMainPtr(){return _pMain;}
	//��������ָ��
	//������
	//      pMain:����ָ��
	//����ֵ����
	static void setMainPtr(IQF_Main_Ext* pMain){_pMain = pMain;}

	//�����Ƿ���ʾtoolTip
	//������
	//		b:�Ƿ���ʾtoolTip
	//����ֵ����
	static void setShowTooltipOn(bool b){_bShowTooltip = b;}
	//�����Ƿ���ʾtoolTip
	//��������
	//����ֵ����ʾ����true������ʾ����false
	static bool showTooltipOn(){return _bShowTooltip;}

protected:
	//��ʼ��
	//��������
	//����ֵ����
	static void setup();
private:
	static std::string _appDir;
	static std::string _workDir;
	static std::string _exeName;

	static std::string _layoutDir;
	static std::string _resDir;
	static std::string _stringResDir;
	static std::string _styleResDir;
	static std::string _uiResDir;
	static std::string _commandResDir;
	static std::string _menuResDir;
	static std::string _configResDir;
	static std::string _imageResDir;
	static std::string _iconResDir;
	static std::string _shortcutDir;
	static std::string _languageDir;
	static std::string _logDir;
	static std::string _toolpanelDir;
	static std::string _qmlResDir;

	static bool _bShowTooltip;
	static IQF_Main_Ext* _pMain;
};

#endif


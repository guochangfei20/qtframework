#include <Common/app_env.h>
#include "Utils/util.h"
#include "Utils/Log.h"

string app_env::_workDir="";
string app_env::_appDir="";
string app_env::_exeName="";
string app_env::_resDir="";
string app_env::_layoutDir="";
string app_env::_stringResDir="";
string app_env::_styleResDir="";
string app_env::_uiResDir="";
string app_env::_uicommandResDir="";
string app_env::_menuResDir="";
string app_env::_configResDir="";
string app_env::_imageResDir="";
string app_env::_iconResDir="";
string app_env::_languageDir="";
string app_env::_shortcutDir="";
string app_env::_logDir="";
string app_env::_toolpanelDir="";
string app_env::_qmlResDir="";

bool app_env::_bShowTooltip=true;

IQF_Main* app_env::_pMain=NULL;
//���캯��
//������wDir qtframework����·��
//����ֵ����
app_env::app_env(const char *wkDir)
{
	std::string path_buffer;
	std::string drive;
	std::string dir;
	std::string fname;
	std::string ext;
	splitpath(wkDir,drive,dir,fname,ext);
	//application·��
	_appDir = dir;
	//ִ�г�������
	_exeName = fname;
	setup();
}
//��������
app_env::~app_env(void)
{
}
//ָ��qtframework����·������res,log,plugins����ԴĿ¼���ڵ�Ŀ¼����C:/qtframe_ui/app_name/
//������wDir ·��
//����ֵ����
void app_env::setWorkDir(const char* wDir)
{
	if (fileOrPahtExist(wDir))
	{
		_workDir = wDir;
		setup();
	}
	else
	{
		printf("QtFrameWork ERROR: The designated qtframework work directory does not exist! Please check! \n");
	}
	
}
//��ʼ��
//��������
//����ֵ����
void app_env::setup()
{
	if (_workDir.empty())
	{
		_workDir.append(_appDir+"ui_qtframework/"+_exeName+"/");
	}
	else
	{
		if (_workDir.compare(_workDir.length()-1,1,"/")!=0||
			_workDir.compare(_workDir.length()-2,2,"\\")!=0)
		{
			_workDir.append("/");
		}
	}
	//��ԴĿ¼
	_resDir.clear();
	_resDir.append(_workDir+"res/");
	//����Ŀ¼
	_layoutDir.clear();
	_layoutDir.append(_resDir+"layout/");
	//LogĿ¼
	_logDir.clear();
	_logDir.append(_workDir+"log/");
	//string��ԴĿ¼
	_stringResDir.clear();
	_stringResDir.append(_resDir+"strings/");
	//style��ԴĿ¼
	_styleResDir.clear();
	_styleResDir.append(_resDir+"styles/");
	//ui��ԴĿ¼
	_uiResDir.clear();
	_uiResDir.append(_resDir+"ui/");
	//uicommand��ԴĿ¼
	_uicommandResDir.clear();
	_uicommandResDir.append(_resDir+"uicommands/");
	//config��ԴĿ¼
	_configResDir.clear();
	_configResDir.append(_resDir+"config/");
	//menu��ԴĿ¼
	_menuResDir.clear();
	_menuResDir.append(_resDir+"menu/");
	//image��ԴĿ¼
	_imageResDir.clear();
	_imageResDir.append(_resDir+"images/");
	//icon��ԴĿ¼
	_iconResDir.clear();
	_iconResDir.append(_resDir+"icons/");
	//language��ԴĿ¼
	_languageDir.clear();
	_languageDir.append(_resDir+"language/");
	//��ݼ���ԴĿ¼
	_shortcutDir.clear();
	_shortcutDir.append(_resDir+"shortcut/");

	_toolpanelDir.clear();
	_toolpanelDir.append(_resDir+"panel/");
	_qmlResDir.clear();
	_qmlResDir.append(_resDir+"qml/");

	////��־���	
	logFileOrPathExist(_workDir.c_str(),Log::LOG_WARN,true);
	//logFileOrPathExist(arg,Log::LOG_ERROR);
	logFileOrPathExist(_layoutDir.c_str(),Log::LOG_WARN,true);
	logFileOrPathExist(_logDir.c_str(),Log::LOG_WARN,true);
	if (!fileOrPahtExist(_resDir.c_str()))
	{
		logFileOrPathExist(_resDir.c_str(),Log::LOG_WARN, true);
	}
	else
	{
		logFileOrPathExist(_uiResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_uicommandResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_stringResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_configResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_styleResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_imageResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_iconResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_languageDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_menuResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_shortcutDir.c_str(),Log::LOG_WARN, true);
	}
}
//���·��
//������type ·������
//����ֵ��·��
const char* app_env::getDir(DirType type)
{
	switch(type)
	{
	case WORKSPACE:
		return _workDir.c_str();
		break;
	case RESOURCE:
		return _resDir.c_str();
		break;
	case LAYOUT:
		return _layoutDir.c_str();
		break;
	case STRING_RESOURCE:
		return _stringResDir.c_str();
		break;
	case STYLE_RESOURCE:
		return _styleResDir.c_str();
		break;
	case UI_RESOURCE:
		return _uiResDir.c_str();
		break;
	case UICOMMAND_RESOURCE:
		return _uicommandResDir.c_str();
		break;
	case MENU_RESOURCE:
		return _menuResDir.c_str();
		break;
	case CONFIG_RESOURCE:
		return _configResDir.c_str();
		break;
	case IMAGE_RESOURCE:
		return _imageResDir.c_str();
		break;
	case ICON_RESOURCE:
		return _iconResDir.c_str();
		break;
	case LANGUAGE_RESOURCE:
		return _languageDir.c_str();
		break;
	case SHORTCUT_RESOURCE:
		return _shortcutDir.c_str();
		break;
	case TOOLPANEL_RESOURCE:
		return _toolpanelDir.c_str();
	default:
		break;
	}
	return "";
}
//��������ļ�
//������language ��������
//����ֵ���ļ�
const char* app_env::getLanguageFile(Language language)
{
	switch(language)
	{
	case CHINESE:
		return "qt_zh_CN.qm";
		break;
	case CHINESE_TW:
		return "qt_zh_TW.qm";
		break;
	case ENGLISH:
		return "";
		break;
	default:
		break;
	}
	return "";
}

//��������ļ�
//������languageStr ��������
//����ֵ���ļ�
const char* app_env::getLanguageFile(const char* languageStr)
{
	std::string tempStr = languageStr;
	if (tempStr.compare("Chinese")==0||tempStr.compare("chinese"))
	{
		return "qt_zh_CN.qm";
	}
	else if (tempStr.compare("Chinese_TW")==0||tempStr.compare("chinese_tw"))
	{
		return "qt_zh_TW.qm";
	}
	else if (tempStr.compare("English")==0||tempStr.compare("english"))
	{
		return "";
	}
	else
		return "";
}

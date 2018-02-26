#include <Common/qt_context.h>
#include "Utils/Log.h"
#include "Res/R.h"
#include "Common/app_env.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QTranslator>
#include <QStyleFactory>
#include "Utils/util.h"

int qt_context::_screenNum = 1;
int qt_context::_primaryScreen =0;
std::vector<sl_Rect*> qt_context::_screenRects;
QTranslator* qt_context::_translator = NULL;
//���캯��
//������app QApplicationָ��
//����ֵ����
qt_context::qt_context(QApplication* app)
{
	QDesktopWidget* desktopWidget = app->desktop();
	_screenNum = desktopWidget->screenCount();
	_primaryScreen = desktopWidget->primaryScreen();
	for (int i=0;i<_screenNum;i++)
	{
		QRect rect = desktopWidget->screenGeometry(i);
		sl_Rect* screenRect = new sl_Rect;
		screenRect->x0 = rect.x();
		screenRect->y0 = rect.y();
		screenRect->x1 = rect.x()+rect.width();
		screenRect->y1 = rect.y()+rect.height();
		screenRect->w = rect.width();
		screenRect->h = rect.height();
		_screenRects.push_back(screenRect);
	}
}
//�����Ļ���
//������i ��Ļ����
//����ֵ����Ļ���
int qt_context::getScreenWidth(int i)
{
	return getScreenRect(i)->w;
}
//�����Ļ�߶�
//������i ��Ļ����
//����ֵ����Ļ�߶�
int qt_context::getScreenHeight(int i)
{
	return getScreenRect(i)->h;
}
//����application�����ʽ
//������coding �����ʽ
//����ֵ���Ƿ����óɹ�
bool qt_context::setApplicationCoding(const char* coding)
{
	QTextCodec* codec = QTextCodec::codecForName(coding);
	if (codec)
	{
		QTextCodec::setCodecForLocale(codec);
		//QTextCodec::setCodecForTr(codec);
		//QTextCodec::setCodecForCStrings(codec);
		return true;
	}
	else
		return false;
}
//����applicationĬ������
//������languageStr ��������
//����ֵ���Ƿ����óɹ�
bool qt_context::setDefaultLanguage(const char* languageStr)
{
	_translator = new QTranslator;
	std::string languageDir = app_env::getLanguageDir();
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
    languageDir = Gb2312ToUTF8(languageDir);
#endif
	if (_translator->load(app_env::getLanguageFile(languageStr),languageDir.c_str()))
	{
		QApplication::installTranslator(_translator);		
		return true;
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Load Language File %s failed! Please check if it has existed!\n",app_env::getLanguageFile(languageStr));
		printf(szMsg);
		return false;
	}
}
//����application��ʽ
//������style ��ʽ
//����ֵ����
void qt_context::setApplicationStyle(const char* style)
{
	std::string styleRes = R::Instance()->getStyleResource(style);
	if (!styleRes.empty())
	{
        QString qss = styleRes.c_str();
         if (qss.contains("QPalette{background:"))
         {
             int index = qss.indexOf("QPalette{background:");
             QString paletteColor = qss.mid(index+20, 7);
             qApp->setPalette(QPalette(QColor(paletteColor)));
         }  
        qApp->setStyleSheet(qss);
		//qApp->setStyleSheet(styleRes.c_str());
	}
	else
	{
		QApplication::setStyle(QStyleFactory::create(style));
	}
}
//��Ӷ�̬�����Ŀ¼
//������path ·��
//����ֵ����
void qt_context::addLibraryPath(const char* path)
{
	/***********************����Qt�����*******************************/
	QApplication::addLibraryPath(path);
}
//��������
qt_context::~qt_context(void)
{
}





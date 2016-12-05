#include <UIs/SplashWindow.h>
#include <QtWidgets>
#include "UIs/Activity.h"
#include "Utils/Log.h"
#include "Utils/util.h"

class sl_Timer : public QThread
{
public:
	sl_Timer(int time):_time(time){}
	void run()
	{
		sleep(_time);
	}
private:
	int _time;
};
//���캯��
//��������
//����ֵ����
SplashWindow::SplashWindow(void):_bDelay(false),_activeSuccess(false),_relateActivity(NULL),_pMessage(NULL)
{
	//����ʼ�����ڲ��ּ��뵽SplashWindow��
	_contentActivity = new Activity;
}
//�����������ڵĲ�������
//������
//		layout_filename:�����ļ�·��
//����ֵ����
void SplashWindow::setContentView(const char* layout_filename)
{
	_contentActivity->setContentView(layout_filename);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->addWidget(_contentActivity);
	setFixedWidth(_contentActivity->getInitWidth()); //���ڴ�С�벼�ִ�Сһ��
	setFixedHeight(_contentActivity->getInitHeight()); //���ڴ�С�벼�ִ�Сһ��
	setLayout(layout);

	//���м���ʾ
	int sw = QApplication::desktop()->width();
	int sh = QApplication::desktop()->height();
	move((sw-width())/2,(sh-height())/2);

}

//��������
//��������
//����ֵ����
SplashWindow::~SplashWindow(void)
{
	//20150925
/*	if (_contentActivity!=NULL)//���ٽ�������
	{
		delete _contentActivity;
		_contentActivity = NULL;
	}
	if (_relateActivity!=NULL) //���ٹ�����Activity
	{
		delete _relateActivity;
		_relateActivity = NULL;
    }     */
	if (_delay!=NULL) //���ٹ�����Activity
	{
		delete _delay;
		_delay = NULL;
	}

	
}
//������ʱ����ʱ��
//������
//		duration:��ʱ����ʱ��
//����ֵ����
//void SplashWindow::setDelay(int duration)
//{
//	_delay = new sl_Timer(duration);
//	QObject::connect(_delay,SIGNAL(finished()),this,SLOT(activeRelatedActivity()));
//	_bDelay = true;
//}

//void SplashWindow::activeRelatedActivity()
//{
//	if (_relateActivity->active())
//	{
//		_activeSuccess = true;
//	}
//	else
//	{
//		char szMsg[1024];
//		sprintf(szMsg, "QtFrameWork ERROR: Start the activity %s failed!\n",_relateActivity->getID());
//		printf(szMsg);
//	}
//	finish(_relateActivity);
//}
//��ʼ����
//��������
//����ֵ����
//bool SplashWindow::start()
//{
//	if (_bDelay)
//	{
//		_delay->start();
//	}else
//	{
//		activeRelatedActivity();
//	}
//	return _activeSuccess;
//}

//������ʾ��Ϣ���ı��ؼ�ID
//������
//		szMessageID:�ı��ؼ�ID
//����ֵ���Ƿ����óɹ�
bool SplashWindow::setMessageLabelID(const char* szMessageID)
{
	_pMessage = (QLabel*)_contentActivity->getViewByID(szMessageID);
	if (_pMessage)
		return true;
	else
		return false;
}

//������ʾ��Ϣ
//������
//		szMessage:��ʾ��Ϣ
//����ֵ����
void SplashWindow::showMessage(const char* szMessage)
{
	if (_pMessage)
	{
		_pMessage->setText(szMessage);
		emit messageChanged(szMessage);
		repaint();

		//qApp.processEvents();
	}
	//QSplashScreen::showMessage(szMessage,Qt::AlignLeft|Qt::AlignBottom);
}

void SplashWindow::setBackground(const char* szFileName)
{
	std::string url ;
	getResImageUrl(url,szFileName);
	QPalette palette;
	_contentActivity->setAutoFillBackground(true);
	//����widget�Ĵ�С��������ͼƬ�Ĵ�С
	palette.setBrush(_contentActivity->backgroundRole(),QBrush(QPixmap(url.c_str())));
	_contentActivity->setPalette(palette);
	_contentActivity->update();
	repaint();
}
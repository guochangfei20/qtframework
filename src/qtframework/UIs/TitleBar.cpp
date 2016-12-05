#include "TitleBar.h"
#include <QtGui>
#include <QtWidgets>
#include <UIs/sl_ImageWidget.h>
#include <Utils/util.h>
#include <UIs/Activity.h>
#include "Res/R.h"
#include "Utils/Log.h"
#include "Utils/variant.h"
//���캯��
//������
//		activity������
//����ֵ����
TitleBar::TitleBar(Activity* activity):_titleNode(NULL),_parentActivity(activity),_size(25)
{
	setContentsMargins(0,0,0,0);
	//����titleĬ�ϴ�С
	const variant* v = R::Instance()->getConfigResource("WindowTitleHeight");
	if (v)
	{
		_size = v->getInt();
	}
	setFixedHeight(_size);

	QHBoxLayout* titleLayout = new QHBoxLayout;
	titleLayout->setSpacing(0);
	titleLayout->setMargin(0);
	setLayout(titleLayout);

	_iconImage = new sl_ImageWidget;  //���������Ͻ�ͼ��
	_titleText = new QLabel;  //�������м�����
	//���ñ�������
	int textSize=14;
	const variant* vSize = R::Instance()->getConfigResource("TitleTextSize");
	if (vSize)
	{
		textSize = vSize->getInt();
	}
	_titleText->setStyleSheet(QString("font-size:%1px; font-weight:bold; color:white").arg(textSize));

	_minimizeBtn = new QToolButton(this); //��������С����ť
	_maximizeBtn = new QToolButton(this); //��������󻯰�ť
	_closeBtn = new QToolButton(this); //�������˳���ť

	_maxPix = new QPixmap; 
	_restorePix = new QPixmap;
	_minPix = new QPixmap;
	_closePix = new QPixmap;

	titleLayout->addWidget(_iconImage);
	titleLayout->addWidget(_titleText);
	titleLayout->addWidget(_minimizeBtn);
	titleLayout->addWidget(_maximizeBtn);
	titleLayout->addWidget(_closeBtn);
	titleLayout->setAlignment(_titleText,Qt::AlignCenter);


	connect(_minimizeBtn,SIGNAL(clicked()),this,SLOT(minimizeParentWidget()));
	connect(_maximizeBtn,SIGNAL(clicked()),this,SLOT(maximizeParentWidget()));
	connect(_closeBtn,SIGNAL(clicked()),this,SLOT(closeParentWidget()));
}

//��������
//��������
//����ֵ����
TitleBar::~TitleBar(void)
{
}
//������С����ť�Ƿ���ʾ
//������
//		b���Ƿ���ʾ
//����ֵ����
void TitleBar::setMinimizeButtonVisible(bool b)
{
	_minimizeBtn->setVisible(b);
}
//������󻯰�ť�Ƿ���ʾ
//������
//		b���Ƿ���ʾ
//����ֵ����
void TitleBar::setMaximizeButtonVisible(bool b)
{
	_maximizeBtn->setVisible(b);
}
//���ùرհ�ť�Ƿ���ʾ
//������
//		b���Ƿ���ʾ
//����ֵ����
void TitleBar::setCloseButtonVisible(bool b)
{
	_closeBtn->setVisible(b);
}
//���ñ����������Ƿ���ʾ
//������
//		b���Ƿ���ʾ
//����ֵ����
void TitleBar::setTitleTextVisible(bool b)
{
	_titleText->setVisible(b);
}
//���ñ�����icon�Ƿ���ʾ
//������
//		b���Ƿ���ʾ
//����ֵ����
void TitleBar::setIconVisible(bool b)
{
	_iconImage->setVisible(b);
}
//���ñ������߶�
//������
//		size���߶�
//����ֵ����
void TitleBar::setTitleSize(int size)
{
	_size = size;
	setFixedHeight(_size);
}
//����ƶ��¼�
//������
//		event:�¼�
//����ֵ����
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (_dragging)
	{
		int dx = event->globalX()-_preMouseX;
		int dy = event->globalY()-_preMouseY;
		_parentActivity->move(_pwPreX+dx,_pwPreY+dy);
	}
}
//��갴���¼�
//������
//		event:�¼�
//����ֵ����
void TitleBar::mousePressEvent(QMouseEvent *event)
{
	//ֻ�е�������ʾ״̬Ϊ����״̬ʱ�ſ����϶�
	if ((event->button() & Qt::LeftButton)&&(_parentActivity->showMode()==Activity::NORMAL))
	{
		_dragging = true;
		_preMouseX = event->globalX();
		_preMouseY = event->globalY();
		_pwPreX = _parentActivity->pos().x();
		_pwPreY = _parentActivity->pos().y();
	}
}
//����ɿ��¼�
//������
//		event:�¼�
//����ֵ����
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::LeftButton))
	{
		_dragging = false;
	}
}
//���˫���¼�
//������
//		event:�¼�
//����ֵ����
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	maximizeParentWidget();
}
//��С������
//��������
//����ֵ����
void TitleBar::minimizeParentWidget()
{
	//_parentActivity->showMinimized();
	//_parentActivity->setShowMode(Activity::MINIMIZED);
	emit minimizeButtonClicked();
}
//��󻯴���
//��������
//����ֵ����
void TitleBar::maximizeParentWidget()
{
	if (_parentActivity->showMode()==Activity::MAXIMIZED)
	{
		//_parentActivity->showNormal();
		//_parentActivity->setShowMode(Activity::NORMAL);
		updateMaximizeButtonImage();
		_maximizeBtn->setIcon(*_maxPix);
	}
	else
	{
		//_parentActivity->showMaximized();
		//_parentActivity->setShowMode(Activity::MAXIMIZED);
		updateMaximizeButtonImage();
		_maximizeBtn->setIcon(*_restorePix);
		//_parentActivity->move(0,0);
	}
	emit maximizeButtonClicked();
}

//�رմ���
//��������
//����ֵ����
void TitleBar::closeParentWidget()
{
	//_parentActivity->close();
	emit closeButtonClicked();
}
//���ͼƬ·��
//������
//		pix:λͼ
//		url:ͼƬ·��
//����ֵ����
void TitleBar::getPixelImage(QPixmap* pix,const char* url)
{
	std::string filename;
	std::string tempStr = url;
	if (tempStr.find("@image/")!=std::string::npos)
	{
		getResImageUrl(filename,url);
	}
	else if (tempStr.find("@icon/")!=std::string::npos)
	{
		getResIconUrl(filename,url);
	}

	if (!filename.empty())
	{
		if (!pix->load(filename.c_str()))
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Load pixmap %s failed\n",filename.c_str());
			printf(szMsg);
		}
	}else
	{
		if (!pix->load(url))
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Load pixmap %s failed\n",url);
			printf(szMsg);
		}
	}
}
//������С����ť��Ӧ��ͼƬ·��
//������
//		url��ͼƬ·��
//����ֵ����
void TitleBar::setMinimizeButtonImage(const char* url)
{
	getPixelImage(_minPix,url);
	_minimizeBtn->setIcon(*_minPix);
}
//������󻯰�ť��Ӧ��ͼƬ·��
//������
//		url��ͼƬ·��
//����ֵ����
void TitleBar::setMaximizeButtonImage(const char* url)
{
	getPixelImage(_maxPix,url);
	updateMaximizeButtonImage();
}
//������󻯰�ťͼƬ
//��������
//����ֵ����
void TitleBar::updateMaximizeButtonImage()
{
	if (_parentActivity&&_parentActivity->showMode()==Activity::MAXIMIZED)
	{
		_maximizeBtn->setIcon(*_restorePix);
	}
	else
	{
		_maximizeBtn->setIcon(*_maxPix);
	}
}
//���ûָ���ť��Ӧ��ͼƬ·��
//������
//		url��ͼƬ·��
//����ֵ����
void TitleBar::setRestoreButtonImage(const char* url)
{
	getPixelImage(_restorePix,url);
}
//���ùرհ�ť��Ӧ��ͼƬ·��
//������
//		url��ͼƬ·��
//����ֵ����
void TitleBar::setCloseButtonImage(const char* url)
{
	getPixelImage(_closePix,url);
	_closeBtn->setIcon(*_closePix);
}
//����iconͼƬ·��
//������
//		url��ͼƬ·��
//����ֵ����
void TitleBar::setIconImage(const char* url)
{
	_iconImage->setImage(url);
}
//���ñ���������
//������
//		text������������
//����ֵ����
void TitleBar::setTitleText(const char* text)
{
	_titleText->setText(text);
}
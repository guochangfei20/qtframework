#include <UIs/CustomActivity.h>
#include "UIs/TitleBar.h"
#include <QtGui>
#include <QtWidgets>
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include "Utils/util.h"
#include "Utils/variant.h"
#include "Common/qt_context.h"
#include "UIs/SplashWindow.h"
////���캯��
//��������
//����ֵ����
CustomActivity::CustomActivity(void):_titleBar(NULL),_mouseArea(Other),_dragging(false),
	_curMouseX(0),_curMouseY(0),_preX(0),_preY(0),_preShowMode(Activity::NORMAL)
{
}
////���캯��
//��������
//����ֵ����
CustomActivity::CustomActivity(SplashWindow* pSplashWindow):Activity(pSplashWindow),_titleBar(NULL),_mouseArea(Other),_dragging(false),
	_curMouseX(0),_curMouseY(0),_preX(0),_preY(0),_preShowMode(Activity::NORMAL)
{
}
//�����¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::paintEvent(QPaintEvent *)
{ 
	//���ڱ߿�ΪԲ��
	/*QPainter p(this);
	p.drawRoundedRect(0,0,width()-1,height()-1,5,5);*/
}

//��������
//��������
//����ֵ����
CustomActivity::~CustomActivity(void)
{
}
//���ڴ���֮ǰ����Ϊ
//��������
//����ֵ���ɹ�����true,���򷵻�false
bool CustomActivity::actionBeforeCreated()
{
	//�ڴ���֮ǰ����window��ʽ,��һ������ȥ��Ĭ�Ի����ܣ��ڶ��������������������������ť�Ҽ��˵�����������������������С���뻹ԭ
	setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint);
	setMouseTracking(true);  //��겻������ʱҲ���Խ�������ƶ��¼�
	
	//����һ����ʱ������������ڲ�ͬ�����״̬
	_timer = new QTimer;
	connect(_timer,SIGNAL(timeout()),this,SLOT(regionMouse()));
	

	QPalette palette;
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background,QColor(51,107,252));
	setPalette(palette);
	return true;
}
//���ڴ���֮�����Ϊ
//��������
//����ֵ���ɹ�����true,���򷵻�false
bool CustomActivity::actionAfterActived()
{
	//40ms����һ��

	return true;
}
//ѡ���¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::focusInEvent(QFocusEvent *event)
{
    Activity::focusInEvent(event);
}
//���뽹���¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::focusOutEvent(QFocusEvent * event)
{
   // _timer->stop();
    Activity::focusOutEvent(event);
}
//���봰���¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::enterEvent(QEvent *event)
{
	_timer->start(100);
    Activity::enterEvent(event);
}

void CustomActivity::installContent()
{
	//�ܲ���
	QVBoxLayout* frameLayout = new QVBoxLayout;
	int borderWidth = 4; //����Activity��Χ�߿�Ŀ��
	if (R::Instance()->getConfigResource("CustomActivityBorderWidth"))
	{
		borderWidth = R::Instance()->getConfigResource("CustomActivityBorderWidth")->value<int>();
	}
	frameLayout->setContentsMargins(borderWidth,borderWidth,borderWidth,borderWidth); //�����marginһ��Ҫ�����洰�ڵ��ĸ����ƴ�С�������һЩ���������任�����л������
    frameLayout->setSpacing(4);
	setLayout(frameLayout);
	//���ڱ�����
	for (int i=0;i<_content->getChildNum();i++)
	{
		ui_node* node = _content->getChild(i);
		if (strcmp(node->getName(),"TitleBar")==0)
		{
			_titleBar = (TitleBar*)node->getObject();
			_titleBar->setParentActivity(this);
          		//���ñ�������Ŀ�Ƿ�ɼ�
			if (node->hasAttribute("minimizeButtonHint"))
			{
				_titleBar->setMinimizeButtonVisible(STR_TO_BOOL(node->getAttribute("minimizeButtonHint")));
			}
			if (node->hasAttribute("maximizeButtonHint"))
			{
				_titleBar->setMaximizeButtonVisible(STR_TO_BOOL(node->getAttribute("maximizeButtonHint")));
			}
			if (node->hasAttribute("closeButtonHint"))
			{
				_titleBar->setCloseButtonVisible(STR_TO_BOOL(node->getAttribute("closeButtonHint")));
			}
			if (node->hasAttribute("titleTextHint"))
			{
                _titleBar->setTitleText(" ");
			}
			if (node->hasAttribute("iconHint"))
			{
				_titleBar->setIconVisible(STR_TO_BOOL(node->getAttribute("iconHint")));
			}
			if (node->hasAttribute("minmaxButtonHint"))
			{
				_titleBar->setMinimizeButtonVisible(STR_TO_BOOL(node->getAttribute("minmaxButtonHint")));
				_titleBar->setMaximizeButtonVisible(STR_TO_BOOL(node->getAttribute("minmaxButtonHint")));
			}
			//��ԭ��ťͼƬ
			if (node->hasAttribute("restoreButtonImage"))
			{
				_titleBar->setRestoreButtonImage(node->getAttribute("restoreButtonImage"));
			}
			else
			{
				_titleBar->setRestoreButtonImage("@icon/restore_win.png");
			}
			//��С����ťͼƬ
			if (node->hasAttribute("minimizeButtonImage"))
			{
				_titleBar->setMinimizeButtonImage(node->getAttribute("minimizeButtonImage"));
			}
			else
			{
				_titleBar->setMinimizeButtonImage("@icon/min_win.png");
			}
			//��󻯰�ťͼƬ
			if (node->hasAttribute("maximizeButtonImage"))
			{
				_titleBar->setMaximizeButtonImage(node->getAttribute("maximizeButtonImage"));
			}
			else
			{
				_titleBar->setMaximizeButtonImage("@icon/max_win.png");
			}
			//�˳���ťͼƬ
			if (node->hasAttribute("closeButtonImage"))
			{
				_titleBar->setCloseButtonImage(node->getAttribute("closeButtonImage"));
			}
			else
			{
				_titleBar->setCloseButtonImage("@icon/quit.png");
			}
			//��������
			if (node->hasAttribute("titleText"))
			{
				_titleBar->setTitleText(node->getAttribute("titleText"));
			}
			else
			{
                _titleBar->setTitleText(" ");
			}
			if (node->hasAttribute("size"))
			{
				_titleBar->setTitleSize(STR_TO_INT(node->getAttribute("size")));
			}
			else
			{
				_titleBar->setTitleSize(25);
			}
			if (node->hasAttribute("iconImage"))
			{
				_titleBar->setIconImage(node->getAttribute("iconImage"));
			}
			else
			{
				_titleBar->setIconImage("@icon/default_icon.png");
			}
			_titleBar->setTitleNode(node);
			break;
		}
	}
	//���û�ж������������Ĭ�ϵı�����
	if (!_titleBar)
	{
		_titleBar = new TitleBar;
		_titleBar->setParentActivity(this);
		_titleBar->setMinimizeButtonImage("@icon/min_win.png");
		_titleBar->setMaximizeButtonImage("@icon/max_win.png");
		_titleBar->setRestoreButtonImage("@icon/restore_win.png");
		_titleBar->setCloseButtonImage("@icon/quit.png");
		_titleBar->setIconImage("@icon/default_icon.png");
		_titleBar->setTitleText("");
	}
	//������������¼�
	relateTitleBar();
	//����������ӽ�����
	frameLayout->addWidget(_titleBar);

	//��������ӽ�ȥ��Ϊ�˷�ֹ���ݶ�Ϊ����ɫ����һ��Widget
	if (_content->getType()==ui_node::LAYOUT)
	{
		QLayout* contentLayout = (QLayout*)_content->getObject();
        contentLayout->setMargin(4);
		QWidget* widget = new QWidget;
		widget->setLayout(contentLayout);
		widget->setAutoFillBackground(true);
		//���ñ�����ɫ
		const variant* v = R::Instance()->getConfigResource("BackgroundColor");
		if (v)
		{
			QPalette palette;
			palette.setColor(QPalette::Background,QColor(QString(v->getString())));
			widget->setPalette(palette);
		}else
		{
			QPalette palette;
			palette.setColor(QPalette::Background,QColor(240,240,240));
			widget->setPalette(palette);
		}
		widget->setParent(this);
		frameLayout->addWidget(widget);
	}
	else if (_content->getType()==ui_node::WIDGET)
	{
		frameLayout->addWidget((QWidget*)_content->getObject());
	}
}

//�ض�λ���
//��������
//����ֵ����
void CustomActivity::regionMouse()
{
	QPoint p = cursor().pos();
    QRect rec = geometry();
	int x = p.x() - rec.x();
	int y = p.y() - rec.y();
	int w = rec.width();
	int h = rec.height();

	int resizeMargin = 4;
	//������Ϊ2��Ҫ�ȴ��ڵ�contents_marginСһ�㣬���������봰���ڲ��ؼ��޷�����Ӧ����ƶ���Ϣ���ᵼ�����仯����
	if ((x>resizeMargin&&x<w-resizeMargin&&y>resizeMargin&&y<h-resizeMargin)||(x<0|x>w|y<0|y>h))
	{
		_mouseArea = Other;
		setCursor(Qt::ArrowCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = TopLeft;
		setCursor(Qt::SizeFDiagCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = TopRight;
		setCursor(Qt::SizeBDiagCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = BottomLeft;
		setCursor(Qt::SizeBDiagCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = BottomRight;
		setCursor(Qt::SizeFDiagCursor);
		return;
	}
	else if (x>resizeMargin&&x<w-resizeMargin&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = Top;
		setCursor(Qt::SizeVerCursor);
		return;
	}
	else if (x>resizeMargin&&x<w-resizeMargin&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = Bottom;
		setCursor(Qt::SizeVerCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y>resizeMargin&&y<h-resizeMargin)
	{
		_mouseArea = Left;
		setCursor(Qt::SizeHorCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y>resizeMargin&&y<h-resizeMargin)
	{
		_mouseArea = Right;
		setCursor(Qt::SizeHorCursor);
		return;
	}
	else
	{
		_mouseArea = Other;
		setCursor(Qt::ArrowCursor);
		return;
	}
	
}

//�뿪�����¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::leaveEvent(QEvent *event)
{
	
	setCursor(Qt::ArrowCursor);
	_timer->stop();
	Activity::leaveEvent(event);
}
//������ʾģʽ
//������
//		mode:��ʾģʽ
//����ֵ����Դ
void CustomActivity::setShowMode(ShowMode mode)
{

	Activity::setShowMode(mode);
	if (_bPrepared)
	{
		_titleBar->updateMaximizeButtonImage();
	}
}
//����ƶ��¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::mouseMoveEvent(QMouseEvent *event)
{
	if (showMode()!=Activity::NORMAL)
	{
		setCursor(Qt::ArrowCursor);
		Activity::mouseMoveEvent(event);
		return;
	}
	_curMouseX = event->globalX();
	_curMouseY = event->globalY();
	int gx = event->globalX();
	int gy = event->globalY();
	if (_dragging)
	{
		QRect g = geometry();
		switch (_mouseArea)
		{
		case Left:
			g.setLeft(gx);
			break;
		case Right:
			g.setRight(gx);
			break;
		case Bottom:
			g.setBottom(gy);
			break;
		case Top:
			g.setTop(gy);
			break;
		case TopLeft:
			g.setTop(gy);
			g.setLeft(gx);
			break;
		case TopRight:
			g.setTop(gy);
			g.setRight(gx);
			break;
		case BottomLeft:
			g.setBottom(gy);
			g.setLeft(gx);
			break;
		case BottomRight:
			g.setBottom(gy);
			g.setRight(gx);
			break;
		case Other:
				break;
		}
		if (_mouseArea!=Other)
		{
			setGeometry(g);
		}
			
	}else
	{
		regionMouse();
	}
	Activity::mouseMoveEvent(event);
}
//��갴���¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::mousePressEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::LeftButton)&&!_dragging)
	{
		_dragging = true;
		regionMouse();
		_timer->stop();
	}
	Activity::mousePressEvent(event);
}
//����ɿ��¼�
//������
//		event:�¼�
//����ֵ����
void CustomActivity::mouseReleaseEvent(QMouseEvent *event)
{
	_dragging = false;
	if (_mouseArea!=Other)
	{
		this->releaseMouse();
		setCursor(Qt::ArrowCursor);
		//regionMouse();
	}
	Activity::mouseReleaseEvent(event);
}

void CustomActivity::relateTitleBar()
{
	connect(_titleBar,SIGNAL(minimizeButtonClicked()),this,SLOT(minimizeActivity()));
	connect(_titleBar,SIGNAL(maximizeButtonClicked()),this,SLOT(maximizeActivity()));
	connect(_titleBar,SIGNAL(closeButtonClicked()),this,SLOT(closeActivity()));
}
////��д�Ŵ���С����
//��ʾ�¼�
//��������
//����ֵ����
void CustomActivity::showEvent(QShowEvent *e)
{
	if (_preShowMode==Activity::MAXIMIZED)
	{
		setShowMode(Activity::MAXIMIZED);
	}
	else if (_preShowMode==Activity::NORMAL)
	{
		setShowMode(Activity::NORMAL);
	}
	Activity::showEvent(e);
}
//�����¼�
//��������
//����ֵ����
void CustomActivity::hideEvent(QHideEvent *e)
{
	_preShowMode = showMode();
	setShowMode(Activity::MINIMIZED);
	Activity::hideEvent(e);
}
//����
//��������
//����ֵ������ɹ�����true,���򷵻�false
bool CustomActivity::active()
{
    if(showMode()==MINIMIZED)
    {
        setShowMode(_preShowMode);
    }
    return Activity::active();
}
//��С������
//��������
//����ֵ����
void CustomActivity::minimizeActivity(){minimizeActivityEvent();}
//��󻯴���
//��������
//����ֵ����
void CustomActivity::maximizeActivity(){maximizeActivityEvent();}
//�رմ���
//��������
//����ֵ����
void CustomActivity::closeActivity(){closeActivityEvent();}
//��С���¼�
//��������
//����ֵ����
void CustomActivity::minimizeActivityEvent()
{
	this->activeMinimized();
	setShowMode(Activity::MINIMIZED);
}
//����¼�
//��������
//����ֵ����
void CustomActivity::maximizeActivityEvent()
{
	if (showMode()==Activity::MAXIMIZED)
	{
		activeNormal();
		setShowMode(Activity::NORMAL);
	}
	else
	{
		activeMaximized();
		setShowMode(Activity::MAXIMIZED);
	}
}
//�ر��¼�
//��������
//����ֵ����
void CustomActivity::closeActivityEvent()
{
	close();
}

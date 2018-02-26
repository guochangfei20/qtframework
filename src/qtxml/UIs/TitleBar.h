/*!
 * \file TitleBar.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <QWidget>
#include <QFrame>

class ui_node;
class QToolButton;
class QLabel;
class sl_ImageWidget;
class QPixmap;
class Activity;
/*!
 * \class TitleBar
 *
 * \brief ���ڱ�����
 *
 * \author ����
 * \date ���� 2016
 */
class TitleBar : public QWidget
{
	Q_OBJECT
public:
	//���캯��
	//������
	//		activity������
	//����ֵ����
	TitleBar(Activity* activity=NULL);
	//��������
	//��������
	//����ֵ����
	~TitleBar(void);
	//���ñ�������Ӧ��ui�ڵ�
	//������
	//		node��ui�ڵ�
	//����ֵ����
	void setTitleNode(ui_node* node){_titleNode = node;}
	//���ñ�������Ӧ�Ĵ���
	//������
	//		activity������
	//����ֵ����
	void setParentActivity(Activity* activity){_parentActivity = activity;}
	//������С����ť��Ӧ��ͼƬ·��
	//������
	//		url��ͼƬ·��
	//����ֵ����
	void setMinimizeButtonImage(const char* url);
	//������󻯰�ť��Ӧ��ͼƬ·��
	//������
	//		url��ͼƬ·��
	//����ֵ����
	void setMaximizeButtonImage(const char* url);
	//���ûָ���ť��Ӧ��ͼƬ·��
	//������
	//		url��ͼƬ·��
	//����ֵ����
	void setRestoreButtonImage(const char* url);
	//���ùرհ�ť��Ӧ��ͼƬ·��
	//������
	//		url��ͼƬ·��
	//����ֵ����
	void setCloseButtonImage(const char* url);
	//����iconͼƬ·��
	//������
	//		url��ͼƬ·��
	//����ֵ����
	void setIconImage(const char* url);
	//���ñ���������
	//������
	//		text������������
	//����ֵ����
	void setTitleText(const char* text);
	//���ñ������߶�
	//������
	//		size���߶�
	//����ֵ����
	void setTitleSize(int size);
	//������󻯰�ťͼƬ
	//��������
	//����ֵ����
	void updateMaximizeButtonImage();
	//������С����ť�Ƿ���ʾ
	//������
	//		b���Ƿ���ʾ
	//����ֵ����
	void setMinimizeButtonVisible(bool b);
	//������󻯰�ť�Ƿ���ʾ
	//������
	//		b���Ƿ���ʾ
	//����ֵ����
	void setMaximizeButtonVisible(bool b);
	//���ùرհ�ť�Ƿ���ʾ
	//������
	//		b���Ƿ���ʾ
	//����ֵ����
	void setCloseButtonVisible(bool b);
	//���ñ����������Ƿ���ʾ
	//������
	//		b���Ƿ���ʾ
	//����ֵ����
	void setTitleTextVisible(bool b);
	//���ñ�����icon�Ƿ���ʾ
	//������
	//		b���Ƿ���ʾ
	//����ֵ����
	void setIconVisible(bool b);
protected slots:
	//��С������
	//��������
	//����ֵ����
	void minimizeParentWidget();
	//��󻯴���
	//��������
	//����ֵ����
	void maximizeParentWidget();
	//�رմ���
	//��������
	//����ֵ����
	void closeParentWidget();
signals:
	//��С����ť�����
	//��������
	//����ֵ����
	void minimizeButtonClicked();
	//��󻯰�ť�����
	//��������
	//����ֵ����
	void maximizeButtonClicked();
	//�رհ�ť�����
	//��������
	//����ֵ����
	void closeButtonClicked();
protected:
	//���ƴ��ڲ���
	//����ƶ��¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mouseMoveEvent(QMouseEvent *event);
	//��갴���¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mousePressEvent(QMouseEvent *event);
	//����ɿ��¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mouseReleaseEvent(QMouseEvent *event);
	//���˫���¼�
	//������
	//		event:�¼�
	//����ֵ����
	void mouseDoubleClickEvent(QMouseEvent *event);
	//���ͼƬ·��
	//������
	//		pix:λͼ
	//		url:ͼƬ·��
	//����ֵ����
	void getPixelImage(QPixmap* pix,const char* url);
	

protected:
	ui_node* _titleNode;
	QToolButton* _minimizeBtn;  //��С����ť
	QToolButton* _maximizeBtn; //��󻯰�ť
	QToolButton* _closeBtn; //���˳���ť
	QLabel* _titleText;  //��������
	sl_ImageWidget* _iconImage;  //����ͼ��
	int _size;  //��������С

	QPixmap* _maxPix,*_restorePix,*_minPix,*_closePix;
	Activity* _parentActivity;

	bool _dragging;
	bool _minimized;
	int _pwPreX;  //������֮ǰ��λ��
	int _pwPreY;
	int _preMouseX; //���֮ǰ��λ��
	int _preMouseY;

};


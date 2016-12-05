/*!
 * \file event_handler.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include <QtCore/QObject>
class QTableWidgetItem;
class QTreeWidgetItem;
class ui_node;
class xml_node;

/*!
 * \class event_handler
 *
 * \brief
	��Ҫ�¼���������Ҫ���������������͵���Ϣ
	1.�󶨿ؼ�ͨ��Signal���͵���Ϣ����ͨ��connect()�������ӵ�handle()�Ĳۺ�����
		��ʱֻ�ܴ���û�в�������Ϣ����
	2.�󶨿ؼ����յ����¼���ͨ��installEventFilter()������
 *
 * \author ����
 * \date ���� 2016
 */

class event_handler: public QObject
{
	Q_OBJECT
public:
	//���캯��
	//������
	//	parent: ��ָ��
	//����ֵ����
	event_handler(QObject* parent=0);
	//��������
	//��������
	//����ֵ����
	~event_handler(void);
	protected slots:
		//��Ϣ����
		//������
		//		int: ��������
		//����ֵ����
		void handle(int);
		//��Ϣ����
		//������
		//		int: ��������
		//		int: ��������
		//����ֵ����
		void handle(int,int);
		//��Ϣ����
		//��������
		//����ֵ����
		void handle();
		//��Ϣ����
		//������
		//	QTreeWidgetItem*:��������
		//	int: ��������
		//����ֵ����
		void handle(QTreeWidgetItem*,int);
protected:
	//�¼�������
	//������
	//		obj: ��������
	//		event: �¼�ָ��
	//����ֵ���Ƿ������
	bool eventFilter(QObject *obj, QEvent *event);
	//������ִ��ui_node��������
	//������
	//		node: ui_node����ָ��
	//����ֵ����
	void parseAndExecuteCommandForUINode(ui_node* node);
	//������ִ��xml_node��������
	//������
	//		node: xml_node����ָ��
	//����ֵ����
	void parseAndExecuteCommandForXmlNode(xml_node* node);
private:
	std::string _shortcutString;  //��ݼ��ַ���������Ҫ��Ҫʶ������
	int _globalPosX;
	int _globalPosY;
};

static event_handler gs_event_handler; //����һ��ȫ�־�̬����


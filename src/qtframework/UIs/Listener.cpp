#include <UIs/Listener.h>
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
//���캯��
//��������
//����ֵ����
Listener::Listener(void):_sender(NULL)
{
}

//��������
//��������
//����ֵ����
Listener::~Listener(void)
{
	//delete _sender;
}
//����
//��������
//����ֵ����
void Listener::trigger()
{
	QObject* senderobj = this->sender();
	_sender = (ui_node*)getUINodeFromObject(senderobj);
}
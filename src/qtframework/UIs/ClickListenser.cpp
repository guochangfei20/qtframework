#include <UIs/ClickListenser.h>
#include <QtCore/QVariant>
#include "Uicreator/ui_node.h"

Q_DECLARE_METATYPE(ui_node*);

ClickListenser::ClickListenser(void):Listener()
{
}


ClickListenser::~ClickListenser(void)
{
}

void ClickListenser::trigger()
{
	Listener::trigger(); //�ȵ��ø���ĺ���
	onClick(_sender);
}

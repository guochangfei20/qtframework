#include <QF_config_internal.h>
#include "CQF_DataBuffer.h"

QF_BEGIN_NAMESPACE(QF)


IQF_DataBuffer* QF_CreateDataBufferObject(int iSize) 
{
	IQF_DataBuffer* p = new CQF_DataBuffer() ;
	assert(p) ;

	if (p)
	{
		// ���û�������С��������ɹ����򷵻�null����ɾ��CQF_DataBuffer����
		bool success = p->SetSize (iSize) ;
		if (!success)
		{
			delete p ;
			p = NULL ;
		}
	}

	return p ;
}

QF_END_NAMESPACE

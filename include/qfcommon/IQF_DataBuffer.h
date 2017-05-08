#ifndef QF_IQF_DATABUFFER_H__
#define QF_IQF_DATABUFFER_H__

#include <qf_config.h>

QF_BEGIN_NAMESPACE(QF)

/// \brief ���ݻ������ӿ�
///
/// ���ݻ������ӿڡ�
///
/// \note ͨ��ȫ�ֺ���QF_CreateDataBufferObject()����һ��IQF_DataBuffer����
///
//##ModelId=3F9CF3CD0253
class IQF_DataBuffer
{
  public:
	/// \brief �ͷ����ݻ���������
	/// 
	/// �ͷ����ݻ���������
	///
	/// \return ��
	///
	/// \param ��
	///
	//##ModelId=3F9CF3CD0276
    virtual void Release() = 0;

	/// \brief ��ȡ���ݻ�������С��
	/// 
	/// ��ȡ���ݻ�������С����λΪ�ֽڡ�
	///
	/// \return ���ݻ�������С
	///
	/// \param ��
	///
    //##ModelId=3F9CF3CD0272
    virtual int GetSize() = 0;

	/// \brief �������ݻ�������С��
	/// 
	/// �������ݻ�������С���������ڴ��ط��䡣������ԭ���ڴ�����ʧЧ��ԭ�����ݽ���ʧ��
	///
	/// \return ������óɹ����ڴ����ɹ����򷵻�true�����򷵻�false��
	///
	/// \param iSize�����ݻ�������С����λΪ�ֽڡ����iSize == 0�������ԭ���ڴ�������ʹ��GetBufferPtr() == NULL��
	///
    //##ModelId=3F9CF3CD0261
    virtual bool SetSize(int iSize) = 0;

	/// \brief ��ȡָ�����ݻ������ڴ��׵�ַ��ָ�롣
	/// 
	/// ��ȡָ�����ݻ������ڴ��׵�ַ��ָ�롣
	///
	/// \return ָ�����ݻ������ڴ��׵�ַ��ָ�롣�����δ�����ڴ���䣬�򷵻�NULL��
	///
	/// \param ��
	///
    //##ModelId=3F9CF3CD0274
    virtual char* GetBufferPtr() = 0;

	/// \brief ��ֵ����
	///
	/// ���������ݻ��������ݸ�����ǰ���ݻ�����
	///
	/// \return ��ǰ���ݻ�����������
	///
	/// \param right����ֵ�����Ҳ�����
	///
    //##ModelId=3FA4C7290085
    virtual IQF_DataBuffer& operator=(const IQF_DataBuffer& right) = 0;

	/// \brief �������
	///
	/// �жϸ������ݻ����������Ƿ��뵱ǰ���ݻ������������
	///
	/// \return �����ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right����������Ҳ�����
	///
    //##ModelId=3FA4C7290112
    virtual int operator==(const IQF_DataBuffer& right) = 0;

	/// \brief ���������
	///
	/// �жϸ������ݻ����������Ƿ��뵱ǰ���ݻ��������ݲ����
	///
	/// \return �������ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right������������Ҳ�����
	///
    //##ModelId=3FA4C729017F
    virtual int operator!=(const IQF_DataBuffer& right) = 0;

};

//extern "C"
//{
	/// \brief ��������������һ�����ݻ���������
	/// 
	/// ����һ�����ݻ��������󣬲����ݳ�ʼ��С�����ڴ���䡣
	/// 
	/// \return ��������ɹ����򷵻����ݻ����������ָ�룻���򷵻�NULL
	/// 
	/// \param iSize�����ݻ������ĳ�ʼ��С�����iSize == 0���򲻽����ڴ���䣬��GetBufferPtr() == NULL��
	///
	QF_API IQF_DataBuffer* QF_CreateDataBufferObject(int iSize);
//}

/// \brief ���ݻ�����������ָ��
/// 
/// ���ݻ�����������ָ�롣��װ�����ݻ���������Ĵ������ͷţ�������Ϊ�ֲ��Զ�����ʹ��
/// 
class IQF_DataBufferPtr 
{
public :
	///	\brief ���캯��
	///
	/// ���ݻ���������ָ��Ĺ��캯��
	///
	/// \param iSize�����ݻ������ĳ�ʼ��С�����iSize == 0���򲻽����ڴ���䣬��GetBufferPtr() == NULL��
	///
	/// \note \e ��̬���ӿ⣺QF_commontype.lib
	///	
	IQF_DataBufferPtr(int iSize)
	{
		m_ptr = QF_CreateDataBufferObject(iSize) ;
	}

	///	\brief ��������
	///
	/// ���ݻ���������ָ�����������
	///
	~IQF_DataBufferPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief ָ�����������
	///
	/// ���ݻ���������ָ���ָ����������ء�
	///
	IQF_DataBuffer* operator->() const 
	{
		return m_ptr;
	}

	/// \brief ���ݻ���������
	///
	/// public��Ա�����ݻ���������ָ���ʵ�����ݻ���������
	///
	IQF_DataBuffer * m_ptr ;

} ;

QF_END_NAMESPACE
#endif /* Z_QF_II_INCLUDE_IQF_DATABUFFER_H_HEADER_INCLUDED_C0630F69 */





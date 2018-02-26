#ifndef QF_IQF_PROPERTYSET_H__
#define QF_IQF_PROPERTYSET_H__

#include <qf_config.h>
#include <IQF_Field.h>

QF_BEGIN_NAMESPACE(QF)

class IQF_Field;
class IQF_DataBuffer;

/// \brief ���Լ��Ͻӿ�
///
/// ���Լ��Ͻӿڡ���װ�˶����Լ����и����ֶε���ӡ�ɾ���Լ������Ȳ�����
///
/// \note ͨ��ȫ�ֺ���QF_CreatePropertySetObject()����һ��IQF_PropertySet����
///
//##
class IQF_PropertySet
{
  public:
	/// \brief �ͷ����Լ��϶���
	/// 
	/// �ͷ����Լ��϶���
	///
	/// \return ��
	///
	/// \param ��
	///
    virtual void Release() = 0;

	/// \brief ������Լ����е��������Լ�¼
	/// 
	/// ������Լ����е��������Լ�¼
	///
	/// \return ��
	///
	/// \param ��
	///
    virtual void Clear() = 0;

    /// \brief ��ȡ���Լ����е��ֶθ�����
	///
	/// ��ȡ���Լ����е��ֶθ�����
	///
	/// \return ���Լ����е��ֶθ���
	///
	/// \param ��
	///
    virtual int GetCount() = 0;

    /// \brief ͨ���ֶ����ƻ�ȡָ�������ֶ�
	///
	/// ͨ���ֶ����ƻ�ȡָ�������ֶΡ�
	///
	/// \return ָ�������ֶζ����ָ�롣���û�и������Ƶ������ֶΣ��򷵻�NULL��
	///
	/// \param szName���ֶ�����
	///
    virtual IQF_Field* GetPropertyPtr(const char* szName) = 0;

    /// \brief ��ȡ���Լ����е�һ�������ֶζ���
	///
	/// ��ȡ���Լ����е�һ�������ֶζ�����GetNextPropertyPtr()����ʹ�ã����ڶ����Լ��Ͻ��б�����
	///
	/// \return ��һ�������ֶζ����ָ�롣������Լ���Ϊ�գ��򷵻�NULL��
	///
	/// \param ��
	///
    virtual IQF_Field* GetFirstPropertyPtr() = 0;

    /// \brief ��ȡ���Լ�����ָ���ֶε���һ�������ֶζ���
	///
	/// ��ȡ���Լ�����ָ���ֶε���һ�������ֶζ�����GetFirstPropertyPtr()����ʹ�ã����ڶ����Լ��Ͻ��б�����
	///
	/// \return ��һ�������ֶζ����ָ�롣������Լ���Ϊ�գ���ǰ�����ֶβ������Լ����У���ǰ�����ֶ��Ѿ������Լ��ϵ����һ�������ֶΣ��򷵻�NULL��
	///
	/// \param pCurrentField����ǰ�����ֶζ����ָ��
	///
    virtual IQF_Field* GetNextPropertyPtr(IQF_Field* pCurrentField) = 0;
    
    /// \brief �����Լ������½�һ�������ֶΡ�
	///
	/// ���ݸ������ơ����͵���Ϣ�����Լ������½�һ�������ֶΡ�
	///
	/// \return ����½��ɹ����򷵻��½������ֶζ����ָ�룻���򷵻�NULL��
	///
	/// \param szName�������ֶ����ơ������ֶ����ƽ���ת��Ϊ��д������ͬһ���Լ����б���Ψһ��
	/// \param szCaption�������ֶα��⡣����ΪNULL��
	/// \param iType�������ֶ��������͡��μ�QF_commondef.h�С��������͡����ֵ���ض��塣
	/// \param bToBeArchive��ѡ�������Ϊtrue��ʾ��Archive()ʱ�������ֶ�Ӧ�鵵�����ݻ������У�Ϊfalse��ʾ��Archive()ʱ�������ֶν������ԡ�ȱʡΪtrue��
	///
    virtual  IQF_Field* AddProperty(const char* szName, const char* szCaption, int iType, bool bToBeArchive = true) = 0;

	/// \brief ���һ�������ֶΡ�
	///
	/// ���һ�������ֶε����Լ����С������ӳɹ���������ֶε��ͷ������Լ��ϸ����û�������ʽ����pField->Release()��
	///
	/// \return �����ӳɹ����򷵻�true�����򷵻�false��������Լ������Ѵ���ͬ�������ֶΣ��򷵻�false��
	///
	/// \param pField������ӵ������ֶΡ�
	///
    virtual bool AddProperty(IQF_Field* pField) = 0;
    
    /// \brief ɾ��ָ�������ֶΡ�
	///
	/// ���ݸ����������ֶ�����ɾ��ָ�������ֶ�
	///
	/// \return ���ɾ���ɹ����򷵻�true�����򷵻�false��������Լ����в�����ָ�����Ƶ������ֶΣ��򷵻�false��
	///
	/// \param szName��Ҫɾ���������ֶε�����
	///
    virtual bool DeleteProperty(const char* szName) = 0;

    /// \brief ����QF_INTEGER��������ֵ
    ///
    /// ����QF_INTEGER��������ֵ��
	/// ��������Լ������Ѿ���szName��ָ�������ԣ���������ΪQF_INTEGER�������ø����Ե���ֵ������������Ͳ�һ�£��򷵻�false��
    /// ��������Լ�����û��szName��ָ�������ԣ������szName���ڱ����Լ������½�һ�����ԣ�����������ֵ��
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szName�������ֶ����ơ������ֶ����ƽ���ת��Ϊ��д������ͬһ���Լ����б���Ψһ��
	/// \param iValue��Ҫ���õ��ֶ�ֵ��
	/// \param bToBeArchive��ѡ�������Ϊtrue��ʾ��Archive()ʱ�������ֶ�Ӧ�鵵�����ݻ������У�Ϊfalse��ʾ��Archive()ʱ�������ֶν������ԡ�ȱʡΪtrue��
	///
    virtual bool SetIntProperty(const char* szName, int iValue, bool bToBeArchive = true) = 0;

    /// \brief ����QF_BOOL��������ֵ
    ///
    /// ����QF_BOOL��������ֵ��
	/// ��������Լ������Ѿ���szName��ָ�������ԣ���������ΪQF_BOOL�������ø����Ե���ֵ������������Ͳ�һ�£��򷵻�false��
    /// ��������Լ�����û��szName��ָ�������ԣ������szName���ڱ����Լ������½�һ�����ԣ�����������ֵ��
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szName�������ֶ����ơ������ֶ����ƽ���ת��Ϊ��д������ͬһ���Լ����б���Ψһ��
	/// \param bValue��Ҫ���õ��ֶ�ֵ��
	/// \param bToBeArchive��ѡ�������Ϊtrue��ʾ��Archive()ʱ�������ֶ�Ӧ�鵵�����ݻ������У�Ϊfalse��ʾ��Archive()ʱ�������ֶν������ԡ�ȱʡΪtrue��
	///
    virtual bool SetBoolProperty(const char* szName, bool bValue, bool bToBeArchive = true) = 0;

    /// \brief ����QF_DOUBLE��������ֵ
    ///
    /// ����QF_DOUBLE��������ֵ��
	/// ��������Լ������Ѿ���szName��ָ�������ԣ���������ΪQF_DOUBLE�������ø����Ե���ֵ������������Ͳ�һ�£��򷵻�false��
    /// ��������Լ�����û��szName��ָ�������ԣ������szName���ڱ����Լ������½�һ�����ԣ�����������ֵ��
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szName�������ֶ����ơ������ֶ����ƽ���ת��Ϊ��д������ͬһ���Լ����б���Ψһ��
	/// \param dValue��Ҫ���õ��ֶ�ֵ��
	/// \param bToBeArchive��ѡ�������Ϊtrue��ʾ��Archive()ʱ�������ֶ�Ӧ�鵵�����ݻ������У�Ϊfalse��ʾ��Archive()ʱ�������ֶν������ԡ�ȱʡΪtrue��
	///
    virtual bool SetDoubleProperty(const char* szName, double dValue, bool bToBeArchive = true) = 0;

    /// \brief ����QF_STRING��������ֵ
    ///
    /// ����QF_STRING��������ֵ��
	/// ��������Լ������Ѿ���szName��ָ�������ԣ���������ΪQF_STRING�������ø����Ե���ֵ������������Ͳ�һ�£��򷵻�false��
    /// ��������Լ�����û��szName��ָ�������ԣ������szName���ڱ����Լ������½�һ�����ԣ�����������ֵ��
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szName�������ֶ����ơ������ֶ����ƽ���ת��Ϊ��д������ͬһ���Լ����б���Ψһ��
	/// \param szValue��Ҫ���õ��ֶ�ֵ��
	/// \param bToBeArchive��ѡ�������Ϊtrue��ʾ��Archive()ʱ�������ֶ�Ӧ�鵵�����ݻ������У�Ϊfalse��ʾ��Archive()ʱ�������ֶν������ԡ�ȱʡΪtrue��
	///
    virtual bool SetStringProperty(const char* szName, const char* szValue, bool bToBeArchive = true) = 0;

	/// \brief ��ֵ����
	///
	/// ���������Լ��ϸ�����ǰ���Լ���
	///
	/// \return ��ǰ���Լ��϶��������
	///
	/// \param right����ֵ�����Ҳ�����
	///
    virtual IQF_PropertySet& operator=(const IQF_PropertySet& right) = 0;

	/// \brief �������
	///
	/// �жϸ������Լ����Ƿ��뵱ǰ���Լ������
	///
	/// \return �����ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right����������Ҳ�����
	///
    virtual int operator==(const IQF_PropertySet& right) = 0;

	/// \brief ���������
	///
	/// �жϸ������Լ����Ƿ��뵱ǰ���Լ��ϲ����
	///
	/// \return �������ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right������������Ҳ�����
	///
    virtual int operator!=(const IQF_PropertySet& right) = 0;


};

//extern "C"
//{
	/// \brief ��������������һ�����Լ��϶���
	/// 
	/// ����һ�����Լ��϶���
	/// 
	/// \return ��������ɹ����򷵻����Լ��϶����ָ�룻���򷵻�NULL
	/// 
	/// \param ��
	///
	/// \note \e ��̬���ӿ⣺common.lib
	///	
	QF_API IQF_PropertySet* QF_CreatePropertySetObject() ;
//}


/// \brief ���Լ��ϵ�����ָ��
/// 
/// ���Լ��ϵ�����ָ�롣��װ�����Լ��϶���Ĵ������ͷţ�������Ϊ�ֲ��Զ�����ʹ��
/// 
class IQF_PropertySetPtr 
{
public :
	///	\brief ���캯��
	///
	/// ���Լ�������ָ��Ĺ��캯��
	///
	/// \param ��
	///
	IQF_PropertySetPtr()
	{
		m_ptr = QF_CreatePropertySetObject() ; 
	}

	///	\brief ��������
	///
	/// ���Լ�������ָ�����������
	///
	~IQF_PropertySetPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief ָ�����������
	///
	/// ���Լ�������ָ���ָ����������ء�
	///
	IQF_PropertySet* operator->() const
	{
		return m_ptr;
	}

	/// \brief ���Լ��϶���
	///
	/// public��Ա�����Լ�������ָ���ʵ�����Լ��϶���
	///
	IQF_PropertySet * m_ptr ;
} ;

QF_END_NAMESPACE
#endif


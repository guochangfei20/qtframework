#ifndef QF_IQF_FIELD_H__
#define QF_IQF_FIELD_H__

#include <qf_config.h>

QF_BEGIN_NAMESPACE(QF)

class IQF_Array;
class IQF_PropertySet;

/// \brief �ֶνӿ�
///
/// �ֶνӿڡ���װ�ɶ��ֶ�Ԫ���ݺ����ݵķ��ʡ�
///
/// \note ͨ��ȫ�ֺ���QF_CreateFieldObject()����һ��IQF_Field����
///
//##ModelId=3F90F98A02E4
class IQF_Field
{
  public:

	/// \brief �ͷ��ֶζ���
	/// 
	/// �ͷ��ֶζ���
	///
	/// \return ��
	///
	/// \param ��
	///
    //##ModelId=3F90F98A02F4
    virtual void Release() = 0;

    /// \brief ��ȡ�ֶ�����
    ///
    /// ��ȡ�ֶ�����
	///
    /// \return �ֶ����ơ�
	///
	/// \param ��
	///
    //##ModelId=3F90F98A02F5
    virtual const char* GetName() = 0;

    /// \brief �����ֶ�����
    ///
    /// �����ֶ����ơ������޸ģ�ֻ�ܳ�ʼ����
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szName���ֶ����ơ�
	///
    virtual bool SetName(const char* szName) = 0;

    /// \brief ��ȡ�ֶ���������
    ///
    /// ��ȡ�ֶ���������
	///
    /// \return �ֶ��������͡�
	///
	/// \param ��
	///
    virtual int GetType() = 0;

    /// \brief �����ֶ�����
    ///
    /// �����ֶ����͡������޸ģ�ֻ�ܳ�ʼ����
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param iType���ֶ����͡�
	///
    virtual bool SetType(int iType) = 0;

    /// \brief ��ȡ�ֶ������ⲿ����
    ///
    /// ��ȡ�ֶ������ⲿ����
	///
    /// \return �ֶ������ⲿ���͡�
	///
	/// \param ��
	///
    virtual int GetExtType() = 0;

    /// \brief �����ֶ������ⲿ����
    ///
    /// �����ֶ������ⲿ���͡�
	///
    /// \return ��
	///
	/// \param iExtType���ֶ������ⲿ���͡�
	///
    virtual void SetExtType(int iExtType) = 0;

    /// \brief ��ȡ�ֶ�����
    ///
    /// ��ȡ�ֶ�����
	///
    /// \return �ֶ����ࡣ
	///
	/// \param ��
	///
    virtual const char* GetStereoType() = 0;

    /// \brief �����ֶ�����
    ///
    /// �����ֶ����ࡣ
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szStereoType���ֶ����ࡣ
	///
    virtual bool SetStereoType(const char* szStereoType) = 0;

    /// \brief ��ȡ�ֶζ��峤��
    ///
    /// ��ȡ�ֶζ��峤�ȡ���ʼ����Ϊ0��
	///
    /// \return �ֶζ��峤�ȡ�
	///
	/// \param ��
	///
    virtual int GetDefLength() = 0;

    /// \brief �����ֶζ��峤��
    ///
    /// �����ֶζ��峤�ȡ������޸ģ�ֻ�ܳ�ʼ����
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param iDefLength���ֶζ��峤�ȡ�
	///
    virtual bool SetDefLength(int iDefLength) = 0;

    /// \brief ��ȡ�ֶα���
    ///
    /// ��ȡ�ֶα���
	///
    /// \return �ֶα��⡣
	///
	/// \param ��
	///
    virtual const char* GetCaption() = 0;

    /// \brief �����ֶα���
    ///
    /// �����ֶα��⡣
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szCaption���ֶα��⡣
	///
    virtual bool SetCaption(const char* szCaption) = 0;

    /// \brief ��ȡ�ֶ�����
    ///
    /// ��ȡ�ֶ�����
	///
    /// \return �ֶ�������
	///
	/// \param ��
	///
    virtual const char* GetDesc() = 0;

    /// \brief �����ֶ�����
    ///
    /// �����ֶ�������
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szDesc���ֶ�������
	///
    virtual bool SetDesc(const char* szDesc) = 0;

    /// \brief �ж��ֶ�ֵ�Ƿ���Ϊ����Ϊ��
	///
	/// �ж��ֶ�ֵ�Ƿ���Ϊ����Ϊ�ա���ʼ����Ϊ����Ϊ�ա�
	///
	/// \return ����ֶ�ֵ���Ϊ����Ϊ�գ��򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsNullable() = 0;

    /// \brief ����ֶ�ֵ�Ƿ����Ϊ��
	///
	/// ����ֶ�ֵ�Ƿ����Ϊ��
	///
	/// \return �����ǳɹ����򷵻�true�����򷵻�false��
	///
	/// \param bNullable��true��ʾҪ���ֶ�ֵ���Ϊ����Ϊ�գ�false��ʾҪ���ֶ�ֵ���Ϊ����Ϊ�ա�ȱʡΪtrue��
	///
    virtual bool SetNullable(bool bNullable = true) = 0;

    /// \brief �ж��ֶ��Ƿ���Ϊ���Ա�ɾ��
	///
	/// �ж��ֶ��Ƿ���Ϊ���Ա�ɾ������ʼ����Ϊ���Ա�ɾ����
	///
	/// \return ����ֶα��Ϊ���Ա�ɾ�����򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsDeletable() = 0;

    /// \brief ����ֶ��Ƿ���Ա�ɾ��
	///
	/// ����ֶ��Ƿ���Ա�ɾ��
	///
	/// \return �����ǳɹ����򷵻�true�����򷵻�false��
	///
	/// \param bDeletable��true��ʾҪ���ֶα��Ϊ���Ա�ɾ����false��ʾҪ���ֶα��Ϊ���ܱ�ɾ����ȱʡΪtrue��
	///
    virtual bool SetDeletable(bool bDeletable = true) = 0;

    /// \brief �ж��ֶ��Ƿ���Ϊ���Ա��޸�
	///
	/// �ж��ֶ��Ƿ���Ϊ���Ա��޸ġ���ʼ����Ϊ���Ա�ɾ����
	///
	/// \return ����ֶα��Ϊ���Ա��޸ģ��򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsUpdatable() = 0;

    /// \brief ����ֶ��Ƿ���Ա��޸�
	///
	/// ����ֶ��Ƿ���Ա��޸�
	///
	/// \return �����ǳɹ����򷵻�true�����򷵻�false��
	///
	/// \param bUpdatable��true��ʾҪ���ֶα��Ϊ���Ա��޸ģ�false��ʾҪ���ֶα��Ϊ���ܱ��޸ġ�ȱʡΪtrue��
	///
    virtual bool SetUpdatable(bool bUpdatable = true) = 0;

    /// \brief �ж��ֶ��Ƿ���Ϊ���Ա�����
	///
	/// �ж��ֶ��Ƿ���Ϊ���Ա���������ʼ����Ϊ���Ա�������
	///
	/// \return ����ֶα��Ϊ���Ա��������򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsIndexable() = 0;

    /// \brief ����ֶ��Ƿ���Ա�����
	///
	/// ����ֶ��Ƿ���Ա�����
	///
	/// \return �����ǳɹ����򷵻�true�����򷵻�false��
	///
	/// \param bIndexable��true��ʾҪ���ֶα��Ϊ���Ա�������false��ʾҪ���ֶα��Ϊ���ܱ�������ȱʡΪtrue��
	///
    virtual bool SetIndexable(bool bIndexable = true) = 0;

    /// \brief �ж��ֶ��Ƿ���Ϊ������
	///
	/// �ж��ֶ��Ƿ���Ϊ����������ʼ����Ϊû�б�������
	///
	/// \return ����ֶα��Ϊ���������򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsIndex() = 0;

    /// \brief ����ֶ��Ƿ�����
	///
	/// ����ֶ��Ƿ�����
	///
	/// \return �����ǳɹ����򷵻�true�����򷵻�false��
	///
	/// \param bIndexable��true��ʾҪ���ֶα��Ϊ��������false��ʾҪ���ֶα��Ϊû�б�������ȱʡΪfalse��
	///
    virtual bool SetToBeIndex(bool bToBeIndex = false) = 0;

    /// \brief ��ȡ�ֶε�ʵ�ʳ��ȣ���λΪ�ֽ�����
	///
	/// ��ȡ�ֶε�ʵ�ʳ��ȣ���λΪ�ֽ�����
	///
	/// \return �ֶε�ʵ�ʳ��ȣ���λΪ�ֽ�����
    /// \li ���ͣ�sizeof(int)
    /// \li �����ͣ�sizeof(char)
    /// \li �����ͣ�sizeof(double)
    /// \li �ַ�����strlen + 1
	///
	/// \param ��
	///
    virtual unsigned int GetLength() = 0;
	
    /// \brief �ж��ֶ�ֵ�Ƿ�Ϊ�ա�
	///
	/// �ж��ֶ�ֵ�Ƿ�Ϊ�ա��κ����͵��ֶξ���ʼ��Ϊ�ա�
	///
	/// \return ����ֶ�ֵΪ�գ��򷵻�true�����򷵻�false��
	///
	/// \param ��
	///
    virtual bool IsNull() = 0;

    /// \brief �����ֶ�ֵ�Ƿ�Ϊ��ֵ
	///
	/// �����ֶ�ֵ�Ƿ�Ϊ��ֵ
	///
	/// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param bIsNull��true��ʾ�����ֶ�ֵΪ��ֵ��false��ʾ�����ֶ�ֵ��Ϊ�ա�ȱʡΪtrue��
	///
    virtual bool SetToNull(bool bIsNull = true) = 0;

    /// \brief ���ַ�������ʽ��ȡ�ֶ�ֵ
	///
	/// ���ַ�������ʽ��ȡ�ֶ�ֵ��
	/// ����QF_INTEGER��QF_DOUBLE���ͣ���ȡ�Ľ��Ϊ�����ַ�����
	/// ����QF_BOOL���ͣ���ȡ�Ľ��Ϊ"TRUE"��"FALSE"��
	/// ����QF_STRING���ͣ���ȡ�Ľ����Ϊ�ֶ�ֵ��
	/// �����������ͣ���ȡ�Ľ��Ϊ�մ�""��������false��
	///
	/// \return �����ȡ�ɹ����򷵻�true�����򷵻�false��
	///
	/// \param szValueString����������������ȡ�ɹ���������Ϊ��ȡ�Ľ������������Ϊ�մ�""��
	/// \param iLength��ָ��szValueString�����ɵ���󳤶ȡ�
	///
    virtual bool GetValueAsString(char* szValueString, int iLength) = 0;

    /// \brief ���ַ�������ʽ�����ֶ�ֵ
	///
	/// ���ַ�������ʽ�����ֶ�ֵ��
	///
	/// \return ������óɹ����򷵻�true�����򷵻�false��
	///
	/// \param szValueString������Ϊ�ַ�����ʽ���ֶ�ֵ
	/// ����QF_INTEGER��QF_DOUBLE���ͣ�Ϊ�����ַ�����
	/// ����QF_BOOL���ͣ�Ϊ"TRUE"��"FALSE"��
	/// ����QF_STRING���ͣ�Ϊ�ֶ�ֵ��
	/// �����������ͣ������壬������false��
	///
    virtual bool SetValueAsString(const char* szValueString) = 0;

    /// \brief ��ȡQF_INTEGER�����ֶ�ֵ
    ///
    /// ��ȡQF_INTEGER�����ֶ�ֵ
	///
    /// \return �����ȡ�ɹ����򷵻���Ӧ��ֵ�����򷵻�INT_MIN������ֶβ�ΪQF_INTEGER���ͣ����ֶ�Ϊ�գ��򷵻�INT_MIN��
	///
	/// \param ��
	///1
    virtual int GetInt() = 0;

    /// \brief ����QF_INTEGER�����ֶ�ֵ
    ///
    /// ����QF_INTEGER�����ֶ�ֵ
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false������ֶβ�ΪQF_INTEGER���ͣ��򷵻�false��
	///
	/// \param iValue��Ҫ���õ��ֶ�ֵ��
	///
    virtual bool SetInt(int iValue) = 0;

    /// \brief ��ȡQF_BOOL�����ֶ�ֵ
    ///
    /// ��ȡQF_BOOL�����ֶ�ֵ
	///
    /// \return �����ȡ�ɹ����򷵻���Ӧ��ֵ�����򷵻�false������ֶβ�ΪQF_BOOL���ͣ����ֶ�Ϊ�գ��򷵻�false��
	///
	/// \param ��
	///
    //##ModelId=4042A7B30017
    virtual bool GetBool() = 0;

    /// \brief ����QF_BOOL�����ֶ�ֵ
    ///
    /// ����QF_BOOL�����ֶ�ֵ
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false������ֶβ�ΪQF_BOOL���ͣ��򷵻�false��
	///
	/// \param bValue��Ҫ���õ��ֶ�ֵ��
	///
    //##ModelId=4042A7B30026
    virtual bool SetBool(bool bValue) = 0;

    /// \brief ��ȡQF_DOUBLE�����ֶ�ֵ
    ///
    /// ��ȡQF_DOUBLE�����ֶ�ֵ
	///
    /// \return �����ȡ�ɹ����򷵻���Ӧ��ֵ�����򷵻�-DBL_MAX������ֶβ�ΪQF_DOUBLE���ͣ����ֶ�Ϊ�գ��򷵻�-DBL_MAX��
	///
	/// \param ��
	///
    //##ModelId=3F90F98A0343
    virtual double GetDouble() = 0;

    /// \brief ����QF_DOUBLE�����ֶ�ֵ
    ///
    /// ����QF_DOUBLE�����ֶ�ֵ
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false������ֶβ�ΪQF_DOUBLE���ͣ��򷵻�false��
	///
	/// \param dValue��Ҫ���õ��ֶ�ֵ��
	///
    //##ModelId=3F90F98A0351
    virtual bool SetDouble(double dValue) = 0;

    /// \brief ��ȡQF_STRING�����ֶ�ֵ
    ///
    /// ��ȡQF_STRING�����ֶ�ֵ
	///
    /// \return �����ȡ�ɹ����򷵻���Ӧ��ֵ�����򷵻ؿ��ַ���""������ֶβ�ΪQF_STRING���ͣ����ֶ�Ϊ�գ��򷵻ؿ��ַ���""��
	///
	/// \param ��
	///
    //##ModelId=3F90F98A0345
    virtual const char* GetString() = 0;

    /// \brief ����QF_STRING�����ֶ�ֵ
    ///
    /// ����QF_STRING�����ֶ�ֵ
	///
    /// \return ������óɹ����򷵻�true�����򷵻�false������ֶβ�ΪQF_STRING���ͣ��򷵻�false��
	///
	/// \param szValue��Ҫ���õ��ֶ�ֵ��
	///
    //##ModelId=3F90F98A0354
    virtual bool SetString(const char* szValue) = 0;

	/// \brief �������
	///
	/// �жϸ����ֶ�Ԫ���ݺ͵���ֵ�Ƿ��뵱ǰ�ֶε�Ԫ���ݺ���ֵ���
	///
	/// \return �����ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right����������Ҳ�����
	///
    //##ModelId=3FA4B93B0154
    virtual int operator==(const IQF_Field& right) = 0;

	/// \brief ���������
	///
	/// �жϸ����ֶ�Ԫ���ݺ͵���ֵ�Ƿ��뵱ǰ�ֶε�Ԫ���ݺ���ֵ�����
	///
	/// \return �������ȣ��򷵻�1�����򣬷���0��
	///
	/// \param right������������Ҳ�����
	///
    //##ModelId=3FA4B93B0210
    virtual int operator!=(const IQF_Field& right) = 0;

	/// \brief ��ֵ����
	///
	/// �������ֶε�Ԫ���ݺ���ֵ������ǰ�ֶ�
	///
	/// \return ��ǰ�ֶζ��������
	///
	/// \param right����ֵ�����Ҳ�����
	///
    //##ModelId=3FA4B93B0079
    virtual IQF_Field& operator=(const IQF_Field& right) = 0;

};

//extern "C"
//{
	/// \brief ��������������һ���ֶζ���
	/// 
	/// ����һ���ֶζ���
	/// 
	/// \return ��������ɹ����򷵻��ֶζ����ָ�룻���򷵻�NULL
	/// 
	/// \param ��
	///
	/// \note \e ��̬���ӿ⣺QF_commontype.lib
	///	
	QF_API IQF_Field* QF_CreateFieldObject() ;
//}

/// \brief �ֶε�����ָ��
/// 
/// �ֶε�����ָ�롣��װ���ֶζ���Ĵ������ͷţ�������Ϊ�ֲ��Զ�����ʹ��
/// 
class IQF_FieldPtr 
{
public :
	///	\brief ���캯��
	///
	/// �ֶ�����ָ��Ĺ��캯��
	///
	/// \param ��
	///
	IQF_FieldPtr()
	{
		m_ptr = QF_CreateFieldObject() ; 
	}

	///	\brief ��������
	///
	/// �ֶ�����ָ�����������
	///
	~IQF_FieldPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief ָ�����������
	///
	/// �ֶ�����ָ���ָ����������ء�
	///
	IQF_Field* operator->() const
	{
		return m_ptr;
	}
	
	/// \brief �ֶζ���
	///
	/// public��Ա���ֶ�����ָ���ʵ���ֶζ���
	///
	IQF_Field* m_ptr ;
	
} ;

QF_END_NAMESPACE
#endif


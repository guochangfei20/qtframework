#ifndef QF_CQF_FIELD_H__
#define QF_CQF_FIELD_H__

#include <qfcommon/IQF_field.h>

QF_BEGIN_NAMESPACE(QF)

// һ��Ԫ�����ֶε���Ϣ��
// ������ΪԪ���ݱ��һ�е�������
// ������Ϊ���Ա��һ�е�������
//##ModelId=3F90F92C018D
class CQF_Field : public IQF_Field
{
  public:
    // ��ȡ�ֶ�����
    //##ModelId=3F90F92C01EA
    const char* GetName();

    // ��ȡ�ֶ����ݿ�����
    //##ModelId=3F90F92C01EB
    int GetType();

    // ��ȡ�ֶ�����
    //##ModelId=3F90F92C01EC
    const char* GetStereoType();

    // ��ȡ�ֶεĳ��ȣ��ֽ�������
    // ���ͣ�4bytes
    // �����ͣ�8bytes
    // ʱ���ͣ�sizeof(SQF_Time) bytes
    // �ַ�����strlen + 1 bytes
    // �����ƣ�4bytes  //ָ��
    // ��������4bytes  //ָ��
    // ���飺4bytes  //ָ��
    //##ModelId=3F90F92C01ED
    unsigned int GetLength();

    // �ж��ֶ�ֵ�Ƿ����Ϊ��
    //##ModelId=3F90F92C01F8
    bool IsNullable();



    // ��ȡ�ֶα���
    //##ModelId=3F90F92C01FB
    const char* GetCaption();

    // ��ȡ�ֶ�����
    //##ModelId=3F90F92C01FC
    const char* GetDesc();


    // �����ֶ����ơ�
    // 
    // ��˵����
    // �ֶ����Ʋ����޸ģ�ֻ�ܳ�ʼ��
    //##ModelId=3F90F92C01FE
    bool SetName(const char* szName);

    // �����ֶ����͡�
    // 
    // ��˵����
    // �ֶ����Ͳ����޸ģ�ֻ�ܳ�ʼ��
    //##ModelId=3F90F92C0208
    bool SetType(int type);

    // �����ֶ����ࡣ
    // 
    // ��˵����
    // �ֶ����಻���޸ģ�ֻ�ܳ�ʼ��
    //##ModelId=3F90F92C020A
    bool SetStereoType(const char* szStereoType);

    // �����ֶ�ֵ�Ƿ��ܹ�Ϊ�ա�
    // 
    // ��˵����
    // �����޸ģ�ֻ�ܳ�ʼ��
    //##ModelId=3F90F92C020E
    bool SetNullable(bool bNullable = true);

    // �����ֶα��⡣
    // 
    // ��˵����
    // �ֶα�������޸�
    //##ModelId=3F90F92C021A
    bool SetCaption(const char* szCaption);

    // �����ֶ�������
    // 
    // ��˵����
    // �ֶ����������޸ġ�
    // ���ڱ��ʽ���䶨���Ƿ������޸ģ�
    //##ModelId=3F90F92C021C
    bool SetDesc(const char* szDesc);

    // ��ȡ�ֶε�����ֵ��
    // �����ֵ��δ�����ã��򷵻�0 ��
    //##ModelId=3F90F92C0228
    int GetInt();

    // ��ȡ�ֶεĸ�����ֵ��
    // �����ֵ��δ�����ã��򷵻�0 ��
    //##ModelId=3F90F92C0229
    double GetDouble();

    // ��ȡ�ֶε��ַ���ֵ��
    // �����ֵ��δ�����ã��򷵻ؿ��ַ���""��
    //##ModelId=3F90F92C022A
    const char* GetString();

    // ���ַ�������ʽ��ȡ�ֶ�ֵ��
    //##ModelId=3F90F92C022B
    bool GetValueAsString(char* szValueString,int iLength);

    // �����ֶε�����ֵ��
    //##ModelId=3F90F92C022D
    bool SetInt(int iValue);

    // �����ֶεĸ�����ֵ��
    //##ModelId=3F90F92C0237
    bool SetDouble(double dValue);

    // �����ֶε��ַ���ֵ��
    //##ModelId=3F90F92C0239
    bool SetString(const char* szValue);

    // ���ַ�������ʽ�����ֶ�ֵ��
    //##ModelId=3F90F92C023B
    bool SetValueAsString(const char* szValueString);

    // �ж��ֶ�ֵ�Ƿ�Ϊ�ա�
    //##ModelId=3F90F92C023D
    bool IsNull();

    // ���ֶ�ֵ��Ϊ��ֵ��
    //##ModelId=3F90F92C023E
    bool SetToNull(bool bIsNull = true);

    //##ModelId=3F90FD54013B
    CQF_Field();

    //##ModelId=3F90FD590199
    ~CQF_Field();

    //##ModelId=3F910CAD00FD
    void Release();

    //##ModelId=3F9CF4D6007D
 //   bool Archive(IQF_DataBuffer* pDataBuffer, int iMode, int iType);

    // ��ȡ�ֶ����ݵ��ⲿ���͡�
    //##ModelId=3F9E33E0028F
    int GetExtType();

    // �����ֶ��ⲿ���͡�
    //##ModelId=3F9E33E002AE
    void SetExtType(int ExtType);

    //##ModelId=3FA4B94603E5
    IQF_Field& operator=(const IQF_Field& right);

    //##ModelId=3FA4B94700A9
    int operator==(const IQF_Field& right);

    //##ModelId=3FA4B9470154
    int operator!=(const IQF_Field& right);

    // ������������������.
    //##ModelId=3FA4B9CB02B0
    void Clear();

    // ��ʼ��.
    //##ModelId=3FA4BA0B0070
    void Init();

    // ��ȡ�ֶε�����ӿ�ָ�롣
    // �����ֵ��δ�����ã��򷵻ؿա�
    //##ModelId=3FA8EC2F0297
//    IQF_Array* GetArray();

    // ��ȡ�ֶε����Լ��Ͻӿ�ָ�롣
    // �����ֵ��δ�����ã��򷵻ؿա�
    //##ModelId=3FA8EC2F02F4
//    IQF_PropertySet* GetPropertySet();

    // ��ȡ�ֶεĶ��������ݽӿ�ָ�롣
    // �����ֵ��δ�����ã��򷵻ؿա�
    //##ModelId=3FACC22A01C8
//    IQF_DataBuffer* GetBinary();
    
	//##ModelId=4035D1E80251
//    bool ArchiveField(IQF_DataBuffer* pDataBuffer, int iMode, int iType);
    
	//##ModelId=4042A6800396
//    bool IsToBeArchive();

    //##ModelId=4042A69E02FB
//    bool SetToBeArchive(bool bToBeArchive = true);

    //##ModelId=4042A6D103E7
    bool GetBool();

    //##ModelId=4042A6E40119
    bool SetBool(bool bValue);

    //##ModelId=405AB05A014D
    bool IsDeletable();

    //##ModelId=405AB0A20381
    bool IsUpdatable();

    //##ModelId=405AB0740341
    bool IsIndexable();

    //##ModelId=405AB08E02F4
    bool IsIndex();

    //##ModelId=405AB1040076
    bool SetDeletable(bool bDeletable = true);

    //##ModelId=405AB17902DB
    bool SetUpdatable(bool bUpdatable = true);

    //##ModelId=405AB119023C
    bool SetIndexable(bool bIndexable = true);

    //##ModelId=405AB18F00A9
    bool SetToBeIndex(bool bToBeIndex = false);

    //##ModelId=40721588036B
//    SQF_Time GetTime();

    //##ModelId=4072159A008D
//    bool SetTime(SQF_Time sTime);

    // �����ֶζ��峤�ȡ�ֻ�ܳ�ʼ���������޸ġ�
    //##ModelId=40BC28F30316
    bool SetDefLength(int iDefLength);

    // ��ȡ�ֶζ��峤�ȡ�δ����ʱΪ0��ȱʡֵ����
    //##ModelId=40BC28F30318
    int GetDefLength();

    //##ModelId=40C9A8EC0336
 //   const char* GetReferencedString(int* piType, int* piSubType);

    //##ModelId=40C9A91F027B
  //  bool SetReferencedString(int iType, int iSubType, const char* szPath);

  private:
    // �ֶ�����
    //##ModelId=3F90F92C019A
    char* m_szName;

    // �ֶ��������͡�
    //##ModelId=3F90F92C01AA
    int m_iType;

    // �ֶ����࣬���ֶα��ָ��û����߼����͡�
    // 
    // 8bits����
    // 0�������������ͣ�����������ͬ���ݿ��е��������ͣ�����ʵ����ֱ�Ӵ������Ӧ�����У�
    // 1����ý�����ͣ�����������Ϊint��ֵΪ��ý�����mid������ʵ���ݴ���ڶ�ý����У�
    // 2�����ʽ���ͣ�����������Ϊstring��ֵΪNULL������ʵ�����ɱ��ʽ������ã����ʽ�������ֶ�����������
    // 3-7Ԥ����
    //##ModelId=3F90F92C01BA
    char* m_szStereoType;

/*
    // �ֶεĶ������󳤶ȣ��ֽ�������
    // 
    // �����ַ����Ͷ���������Ч��
    // 
    // ���ͣ�4bytes
    // �����ͣ�8bytes
    // ʱ���ͣ�20bytes
    // �ַ�����n bytes
    // �����ƣ�m bytes  //longraw��binary
    // ���ֶΣ�4bytes  //ָ��
    //##ModelId=3F90F92C01BB
    unsigned int m_uiLength;
*/




    // �ֶα���
    //##ModelId=3F90F92C01D9
    char* m_szCaption;

    // �ֶ�������Ϣ��
    // ���ڱ��ʽ���ͣ��������Ǳ��ʽ�Ķ��塣
    //##ModelId=3F90F92C01DA
    char* m_szDesc;


    //##ModelId=3F90F92C01E9
    void* m_pValue;
    // �ֶ��ⲿ�������͡�
    //##ModelId=3F9E340A0231
    int m_iExtType;
    // ��������bool�ͱ�־��
    // 0x 0000 0001: �Ƿ��ܹ�Ϊ��
    // 0x 0000 0002: �Ƿ�Ϊ��
    // 0x 0000 0004: �Ƿ��ܹ���Ϊ����
    // 0x 0000 0008: �Ƿ���Ϊ����
    // 0x 0000 0010: �Ƿ��ܹ����޸�
    // 0x 0000 0020: �Ƿ��ܹ���ɾ��
    // 0x 0000 0040: �Ƿ���Ҫ��Achive
    //##ModelId=405AAF180076
    int m_iFlags;
    // �ֶεĶ������󳤶ȣ��ֽ�������
    // 
    // �����ַ����Ͷ���������Ч��
    // 
    // ���ͣ�4bytes
    // �����ͣ�8bytes
    // ʱ���ͣ�20bytes
    // �ַ�����n bytes
    // �����ƣ�m bytes  //longraw��binary
    // ���ֶΣ�4bytes  //ָ��
    //##ModelId=3F90F92C01BB
    unsigned int m_uiLength;

};

QF_END_NAMESPACE
#endif


#ifndef iconfig_h__
#define iconfig_h__

//
#ifndef  BUILD_INTERFACE
#define BUILD_INTERFACE(INTERFACE_NAME) \
public:     \
    virtual ~##INTERFACE_NAME(){}       //��ֹ�ڽӿ����û�ͨ��deleteɾ���ӿ�ָ�뵼��ʵ������������δ���õ����⣬������ͨ��IQF_Object��release()�ӿڽ��
#endif
#endif // iconfig_h__
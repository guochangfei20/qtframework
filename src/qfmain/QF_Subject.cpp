#include "QF_Subject.h"
#include "IQF_Observer.h"

#include <assert.h>
QF_BEGIN_NAMESPACE(QF)

IQF_Subject* QF_CreateSubjectObject()
{
    IQF_Subject* psubject = new CQF_Subject;
    return psubject;
}

void QF_ReleaseSubjectObject(IQF_Subject *pSubject)
{
    if (pSubject)
        delete (CQF_Subject*)pSubject;
}


CQF_Subject::CQF_Subject()
{
}


CQF_Subject::~CQF_Subject()
{
    DetachAll();
}


void CQF_Subject::Release()
{
    delete this;
}

void CQF_Subject::Attach(IQF_Observer* pObserver, const char* szMessage)
{
    bool is_broadcast = false;

    is_broadcast = (strcmp(szMessage,"")==0);
    if (is_broadcast)
    {
        // ���뵽�㲥�б���
        if (!HasObserver(pObserver, &m_BroadcastObservers))
        {
            //m_BroadcastObservers.push_back(pObserver) ;
            SQF_ObserverItem item;
            item.pObserver = pObserver;
            item.CheckValue = *((int*)pObserver);
            item.IsValid = true;

            m_BroadcastObservers.push_back(item);
        }
    }
    else
    {
        // ���뵽ָ����Ϣ����Ӧ��Observer�б���

        // �����Observer�Ѿ��ڹ㲥�б���,�����ټ��뵽�ض�Message���б���
        if (HasObserver(pObserver, &m_BroadcastObservers))
            return;

        // ���Ȳ���sz_message����Ӧ��Observer�б�
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.find(szMessage);

        CQF_ObserverList* p_observer_list = 0;

        // ����Ҳ���,����һ���µ�Observer�б�,�����뵽Map��
        if (iterator == m_MsgObserverMap.end())
        {
            p_observer_list = new CQF_ObserverList;

            // ������Ϣ�ַ���
            /*	char* sz_message = new char [strlen(szMessage) + 1] ;
            assert(sz_message) ;

            strcpy(sz_message, szMessage) ;

            m_MsgObserverMap[sz_message] = p_observer_list ;
            */
            m_MsgObserverMap[szMessage] = p_observer_list;
        }
        else
            p_observer_list = (*iterator).second;

        assert(p_observer_list);

        // ��ָ����Observer������뵽��Ӧ��Observer�б���
        if (p_observer_list)
        {
            if (!HasObserver(pObserver, p_observer_list))
            {
                SQF_ObserverItem item;
                item.pObserver = pObserver;
                item.CheckValue = *((int*)pObserver);
                item.IsValid = true;
                p_observer_list->push_back(item);
            }
        }

    }
}


void CQF_Subject::Detach(IQF_Observer* pObserver, const char* szMessage)
{
#ifndef _DEBUG
    try
    {
#endif	
        // ���szMessageΪ��ָ�����ַ�������ʾ���ټ���������Ϣ������������б���ȥ��
        bool is_removeall = false;
        /*
        if (szMessage == NULL)
        is_removeall = true ;
        else if (strlen(szMessage) == 0)
        is_removeall = true ;
        else
        is_removeall = false ;
        */
        is_removeall = (strcmp(szMessage, "") == 0);

        CQF_MsgObserverMap::iterator iterator;
        CQF_ObserverList::iterator observer_iterator;

        // ������ټ���ָ����Ϣ���������ҵ�����Ϣ��Ӧ��Observer�б�Ȼ����н���ɾ��
        if (!is_removeall)
        {
            iterator = m_MsgObserverMap.find(szMessage);

            // ����ҵ�,����н�ָ��Observerɾ��
            if (iterator != m_MsgObserverMap.end())
            {
                CQF_ObserverList* p_observer_list = (*iterator).second;
                assert(p_observer_list);

                if (p_observer_list)
                {
                    //p_observer_list->remove(pObserver) ;
                    observer_iterator = p_observer_list->begin();
                    while (observer_iterator != p_observer_list->end())
                    {
                        if ((*observer_iterator).pObserver == pObserver)
                            break;
                        else
                            observer_iterator++;
                    }

                    if (observer_iterator != p_observer_list->end())
                    {
                        //					if (!m_IsBeingNotify)
                        if (m_NotifyLevel == 0)
                            p_observer_list->erase(observer_iterator);
                        else
                        {
                            SQF_ObserverItem item = *observer_iterator;
                            item.IsValid = false;
                            *observer_iterator = item;
                        }
                    }
                }
            }

        }
        else
        {
            // ������ټ���������Ϣ����������б��н�ָ��Observerɾ��

            // ����ɾ���㲥�б�
            //m_BroadcastObservers.remove(pObserver) ;
            observer_iterator = m_BroadcastObservers.begin();
            while (observer_iterator != m_BroadcastObservers.end())
            {
                if ((*observer_iterator).pObserver == pObserver)
                    break;
                else
                    observer_iterator++;
            }

            if (observer_iterator != m_BroadcastObservers.end())
            {
                //			if (!m_IsBeingNotify)
                if (m_NotifyLevel == 0)
                    m_BroadcastObservers.erase(observer_iterator);
                else
                {
                    SQF_ObserverItem item = *observer_iterator;
                    item.IsValid = false;
                    *observer_iterator = item;
                }
            }


            // Ȼ��ɾ��������Ϣ�����б�
            iterator = m_MsgObserverMap.begin();
            while (iterator != m_MsgObserverMap.end())
            {
                CQF_ObserverList* p_observer_list = (*iterator).second;
                assert(p_observer_list);

                if (p_observer_list)
                {
                    //p_observer_list->remove(pObserver) ;
                    observer_iterator = p_observer_list->begin();
                    while (observer_iterator != p_observer_list->end())
                    {
                        if ((*observer_iterator).pObserver == pObserver)
                            break;
                        else
                            observer_iterator++;
                    }

                    if (observer_iterator != p_observer_list->end())
                    {
                        //					if (!m_IsBeingNotify)
                        if (m_NotifyLevel == 0)
                            p_observer_list->erase(observer_iterator);
                        else
                        {
                            SQF_ObserverItem item = *observer_iterator;
                            item.IsValid = false;
                            *observer_iterator = item;
                        }
                    }
                }

                iterator++;
            }
        }

#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}
void CQF_Subject::DetachAll()
{
#ifndef _DEBUG
    try
    {
#endif	
        // ��������㲥��Ϣ�б�
        m_BroadcastObservers.clear();

        // Ȼ�����������Ϣ�б�
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.begin();
        while (iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observer_list = (*iterator).second;
            assert(p_observer_list);

            //	char* sz_message = (char*)((*iterator).first) ;
            //	assert(sz_message);

            iterator++;

            if (p_observer_list)
            {
                p_observer_list->clear();
                delete p_observer_list;
            }

            //	if (sz_message)
            //		delete[] sz_message ;

        }

        m_MsgObserverMap.clear();

#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}

void CQF_Subject::Notify(const char* szMessage, int iValue, void* pValue)
{
#ifndef _DEBUG
    try
    {
#endif	

        //	m_IsBeingNotify = true ;
        m_NotifyLevel++;

        // ������㲥�����е�Observer������Ϣ
        CQF_ObserverList::iterator observer_iterator;

        observer_iterator = m_BroadcastObservers.begin();
        while (observer_iterator != m_BroadcastObservers.end())
        {
            //IGIS_Observer* pobserver = *observer_iterator ;
            SQF_ObserverItem item = *observer_iterator;

            //pobserver->Update(szMessage, iValue, pValue) ;

            if (item.pObserver)
            {
                if (item.IsValid)
                {
                    if (item.CheckValue == *((int*)item.pObserver))
                    {
#ifndef _DEBUG
                        try
                        {
#endif	
                            item.pObserver->Update(szMessage, iValue, pValue);
#ifndef _DEBUG
                        }
                        catch (...)
                        {
                            std::cerr << "Error when execute message " << szMessage;
                        }
#endif	
                    }
                    else
                    {
                        item.IsValid = false;
                        *observer_iterator = item;
                    }
                }
            }

            observer_iterator++;

        }

        // Ȼ����ָ����Ϣ�����е�Observer������Ϣ
        CQF_MsgObserverMap::iterator list_iterator = m_MsgObserverMap.find(szMessage);
        if (list_iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observerlist = (*list_iterator).second;
            assert(p_observerlist);

            if (p_observerlist)
            {
                observer_iterator = p_observerlist->begin();
                while (observer_iterator != p_observerlist->end())
                {
                    //IGIS_Observer* pobserver = *observer_iterator ;
                    //if (pobserver)
                    //	pobserver->Update(szMessage, iValue, pValue) ;

                    SQF_ObserverItem item = *observer_iterator;

                    if (item.pObserver)
                    {
                        if (item.IsValid)
                        {
                            if (item.CheckValue == *((int*)item.pObserver))
                            {
#ifndef _DEBUG
                                try
                                {
#endif	
                                    item.pObserver->Update(szMessage, iValue, pValue);
#ifndef _DEBUG
                                }
                                catch (...)
                                {
                                    std::cerr << "Error when execute message " << szMessage;
                                }
#endif	
                            }
                            else
                            {
                                assert(false && strcmp("Pointer to Observer is invalid, maybe is been deleted!", 0));
                                item.IsValid = false;
                                *observer_iterator = item;
                            }
                        }
                    } //if (item.pObserver)

                    observer_iterator++;

                } // while (observer_iterator != p_observerlist->end ())
            }
        }

        //	m_IsBeingNotify = false ;
        m_NotifyLevel--;
        if (m_NotifyLevel < 0)
            m_NotifyLevel = 0;

        // ���������Notify�����У���Detach��������Ϊ��Ч��Observer

        // ��������㲥��Ϣ�б��е���ЧObserver
        observer_iterator = m_BroadcastObservers.begin();
        while (observer_iterator != m_BroadcastObservers.end())
        {
            SQF_ObserverItem item = *observer_iterator;

            CQF_ObserverList::iterator observer_iterator_tobe_delete = observer_iterator;

            observer_iterator++;

            if (!item.IsValid)
                m_BroadcastObservers.erase(observer_iterator_tobe_delete);
        }

        // Ȼ�����������Ϣ�б��е���ЧObserver
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.begin();
        while (iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observer_list = (*iterator).second;
            assert(p_observer_list);

            iterator++;

            if (p_observer_list)
            {
                observer_iterator = p_observer_list->begin();
                while (observer_iterator != p_observer_list->end())
                {
                    SQF_ObserverItem item = *observer_iterator;

                    CQF_ObserverList::iterator observer_iterator_tobe_delete = observer_iterator;

                    observer_iterator++;

                    if (!item.IsValid)
                        p_observer_list->erase(observer_iterator_tobe_delete);

                }
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}

bool CQF_Subject::HasObserver(IQF_Observer* pObserver, CQF_ObserverList* pObserverList)
{
    CQF_ObserverList::iterator observer_iterator;

    // ���Ϊ�գ��򷵻�false
    if (pObserverList->size() == 0)
        return false;

    // ������ѯָ����Observer
    observer_iterator = pObserverList->begin();
    while (observer_iterator != pObserverList->end())
    {
        // �Ƚ���ǰָ��ǰ�ƣ��ٷ�����Ϣ��
        // �Ӷ�ʹ�۲�Ҷ����ܹ�����Ϣ����������뱾���۲�����ѹ�
        SQF_ObserverItem item = *observer_iterator;
        observer_iterator++;

        //if (observer == pObserver)
        if (item.pObserver == pObserver)
            return true;
    }

    return false;
}

QF_END_NAMESPACE
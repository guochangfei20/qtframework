#include "CQF_Properties.h"
#include "IQF_Property.h"

QF_BEGIN_NAMESPACE(QF)


IQF_Properties* QF_CreateProperties()
{
    return new CQF_Properties();
}

CQF_Properties::CQF_Properties()
{
}


CQF_Properties::~CQF_Properties()
{
    Clear();
}

void CQF_Properties::Release()
{
    delete this;
}

void CQF_Properties::Clear()
{
    for (ProperteisMapType::iterator it = m_properties.begin(); it != m_properties.end(); )
    {
        it->second->Release();
        it->second = NULL;
        m_properties.erase(it++);
    }
}

int CQF_Properties::GetCount()
{
    return m_properties.size();
}

IQF_Property* CQF_Properties::GetProperty(const char* szName)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it!=m_properties.end())
    {
        return m_properties[szName];
    }
    else
    {
        return NULL;
    }
}

bool CQF_Properties::HasProperty(const char* szName)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CQF_Properties::AddProperty(const char* szName, IQF_Property* pProperty)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        return false;
    }
    else
    {
        m_properties[szName] = pProperty;
        return true;
    }
    
}

IQF_Property* CQF_Properties::AddProperty(const char* szName, int iType)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        return m_properties[szName];
    }
    else
    {
        IQF_Property* newProperty = QF_CreateProperty();
        newProperty->SetType(iType);
        m_properties[szName] = newProperty;
        return newProperty;
    }
    
}

IQF_Property* CQF_Properties::GetFirstProperty()
{
    m_propertiesIterator = m_properties.begin();
    if (m_propertiesIterator !=m_properties.end())
    {
        return m_propertiesIterator->second;
    }
    else
    {
        return NULL;
    }
}

IQF_Property* CQF_Properties::GetNextProperty(IQF_Property* pCurrentProperty)
{
    m_propertiesIterator++;
    if (m_propertiesIterator != m_properties.end())
    {
        return m_propertiesIterator->second;
    }
    else
    {
        return NULL;
    }
}

bool CQF_Properties::DeleteProperty(const char* szName)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        it->second->Release();
        it->second = NULL;
        m_properties.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

bool CQF_Properties::SetIntProperty(const char* szName, int iValue)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        if (it->second->GetType()==QF_DataType_Integer)
        {
            it->second->SetInt(iValue); 
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        IQF_Property* newProperty = QF_CreateProperty();
        newProperty->SetType(QF_DataType_Integer);
        newProperty->SetInt(iValue);
        m_properties[szName] = newProperty;
        return true;
    }
}

bool CQF_Properties::SetBoolProperty(const char* szName, bool bValue)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        if (it->second->GetType() == QF_DataType_Bool)
        {
            it->second->SetBool(bValue);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        IQF_Property* newProperty = QF_CreateProperty();
        newProperty->SetType(QF_DataType_Bool);
        newProperty->SetBool(bValue);
        m_properties[szName] = newProperty;
        return true;
    }
}

bool CQF_Properties::SetDoubleProperty(const char* szName, bool dValue)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        if (it->second->GetType() == QF_DataType_Double)
        {
            it->second->SetDouble(dValue);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        IQF_Property* newProperty = QF_CreateProperty();
        newProperty->SetType(QF_DataType_Double);
        newProperty->SetDouble(dValue);
        m_properties[szName] = newProperty;
        return true;
    }
}

bool CQF_Properties::SetStringProperty(const char* szName, const char* szValue)
{
    ProperteisMapType::iterator it = m_properties.find(szName);
    if (it != m_properties.end())
    {
        if (it->second->GetType() == QF_DataType_String)
        {
            it->second->SetString(szValue);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        IQF_Property* newProperty = QF_CreateProperty();
        newProperty->SetType(QF_DataType_String);
        newProperty->SetString(szValue);
        m_properties[szName] = newProperty;
        return true;
    }
}

QF_END_NAMESPACE
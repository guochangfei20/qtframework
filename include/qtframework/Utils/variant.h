/*!
 * \file variant.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef VARIANT_H
#define VARIANT_H

#pragma once
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include "Common/qtframework_com.h"
using namespace std;

class QTFRAMEWORK_EXPORT variant;

template<typename T> inline T variant_cast(const variant&);
typedef std::map<std::string, variant> VarientMap;
/*!
 * \class variant
 *
 * \brief 
 *  ����QVariant��һ���������ı�����,��ǰ��Ҫ����config�ļ���������Ϣ�Ĵ洢
 *  ��ʱֻ֧��int��bool��string��double��ָ�����ͱ���������
 *  variant v(3.14);
 *  double val = v.value<double>();����double val = v.getDouble();
 *
 * \author ����
 * \date ���� 2016
 */
class variant{
public:
	//��������
	enum Type{
		Int,
		Bool,
		String,
		Double,
		Ptr,
		UnKnown
	};
	//���캯��
	//��������
	//����ֵ����
	variant();
	//���캯��
	//������
	//	val: int������ֵ
	//����ֵ����
	variant(int val)
	{
		setInt(val);
	}
	//���캯��
	//������
	//	val: bool������ֵ
	//����ֵ����
	variant(bool val)
	{
		setBool(val);
	}
	//���캯��
	//������
	//	val: �ַ�������ֵ
	//����ֵ����
	variant(const char* val)
	{
		setString(val);
	}
	//���캯��
	//������
	//	val: double������ֵ
	//����ֵ����
	variant(double val)
	{
		setDouble(val);
	}
	//���캯��
	//������
	//	val: ָ��������ֵ
	//����ֵ����
	variant(void* val)
	{
		setPtr(val);
	}
	//��������
	//��������
	//����ֵ����
	~variant();
	//��ñ�������
	//��������
	//����ֵ����������
	Type getType() const
	{
		return _type;
	}
	//���ñ�������
	//������
	//	type: ��������
	//����ֵ����
	void setType(Type type){_type = type;}
	//���ñ���ֵ
	//������
	//	val: int�ͱ���
	//����ֵ����
	void setInt(int val)
	{
		_data.iValue=val;
		char temp[50];
		sprintf(temp,"%d",val);
		_content = temp;
		_type=Int;
	}
	//���ñ���ֵ
	//������
	//	val: bool�ͱ���
	//����ֵ����
	void setBool(bool val)
	{
		_data.bValue=val;
		if (val)
		{
			_content = "true";
		}else
		{
			_content = "false";
		}
		_type = Bool;
	}
	//���ñ���ֵ
	//������
	//	val: �ַ��ͱ���
	//����ֵ����
	void setString(const char* val)
	{
		_sdata = val;
		_content = _sdata;
		_type = String;
	}
	//���ñ���ֵ
	//������
	//	val: double�ͱ���
	//����ֵ����
	void setDouble(double val)
	{
		_data.dValue=val;
		char temp[50];
		sprintf(temp,"%lf",val);
		_content = temp;
		_type = Double;
	}
	//���ñ���ֵ
	//������
	//	val: ָ���ͱ���
	//����ֵ����
	void setPtr(void* val)
	{
		_data.pValue=val;
		_type = Ptr;
	}
	//��ñ���ֵ
	//��������
	//����ֵ��int�ͱ���ֵ
	int getInt() const
	{
		if (_type==Int)
		{
			return _data.iValue;
		}
		else
			return -1111111;
	}
	//��ñ���ֵ
	//��������
	//����ֵ��bool�ͱ���ֵ
	bool getBool() const
	{
		if (_type==Bool)
		{
			return _data.bValue;
		}
		else
			return false;
	}
	//��ñ���ֵ
	//��������
	//����ֵ��double�ͱ���ֵ
	double getDouble() const
	{
		if (_type==Double)
		{
			return _data.dValue;
		}
		else
			return -11111111;
	}
	//��ñ���ֵ
	//��������
	//����ֵ���ַ��ͱ���ֵ
	const char* getString() const
	{
		if (_type==String)
		{
			return _sdata.c_str();
		}
		else
			return "";
	}
	//��ñ�������
	//��������
	//����ֵ����������
	const char* getContent() const
	{
		return _content.c_str();
	}
	//���ñ�������
	//������
	//		conten����������
	//����ֵ����
	void setContent(const char* content)
	{
		_content = content;
	}
	//��ñ���ֵ
	//��������
	//����ֵ��ָ���ͱ���ֵ
	void* getPtr() const
	{
		if (_type==Ptr)
		{
			return _data.pValue;
		}
		else
			return NULL;
	}
	//����ģ�����
	//C++Ҫ��ģ�庯����������ʵ�ֶ������߱��붼�ɼ���������Ҫ����ͬһ���ļ�������߰���ʵ�ֵ��ļ�
    template<typename T> T value() const
    {
        return variant_cast<T>(*this);
    }
    inline static variant& GetVariant(VarientMap& map, const char* id)
    {
        VarientMap::iterator it = map.find(id);
        if (it != map.end())
        {
            return it->second;
        }
        else
        {
            return variant(NULL);
        }
    }
private:
    friend inline bool variant_cast_helper(const variant&, variant::Type, void *);
	union{
		int iValue;
		bool bValue;
		double dValue;
		void* pValue;
	}_data;
	string _sdata;
	string _content;
	Type _type;
};


inline bool variant_cast_helper(const variant &v, variant::Type tp, void *ptr)  //����ת��
{	
	if (tp==variant::Int)
	{
		int* pInt = (int*)ptr;
		*pInt = v._data.iValue;
		return true;
	}
	else if (tp==variant::Double)
	{
		double* pDouble = (double*)ptr;
		*pDouble = v._data.dValue;
		return true;
	}
	else if (tp==variant::Bool)
	{
		bool* pBool = (bool*)ptr;
		*pBool = v._data.bValue;
		return true;
	}
	else if (tp==variant::String)
	{
		char** pChar = (char**)ptr;
		*pChar = (char*)v._sdata.c_str();
		return true;
	}
	else if (tp==variant::Ptr)
	{
		void** pValue = (void**)ptr;
		*pValue = (char*)v._data.pValue;
		return true;
	}
	else
		return false;
}

template<typename T> T variant_cast(const variant &v)
{
	variant::Type type = v.getType();	 //const����ָ��ֻ�ܵ���const���ͺ���
	if (type < (int)variant::UnKnown)    //����Ǵ��ڵ����;�ת��������
	{
		T t ;
		if (variant_cast_helper(v,type,&t))
			return t;
	}
	return T();
}

#endif
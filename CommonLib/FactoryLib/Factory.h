#pragma once
#include <map>
#include <string>
using std::map;
using std::string;

#define IMPLEMENT_FACTORYCLASS(CLASS) static const bool NoUser##CLASS=CFactoryObject::Register(#CLASS, (CFactoryObject* (*)())&CLASS::createInstance);
#define DECLARE_FACTORYCLASS(CLASS) static CLASS *createInstance() { return new CLASS; }
class CFactoryObject;
typedef CFactoryObject* (*Func)();


class __declspec(dllexport) CFactoryObject
{
	typedef map<string,Func> MapFunction; 
public:
	CFactoryObject();
	virtual ~CFactoryObject();
	void RelaseInstance();
	static CFactoryObject* GetInstance(const char* chClassName);
	static bool Register(const char* chClassName,Func pFunc);
	static MapFunction * m_MapFunc;
};
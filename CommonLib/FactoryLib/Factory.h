#pragma once
#include <map>
#include <string>
using std::map;
using std::string;

#define IMPLEMENT_FACTORYCLASS(CLASS) static const bool NoUser##CLASS=CFactoryObject::Register(#CLASS, (CFactoryObject* (*)())&CLASS::createInstance);
#define DECLARE_FACTORYCLASS(CLASS) static CLASS *createInstance() { return new CLASS; }
class CFactoryObject;
typedef CFactoryObject* (*Func)();
static map<string,Func> g_MapFunc;

class __declspec(dllexport) CFactoryObject
{
public:
	CFactoryObject();
	virtual ~CFactoryObject();
	static CFactoryObject* GetInstance(const char* chClassName);
	static bool Register(const char* chClassName,Func pFunc);
};
#pragma once
#include "AutoLock.h"
#include "DataObject.h"
#include <hash_map>
using std::pair;
using std::hash_map;
class __declspec(dllexport) CDataObjectManager
{
private:
	const static int begin=99;
	const static int end=0;
	class _declspec(dllexport) CInternal
	{
	public:
		CInternal();
		~CInternal();
	};
private:
	CDataObjectManager();
	~CDataObjectManager();
	static void RelaseInstance();
public:
	static CDataObjectManager* GetInstance();
	unsigned long Add(CDataObject* pObj);
	void Remove(unsigned long ulObjId);
	CDataObject* GetDataObject(unsigned long ulObjId);
private:
	static CDataObjectManager* m_pDataObjectManger;
	static CInternal m_Internal;
	hash_map<unsigned long,CDataObject*>* m_pMapDataObj;
	CAutoLock::CLock m_lock;
	unsigned long m_ulCurrId;
};


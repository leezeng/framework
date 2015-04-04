#pragma once
template<class T>
class CQueue;

template<class T>
class __declspec(dllexport) CNode
{
private:
	T m_t;
	CNode<T>* m_pNext;
public:
	CNode();
	CNode(T t);
	~CNode();
	template<class T>
	friend class CQueue;
};

template<class T>
CNode<T>::~CNode()
{
	m_pNext=nullptr;
}

template<class T>
class __declspec(dllexport) CQueue
{
public:
	CQueue(void); 
	~CQueue(void);
	bool isEmpty();
	bool enqueue(T t);
	bool dequeue(T& t);
	int length();
	void clear();
private:
	CNode<T>* m_pTail;//Œ≤÷∏’Î
	CNode<T>* m_pHead;//Õ∑÷∏’Î
	//int m_nMaxSize;
};

template<class T>
int CQueue<T>::length()
{
	int nLength=0;
	CNode<T>* p=m_pHead;
	while(p!=m_pTail)
	{
		p=p->m_pNext;
		nLength++;
	}
	return nLength;
}

template<class T>
void CQueue<T>::clear()
{
	CNode<T>* p=m_pHead;
	CNode<T>* pTemp=nullptr;
	while(p!=m_pTail)
	{
		pTemp=p;
		p=pTemp->m_pNext;
		delete pTemp;
		pTemp=nullptr;
	}
	m_pTail=m_pHead;
}



template<class T>
CQueue<T>::CQueue( void ):m_pTail(nullptr),m_pHead(nullptr)/*,m_nMaxSize(((unsigned int)(-1))>>1)*/
{ 
	m_pHead=m_pTail=new CNode<T>();
}

template<class T>
CNode<T>::CNode():m_pNext(nullptr)
{
	memset(&m_t,0,sizeof(T));
}


template<class T>
CNode<T>::CNode( T t ):m_t(t)
{
	m_pNext=nullptr;
}


template<class T>
bool CQueue<T>::enqueue( T t )
{
	CNode<T>* pT=new CNode<T>(t);
	pT->m_pNext=nullptr;
	m_pTail->m_pNext=pT;
	m_pTail=pT;
	return true;
}

template<class T>
bool CQueue<T>::dequeue( T& t )
{
	if (isEmpty())
	{
		return false;
	}
	t=m_pHead->m_pNext->m_t;
	CNode<T>* pNode=m_pHead->m_pNext;
	m_pHead->m_pNext=pNode->m_pNext;
	if (pNode==m_pTail)
	{
		m_pTail=m_pHead;
	}
	delete pNode;
	pNode=nullptr;
	return true;
}

template<class T>
bool CQueue<T>::isEmpty()
{
	return m_pTail==m_pHead;
}

template<class T>
CQueue<T>::~CQueue(void)
{
	clear();
}

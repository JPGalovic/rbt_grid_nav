#pragma once
/**
 * List
 * @author J.P.Galovic
 * @date March 2018
 */

#include "ListNodeIter.h"

#include <stdexcept>

template<class T>
class List
{
private:
	ListNode<T>* fTop;
	ListNode<T>* fLast;
	int fCount;

public:
	List();
	~List();

	List(List & aOther);
	List& operator= (List & aOther);
	bool empty();
	int size();

	void push_front(T & aElement);
	void push_back(T & aElement);
	void add(T & aElement);
	void remove(T & aElement);

	T & operator[](unsigned int aIndex);

	bool hasValue(T & aValue);

	ListNodeIter<T> getIter();
};

template<class T>
inline List<T>::List()
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;
}

template<class T>
inline List<T>::~List()
{
	while (fTop != nullptr)
	{
		ListNode<T>* lTemp = (ListNode<T>*)&fTop->getNext();
		fTop->remove();
		delete fTop;
		fTop = lTemp;
	}
}

template<class T>
inline List<T>::List(List<T> & aOther)
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;

	for (ListNodeIter<T> iter = aOther.getIter().first(); iter != iter.rightEnd(); iter++)
		push_back(*iter);
}

template<class T>
inline List<T> & List<T>::operator=(List<T> & aOther)
{
	while (fTop != nullptr)
	{
		ListNode<T>* lTemp = (ListNode<T>*)&fTop->getNext();
		fTop->remove();
		delete fTop;
		fTop = lTemp;
	}

	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;

	for (ListNodeIter<T> iter = aOther.getIter().first(); iter != iter.rightEnd(); iter++)
		push_back(*iter);

	return *this;
}

template<class T>
inline bool List<T>::empty()
{
	return fTop == nullptr;
}

template<class T>
inline int List<T>::size()
{
	return fCount;
}

template<class T>
inline void List<T>::push_front(T & aElement)
{
	ListNode<T>* lNewElement = new ListNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewElement;
		fLast = lNewElement;
	}
	else
	{
		fTop->prepend(*lNewElement);
		fTop = lNewElement;
	}
	fCount++;
}

template<class T>
inline void List<T>::push_back(T & aElement)
{
	ListNode<T>* lNewElement = new ListNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewElement;
		fLast = lNewElement;
	}
	else
	{
		fLast->append(*lNewElement);
		fLast = lNewElement;
	}
	fCount++;
}

template<class T>
inline void List<T>::add(T & aElement)
{
	push_back(aElement);
}

template<class T>
inline void List<T>::remove(T & aElement)
{
	ListNode<T>* lNode = fTop;

	while (lNode != nullptr)
	{
		if (lNode->getValue() == aElement)
			break;
		lNode = (ListNode<T>*)&lNode->getNext();
	}

	if (lNode != nullptr)
	{
		if (lNode == fTop)
			fTop = (ListNode<T>*)&lNode->getNext();
		if (lNode == fLast)
			fLast = (ListNode<T>*)&lNode->getPrevious();

		lNode->remove();
		delete lNode;
		fCount--;
	}
}

template<class T>
inline T & List<T>::operator[](unsigned int aIndex)
{
	if (aIndex >= fCount)
		throw std::range_error("Index out of range.");
	ListNode<T>* lNode = fTop;
	while (aIndex)
	{
		aIndex--;
		lNode = (ListNode<T>*)&lNode->getNext();
	}
	return lNode->getValue();
}

template<class T>
inline bool List<T>::hasValue(T & aValue)
{
	if (empty())
		return false;
	for (ListNodeIter<T> iter = getIter().first(); iter != iter.rightEnd(); iter++)
		if (*iter == aValue)
			return true;
	return false;
}

template<class T>
inline ListNodeIter<T> List<T>::getIter()
{
	return ListNodeIter<T>(*fTop);
}

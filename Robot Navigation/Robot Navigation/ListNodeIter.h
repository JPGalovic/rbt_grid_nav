#pragma once
/**
 * List Node Iterator, Iterator for iterating through List Nodes
 * @author J.P.Galovic
 * @date March 2018
 */
#include "ListNode.h"

template<class T>
class ListNodeIter
{
private:
	enum IterState {BEFORE, DATA, AFTER};

	IterState fState;

	ListNode<T>* fLeftMost;
	ListNode<T>* fRightMost;
	ListNode<T>* fCurrent;

public:
	ListNodeIter(ListNode<T> & aList);

	T & operator*();
	ListNodeIter & operator++();
	ListNodeIter operator++(int);
	ListNodeIter & operator--();
	ListNodeIter operator--(int);

	bool operator==(ListNodeIter & aOtherIter);
	bool operator!=(ListNodeIter & aOtherIter);

	ListNodeIter leftEnd();
	ListNodeIter first();
	ListNodeIter last();
	ListNodeIter rightEnd();
};

template<class T>
inline ListNodeIter<T>::ListNodeIter(ListNode<T>& aList)
{
	fLeftMost = &aList;
	while (&fLeftMost->getPrevious() != nullptr)
		fLeftMost = &fLeftMost->getPrevious();

	fCurrent = fLeftMost;
	if (fCurrent != nullptr)
		fState = DATA;
	else
		fState = AFTER;

	fRightMost = &aList;
	while (&fRightMost->getNext() != nullptr)
		fRightMost = &fRightMost->getNext();
}

template<class T>
inline T & ListNodeIter<T>::operator*()
{
	return fCurrent->getValue();
}

template<class T>
inline ListNodeIter<T> & ListNodeIter<T>::operator++()
{
	switch (fState)
	{
	case BEFORE:
		fCurrent = fLeftMost;
		if (fCurrent == nullptr)
			fState = AFTER;
		else
			fState = DATA;
		break;
	case DATA:
		fCurrent = &fCurrent->getNext();
		if (fCurrent == nullptr)
			fState = AFTER;
		break;
	default:
		break;
	}

	return *this;
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::operator++(int)
{
	ListNodeIter lTemp = *this;
	++(*this);
	return lTemp;
}

template<class T>
inline ListNodeIter<T> & ListNodeIter<T>::operator--()
{
	switch (fState)
	{
	case AFTER:
		fCurrent = fRightMost;
		if (fCurrent == nullptr)
			fState = BEFORE;
		else
			fState = DATA;
		break;
	case DATA:
		fCurrent = &fCurrent->getPrevious();
		if (fCurrent == nullptr)
			fState = BEFORE;
		break;
	default:
		break;
	}

	return *this;
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::operator--(int)
{
	ListNodeIter lTemp = *this;
	--(*this);
	return lTemp;
}

template<class T>
inline bool ListNodeIter<T>::operator==(ListNodeIter<T> & aOtherIter)
{
	return fLeftMost == aOtherIter.fLeftMost && fRightMost == aOtherIter.fRightMost && fCurrent == aOtherIter.fCurrent && fState == aOtherIter.fState;
}

template<class T>
inline bool ListNodeIter<T>::operator!=(ListNodeIter<T> & aOtherIter)
{
	return !(*this == aOtherIter);
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::leftEnd()
{
	ListNodeIter lTemp = *this;
	lTemp.fCurrent = nullptr;
	lTemp.fState = BEFORE;
	return lTemp;
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::first()
{
	return ++(leftEnd());
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::last()
{
	return --(rightEnd());
}

template<class T>
inline ListNodeIter<T> ListNodeIter<T>::rightEnd()
{
	ListNodeIter lTemp = *this;
	lTemp.fCurrent = nullptr;
	lTemp.fState = AFTER;
	return lTemp;
}

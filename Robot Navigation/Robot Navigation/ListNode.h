#pragma once
/**
 * DL List Node, Defines Doubly Linked Node (used for lists)
 * @version 1.2.0
 * @author J.P.Galovic
 * @date March 2018
 */
template<class T>
class ListNode
{
private:
	T fValue;
	ListNode* fNext;
	ListNode* fPrevious;

	ListNode()
	{
		fValue = T();
		fNext = nullptr;
		fPrevious = nullptr;
	}

public:
	ListNode(T & aValue);

	void prepend(ListNode & aNode);
	void append(ListNode & aNode);
	void remove();

	T & getValue();
	ListNode & getNext();
	ListNode & getPrevious();
};

template<class T>
inline ListNode<T>::ListNode(T & aValue)
{
	fValue = aValue;
	fPrevious = nullptr;
	fNext = nullptr;
}

template<class T>
inline void ListNode<T>::prepend(ListNode & aNode)
{
	aNode.fNext = this;

	if (fPrevious != nullptr)
	{
		aNode.fPrevious = fPrevious;
		fPrevious->fNext = &aNode;
	}

	fPrevious = &aNode;
}

template<class T>
inline void ListNode<T>::append(ListNode & aNode)
{
	aNode.fPrevious = this;

	if (fNext != nullptr)
	{
		aNode.fNext = fNext;
		fNext->fPrevious = &aNode;
	}

	fNext = &aNode;
}

template<class T>
inline void ListNode<T>::remove()
{
	if (fPrevious != nullptr)
		fPrevious->fNext = fNext;

	if (fNext != nullptr)
		fNext->fPrevious = fPrevious;
}

template<class T>
inline T & ListNode<T>::getValue()
{
	return fValue;
}

template<class T>
inline ListNode<T> & ListNode<T>::getNext()
{
	return *fNext;
}

template<class T>
inline ListNode<T> & ListNode<T>::getPrevious()
{
	return *fPrevious;
}

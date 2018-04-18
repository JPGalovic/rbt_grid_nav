#pragma once
/** 
 *
 * Adapted from code developed for COS30008 Data Structures and Patterns
 * @author  J.P.Galovic
 * @version v1.0.3
 * @date    18-04-2018
 */
#include "DLNode.h"

#include <stdexcept>

template <class T>
class List
{
private:
	DLNode<T>* fTop;
	DLNode<T>* fLast;

	unsigned int fCount;
private:
	// Construction & Destruction
	List();
	List(const List<T> & aOther);

	~List();

	List<T> & operator=(const List<T> & aOther);

	// Getters
	bool isEmpty() const;
	int size() const;

	const T & getValue(unsigned int aIndex) const;
	const T & operator[](unsigned int aIndex) const;

	const T & remove(unsigned int aIndex);

	bool hasValue(const T & aValue) const;

	// Setters
	void setValue(unsigned int aIndex, const T & aValue);

	void pushFront(const T & aElement);
	void pushBack(const T & aElement);

	void add(const T & aElement);

	void remove(const T & aElement);
};

/**
 * Default constructor, constructs empty list.
 */
template<class T>
inline List<T>::List()
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;
}

/**
 * Copy constructor, copies items in list.
 * @param aOther, refence to other list.
 */
template<class T>
inline List<T>::List(const List<T> & aOther)
{
	fTop = nullptr;
	fLast = nullptr;
	fCount = 0;

	for (int i = 0; i < aOther.count(); i++)
		pushBack(aOther[i]);
}

template<class T>
inline List<T>::~List()
{
	while (fTop != nullptr)
	{
		DLNode<T>* lTemp = (Node *)&fTop->getNext();
		fTop->remove();
		delete fTop;
		fTop = lTemp;
	}
}

template<class T>
inline List<T> & List<T>::operator=(const List<T> & aOther)
{
	if (&aOther != this)
	{
		while (fTop != nullptr)
		{
			DLNode<T>* lTemp = (Node *)&fTop->getNext();
			fTop->remove();
			delete fTop;
			fTop = lTemp;
		}

		fTop = nullptr;
		fLast = nullptr;
		fCount = 0;

		for (int i = 0; i < aOther.count(); i++)
			pushBack(aOther[i]);
	}
	return *this;
}

/**
 * Determines if list is empty.
 */
template<class T>
inline bool List<T>::isEmpty() const
{
	return fTop == nullptr && fLast == nullptr && fCount == 0;
}

/**
 * reports the size of the list.
 */
template<class T>
inline int List<T>::size() const
{
	return fCount;
}

/**
 * Gets the value of the specified node value.
 * @param aIndex, index of node.
 */
template<class T>
inline const T & List<T>::getValue(unsigned int aIndex) const
{
	if (!(aIndex < fCount))
		std::range_error("Index out of bounds.");
	DLNode<T> * lNode = fTop;
	while (aIndex)
	{
		aIndex--;
		lNode = (DLNode<T> *) &lNode->getNext();
	}
	return lNode->getValue();
}

/**
 * Gets the value of the specified node value.
 * @param aIndex, index of node.
 */
template<class T>
inline const T & List<T>::operator[](unsigned int aIndex) const
{
	if (!(aIndex < fCount))
		std::range_error("Index out of bounds.");
	return getValue(aIndex);
}

/**
 * Removes a node at the specified index.
 */
template<class T>
inline const T & List<T>::remove(unsigned int aIndex)
{
	if (!(aIndex < fCount))
		std::range_error("Index out of bounds.");
	DLNode<T> * lNode = fTop;
	while (aIndex)
	{
		aIndex--;
		lNode = (DLNode<T> *) &lNode->getNext();
	}

	lNode->remove();

	delete lNode;
	fCount--;
}
/**
 * Checks to see if value is in list.
 */
template<class T>
inline bool List<T>::hasValue(const T & aValue) const
{
	DLNode<T> * lNode = fTop;
	for (int i = 0; i < fCount; i++)
		if (lNode->getValue() == aValue)
			return true;
		else
			lNode = (DLNode<T> *) &lNode->getNext();
	return false;
}

/**
 * Sets the value of a node at a given index.
 * @param aIndex, index of node to set.
 * @param aValue, value of node to set.
 */
template<class T>
inline void List<T>::setValue(unsigned int aIndex, const T & aValue)
{
	if (!(aIndex < fCount))
		std::range_error("Index out of bounds.");
	DLNode<T> * lNode = fTop;
	while (aIndex)
	{
		aIndex--;
		lNode = (DLNode<T> *) &lNode->getNext();
	}

	lNode->setValue(aValue);
}

template<class T>
inline void List<T>::pushFront(const T & aElement)
{
	DLNode<T>* lNewNode = new DLNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewNode;
		fLast = lNewNode;
	}
	else
	{
		fTop->prepend(*lNewNode);
		fTop = lNewNode;
	}
	fCount++;
}

template<class T>
inline void List<T>::pushBack(const T & aElement)
{
	DLNode<T>* lNewNode = new DLNode<T>(aElement);

	if (fTop == nullptr)
	{
		fTop = lNewNode;
		fLast = lNewNode;
	}
	else
	{
		fLast->append(*lNewNode);
		fLast = lNewNode;
	}
	fCount++;
}

template<class T>
inline void List<T>::add(const T & aElement)
{
	pushBack(aElement);
}


template<class T>
inline void List<T>::remove(const T & aElement)
{
	DLNode<T> * lNode = fTop;
	while (lNode != nullptr)
	{
		if (lNode->getValue() == aElement)
			break;
		lNode = (DLNode<T> *) &lNode->getNext();
	}

	if (lNode != nullptr)
	{
		if (lNode == fTop)
			fTop = (DLNode<T> *) & lNode->getNext();
		if (lNode == fLast)
			fLast = (DLNode<T> *) & lNode->getPrevious();

		lNode->remove();

		delete lNode;
		fCount--;
	}
}

#pragma once

/**
 * Doubly Linked Node, used for lists
 * Adapted from code developed for COS30008 Data Structures and Patterns
 * @author  J.P.Galovic
 * @version v1.0.3
 * @date    18-04-2018
 */
template<class T>
class DLNode
{
private:
	T fValue;

	DLNode<T> * fNext;
	DLNode<T> * fPrevious;

public:
	// Construction & Destruction
	DLNode(const T & aValue);
	
	// Getters
	const T & getValue() const;
	const DLNode<T> & getNext() const;
	const DLNode<T> & getPrevious() const;

	// Setters
	void setValue(const T & aValue);

	void append(const DLNode<T> & aNode);
	void prepend(const DLNode<T> & aNode);
	void remove();
};
/**
 * Node for Doubly Linked Lists.
 * @param aValue, value of node.
 */
template<class T>
inline DLNode<T>::DLNode(const T & aValue)
{
	fValue = aValue;
	fNext = nullptr;
	fPrevious = nullptr;
}

/**
 * Gets value of node.
 * @return Value of node.
 */
template<class T>
inline const T & DLNode<T>::getValue() const
{
	return fValue;
}

/**
 * Gets next node.
 * @return refernce to next node.
 */
template<class T>
inline const DLNode<T>& DLNode<T>::getNext() const
{
	return *fNext;
}

/**
 * Gets previous node.
 * @return refernce to previous node.
 */
template<class T>
inline const DLNode<T>& DLNode<T>::getPrevious() const
{
	return *fPrevious;
}

/**
 * Sets the value of the node.
 * @param aValue, value to set to.
 */
template<class T>
inline void DLNode<T>::setValue(const T & aValue)
{
	fValue = aValue;
}

/**
 * Connects to next node.
 * @param aNode, refernce to node to connect to.
 */
template<class T>
inline void DLNode<T>::append(const DLNode<T>& aNode)
{
	aNode.fPrevious = this;

	if (fNext != nullptr)
	{
		aNode.fNext = fNext;
		fNext->fPrevious = &aNode;
	}

	fNext = &aNode;
}

/**
 * Connect to previous node.
 * @param aNode, refernce to node to connect to.
 */
template<class T>
inline void DLNode<T>::prepend(const DLNode<T>& aNode)
{
	aNode.fNext = this;

	if (fPrevious != nullptr)
	{
		aNode.fPrevious = fPrevious;
		fPrevious->fNext = &aNode;
	}

	fPrevious = &aNode;
}

/**
 * Removes node (does not delete)
 */
template<class T>
inline void DLNode<T>::remove()
{
	if (fPrevious != nullptr)
		fPrevious->fNext = fNext;
	if (fNext != nullptr)
		fNext->fPrevious = fPrevious;
}

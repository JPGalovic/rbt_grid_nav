#pragma once

#include <stdexcept>

template<class T, int N>
class NTree
{
private:
	T* fKey; // Value of node
	NTree<T, N> fNodes[N]; // array of subtrees

public:
	NTree();
	NTree(T& aKey);

	bool isEmpty();
	T& key();

	NTree<T, N> & operator[](unsigned int aIndex);

	void attachSubtree(unsigned int aIndex, NTree<T, N> & aSubTree);
	NTree<T, N> & detachSubtree(unsigned int aIndex);
};

template<class T, int N>
inline NTree<T, N>::NTree()
{
	fKey = nullptr;
	for (int i = 0; i < N; i++)
		fNodes[i] = nullptr;
}

template<class T, int N>
inline NTree<T, N>::NTree(T & aKey)
{
	fKey = &aKey;
	for (int i = 0; i < N; i++)
		fNodes[i] = nullptr;
}

template<class T, int N>
inline bool NTree<T, N>::isEmpty()
{
	if(fKey != nullptr)
		return false;
	for (int i = 0; i < N; i++)
		if (fNodes[i] != nullptr)
			return false;
	return true;
}

template<class T, int N>
inline T & NTree<T, N>::key()
{
	return *fKey;
}

template<class T, int N>
inline NTree<T, N> & NTree<T, N>::operator[](unsigned int aIndex)
{
	if (aIndex > N)
		throw std::out_of_range("Index out of range.");
	return *fNodes[aIndex];
}

template<class T, int N>
inline void NTree<T, N>::attachSubtree(unsigned int aIndex, NTree<T, N>& aSubTree)
{
	if (aIndex > N)
		throw std::out_of_range("Index out of range.");
	fNodes[aIndex] = &aSubTree;
}

template<class T, int N>
inline NTree<T, N>& NTree<T, N>::detachSubtree(unsigned int aIndex)
{
	if (aIndex > N)
		throw std::out_of_range("Index out of range");
	NTree<T, N> lTempNode = &fNodes[aIndex];
	fNodes[aIndex] = nullptr;
	return lTempNode;
}
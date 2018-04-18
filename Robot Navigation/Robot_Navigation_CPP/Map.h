#pragma once

/**
 * Map Node Data Type Template
 * @author  J.P.Galovic
 * @version v0.0.1
 * @date    19-04-2018
 */
#include "MapNode.h"

template<class I, class T, class N>
class Map
{
private:
	MapNode<I, T, N>* fOrigin;
	MapNode<I, T, N>* fCurrent;

public:
	// Construction & Destruction
	Map(const MapNode<I, T, N> & aOrigin);

	// Getters
	const MapNode<I, T, N> & getNode(const I & aIdentifier) const;
	const T & getNodeValue(const I & aIdenifier) const;

	const T & getValue() const;

	const MapNode<I, T, N> & getCurrent() const;

	// Setters
	//void setCellValue(const I & aIdentifer, const T & aValue);

	void setValue(const T & aValue);

	// Misc
	void move(unsigned int aIndex);
	void move(const I & aIdent);
};

template<class I, class T, class N>
inline Map<I, T, N>::Map(const MapNode<I, T, N>& aOrigin)
{
	fOrigin = &aOrigin;
	fCurrent = &aOrigin;
}

template<class I, class T, class N>
inline const MapNode<I, T, N>& Map<I, T, N>::getNode(const I & aIdentifier) const
{
	List<MapNode<I, T, N>*> lOpen; // Open List for nodes Descovery
	List<MapNode<I, T, N>*> lClosed; // Closed List of alredy checked nodes.

	lOpen.add(fOrigin);

	while (!lOpen.isEmpty())
	{
		MapNode<I, T, N>* lCurrent = lOpen[0];

		if (lCurrent->getIdent() == aIdentifier) // If this is the been searched for return it.
			return *lCurrent;

		lOpen.remove(0);
		lClosed.add(lCurrent);

		// Get each connection for current and add it to the open list if not alredy in the open or closed lists.
		for (int i = 0; i < lCurrent.connectionCount(); i++) 
		{
			MapNode<I, T, N>* lTemp = &lCurrent->getConnection(i);
			if (lClosed.hasValue(lTemp))
				continue;
			if (!lOpen.hasValue(lTemp))
				lOpen.add(lTemp);
		}
	}

	throw std::runtime_error("Node does not exist")
}

template<class I, class T, class N>
inline const T & Map<I, T, N>::getNodeValue(const I & aIdenifier) const
{
	try
	{
		return getNode(aIdenifier).getValue();
	}
}

template<class I, class T, class N>
inline const T & Map<I, T, N>::getValue() const
{
	return fCurrent->getValue();
}

template<class I, class T, class N>
inline const MapNode<I, T, N>& Map<I, T, N>::getCurrent() const
{
	return *fCurrent;
}

template<class I, class T, class N>
inline void Map<I, T, N>::setValue(const T & aValue)
{
	fCurrent->setValue(aValue);
}

template<class I, class T, class N>
inline void Map<I, T, N>::move(unsigned int aIndex)
{
	fCurrent = & fCurrent->getConnection(aIndex);
}

template<class I, class T, class N>
inline void Map<I, T, N>::move(const I & aIdent)
{
	try
	{
		fCurrent = &fCurrent->getConnection(aIdent);
	}
	catch (const std::runtime_error & e)
	{
		throw std::runtime_error(e.what());
	}
}

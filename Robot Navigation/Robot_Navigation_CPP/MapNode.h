#pragma once

/**
 * Map Node Data Type Template
 * @author  J.P.Galovic
 * @version v0.0.1
 * @date    18-04-2018
 */
#include "List.h"

#include <stdexcept>

template <class I, class T, class N> // Type of identifier, Type of Value, Type of Connection Value
class MapNode {
private:
	I fIdent; // Node Identifier
	T fValue; // Node Value

	List<MapNodeLink<I, T, N>*> fConnections; // Set of connections 

public:
	// Construction & Destruction
	MapNode(const I & aIdent, const T & aValue);

	// Getters
	const I & getIdent() const;
	const T & getValue() const;

	const MapNode<I, T, N> & operator[] (unsigned int aIndex) const;

	const MapNode<I, T, N> & getConnection(unsigned int aIndex) const;
	const MapNode<I, T, N> & getConnection(const I & aIdent) const;

	const int connectionCount() const;

	// Setters
	void setIdent(const I & aIdent);
	void setValue(const T & aIdent);

	void addConnection(const MapNodeLink<I, T, N> & aLink);

	void addConnection(const N & aConnectionValue, const MapNode<I, T, N> & aDestination);
	void addOneWayConnection(const N & aConnectionValue, const MapNode<I, T, N> & aDestination);

	void removeConnection(const MapNodeLink<I, T, N> & aLink);
	void removeConnection(const I & aIdent);
	void removeConnection(int aIndex);
};

template<class I, class T, class N>
inline MapNode<I, T, N>::MapNode(const I & aIdent, const T & aValue)
{
	fIdent = aIdent;
	fValue = aValue;
}

template<class I, class T, class N>
inline const I & MapNode<I, T, N>::getIdent() const
{
	return fIdent;
}

template<class I, class T, class N>
inline const T & MapNode<I, T, N>::getValue() const
{
	return fValue;
}

template<class I, class T, class N>
inline const MapNode<I, T, N>& MapNode<I, T, N>::operator[](unsigned int aIndex) const
{
	if (!(aIndex < fConnections.count()))
		throw std::range_error("Index out of bounds");

	return fConnections[aIndex];
}

template<class I, class T, class N>
inline const MapNode<I, T, N>& MapNode<I, T, N>::getConnection(unsigned int aIndex) const
{
	if (!(aIndex < fConnections.count()))
		throw std::range_error("Index out of bounds");

	return fConnections[aIndex];
}

template<class I, class T, class N>
inline const MapNode<I, T, N>& MapNode<I, T, N>::getConnection(const I & aIdent) const
{
	for (int i = 0; i < fConnections.count(); i++)
		if (fConnections[i].getIdent() == aIdent)
			return fConnections[i];
	throw std::runtime_error("Connection not found");
}

template<class I, class T, class N>
inline const int MapNode<I, T, N>::connectionCount() const
{
	return fConnections.fCount;
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::setIdent(const I & aIdent)
{
	fIdent = aIdent;
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::setValue(const T & aIdent)
{
	fValue = aValue;
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::addConnection(const MapNodeLink<I, T, N> & aLink)
{
	fConnections.add(&aLink);
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::addConnection(const N & aConnectionValue, const MapNode<I, T, N>& aDestination)
{
	fConnections.add(new MapNodeLink<I, T, N>(aConnectionValue, aDestination));
	aDestination.addConnection(aConnectionValue, *this);
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::addOneWayConnection(const N & aConnectionValue, const MapNode<I, T, N>& aDestination)
{
	fConnections.add(new MapNodeLink<I, T, N>(aConnectionValue, aDestination));
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::removeConnection(const MapNodeLink<I, T, N>& aLink)
{
	return fConnections.remove(aLink);
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::removeConnection(const I & aIdent)
{
	if (!(aIndex < fConnections.count()))
		throw std::range_error("Index out of bounds");

	for (int i = 0; i < fConnections.count(); i++)
		if (fConnections[i].getIdent() == aIdent)
			return fConnections.remove(i);
}

template<class I, class T, class N>
inline void MapNode<I, T, N>::removeConnection(int aIndex)
{
	return fConnections.remove(aIndex);
}

/**
 * Map Node Link Type Template
 * @author  J.P.Galovic
 * @version v0.0.1
 * @date    17-04-18
 */

template <class I, class T, class N>
class MapNodeLink
{
private:
	I fIdent; // Identifier for link (used for searching for a set path)
	N fValue; // Value of Link (used for AI heuristics)
	MapNode<I, T, N> * fDestination; // Pointer to Destination Node

public:
	// Construction & Destruction
	MapNodeLink(const N & aValue, const MapNode<I, T, N> & aNode);
	MapNodeLink(const I & aIdent, const N & aValue, const MapNode<I, T, N> & aNode);

	// Getters
	const I & getIdent() const;
	const N & getValue() const;
	const MapNode & getDestination() const;

	// Setters
	void setValue(const N & aValue);
};

/**
 * Contains link to node and value of link.
 * @param aValue, value of Link.
 * @param aNode, destination node.
 */
template<class I, class T, class N>
inline MapNodeLink<I, T, N>::MapNodeLink(const N & aValue, const MapNode<I, T, N> & aNode)
{
	fIdent = I();
	fValue = aValue;
	fNode = & aNode;
}

/**
 * Constructs ling to node, with custom ident and value of link.
 * @param aIdent, identifier of link.
 * @param aValue, value of link.
 * @param aDestination, destination node.
 */
template<class I, class T, class N>
inline MapNodeLink<I, T, N>::MapNodeLink(const I & aIdent, const N & aValue, const MapNode<I, T, N>& aNode)
{
	fIdent = aIdent;
	fValue = aValue;
	fNode = &aNode;
}

/**
 * Gets identifier.
 * @return identifier of link
 */
template<class I, class T, class N>
inline const I & MapNodeLink<I, T, N>::getIdent() const
{
	return fIdent;
}

/**
 * Gets value of Link.
 * @return value of Link.
 */
template<class I, class T, class N>
inline const N & MapNodeLink<I, T, N>::getValue() const
{
	return fValue;
}

/**
 * Gets destination of link.
 * @return refernce to destination.
 */
template<class I, class T, class N>
inline const MapNode<I, T, N> & MapNodeLink<I, T, N>::getDestination() const
{
	return *fDestination;
}

/**
 * Sets value of Link.
 * @param aValue, value of link.
 */
template<class I, class T, class N>
inline void MapNodeLink<I, T, N>::setValue(const N & aValue)
{
	fValue = aValue;
}


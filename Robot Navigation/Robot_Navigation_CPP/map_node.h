#pragma once

/**
 * Map Node Data Type Template
 * @author  J.P.Galovic
 * @version v0.0.1
 * @date    17-04-2018
 */

template <class I, class T, class N>
class MapNode {
private:
	I fIdent; // Node Identifier
	T fValue; // Node Value

	
};



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
	N fValue; // Value of Link (used for AI heuristics)
	MapNode * fDestination; // Pointer to Destination Node

public:
	// Construction & Destruction
	MapNodeLink(const N & aValue, const MapNode & aNode);
	
	// Getters
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
inline MapNodeLink<I, T, N>::MapNodeLink(const N & aValue, const MapNode<I,T,N> & aNode)
{
	fValue = aValue;
	fNode = & aNode;
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

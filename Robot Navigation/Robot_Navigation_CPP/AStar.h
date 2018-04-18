#pragma once

/**
 * Implementation of A* (A Star) search algorithem for maps
 * @author  J.P.Galovic
 * @version v0.0.1
 * @date    19-04-2018
 */
#include "Map.h"

template<class I, class T, class N> // to match map settings
class AStar
{
private:
	I fGoal; // Ident of Goal

	Map<I, T, N> * fMap; // Map to search;

	MapNode<I, T, N> * fBlock; // Refernce to blocked node;

	const List<I> & constructPath(const Map<I, I, N> & aCameFromMap) const;
	int heuristicCostEstimate(const MapNode<I, T, N> & aSource, const MapNode<I, T, N>& aDestination) const;

public:
	// Construction and Destruction
	AStar(const I & aGoal, const Map<I, T, N> & aMap);
	AStar(const I & aGoal, const Map<I, T, N> & aMap, const MapNode<I, T, N> & aBlock);

	// Getters
	const List<I> & search() const;

	// Setters
	void setGoal(const I & aGoal);
	void setBlock(const MapNode<I, T, N> & aBlock);
};

/**
 * Constructs a list containing a path using node identifiers for which path to take.
 * @param aCameFromMap, with current pointing at the goal.
 */
template<class I, class T, class N>
inline const List<I>& AStar<I, T, N>::constructPath(const Map<I, I, N>& aCameFromMap) const
{
	List<I> lList;
	MapNode<I, I, N> * lNode = aCameFromMap->fCurrent;
	while (lNode != fMap->fOrigin)
	{
		I lDirection = lNode->getValue(); // Get direction from current node.
		lList.pushFront(lDirection); // Add direction to front of list.
		lNode = aCameFromMap->move(lDirection);
	}
	return lList;
}

/**
 * Calulates husristic cost estimate of traveling from source to destination. via a given path.
 * @param aSource, source node.
 * @param aDestination, destination node.
 */
template<class I, class T, class N>
inline int AStar<I, T, N>::heuristicCostEstimate(const MapNode<I, T, N>& aSource, const MapNode<I, T, N>& aDestination) const
{
	return 1;
}

template<class I, class T, class N>
inline AStar<I, T, N>::AStar(const I & aGoal, const Map<I, T, N>& aMap)
{
	fGoal = aGoal;
	fMap = &aMap;
	fBlock = nullptr;
}

template<class I, class T, class N>
inline AStar<I, T, N>::AStar(const I & aGoal, const Map<I, T, N>& aMap, const MapNode<I, T, N>& aBlock)
{
	fGoal = aGoal;
	fMap = &aMap;
	fBlock = &aBlock;
}

/**
 * Runs search. Code Generated based on psudo code avalible at https://en.wikipedia.org/wiki/A*_search_algorithm
 * @return List of Coordinates for Agent to follow (path).
 * @throw If a path cannot be found from Start to Goal, then method throws with error. "No path to goal found."
 */
template<class I, class T, class N>
inline const List<I>& AStar<I, T, N>::search() const
{
	// Reached end of open list without finding path to goal. throw error???
	throw std::runtime_error("No path to goal found.");
}

/**
 * Sets ident of goal to search for.
 * @param aGoal, value of goal identifier.
 */
template<class I, class T, class N>
inline void AStar<I, T, N>::setGoal(const I & aGoal)
{
	fGoal = aGoal;
}

/**
 * Sets pointer to blocked node (not sure on this impelentation).
 * @param aBlock, refernce to blocked node.
 */
template<class I, class T, class N>
inline void AStar<I, T, N>::setBlock(const MapNode<I, T, N>& aBlock)
{
	fBlock = &aBlock;
}

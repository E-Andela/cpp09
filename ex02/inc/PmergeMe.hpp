#pragma once

#include <algorithm>
#include <deque>
#include <vector>
#include <cstddef>

// ============================================================================
// Vector-based Ford-Johnson merge-insertion sort implementation
// ============================================================================

template <typename T>
std::vector<T> stripVectorVector(const std::vector<T> &v, size_t stepSize)
{
	std::vector<T> stripped;
	for (size_t i = 0; i < v.size(); i += stepSize)
	{
		stripped.push_back(v[i]);
	}
	return stripped;
}

std::vector<int> calculateInsertionOrderVector(int inserts)
{
	std::vector<int> order;
	order.reserve(inserts);
	
	int j_prev = 1;
	int j_curr = 3;

	order.push_back(1);

	while ((int)order.size() < inserts)
	{
		if (j_curr < inserts)
			order.push_back(j_curr);
		int i;
		if (j_curr >= inserts)
			i = inserts;
		else
			i = j_curr - 1;

		while (i > j_prev)
		{
			order.push_back(i);
			--i;
		}

		int j_next = j_prev * 2 + j_curr;
		j_prev = j_curr;
		j_curr = j_next;
	}
	return order;
}

std::vector<int> updateOrderVector(const std::vector<int> &order, int insertedIndex)
{
	std::vector<int> newOrder = order;
	for (size_t i = 0; i < order.size(); ++i)
	{
		if (order[i] >= insertedIndex)
			++newOrder[i];
	}
	return newOrder;
}

template <typename T>
bool detachLeftoverBlockVector(std::vector<T> &c, size_t stepSize, std::vector<T> &leftoverBlock)
{
	size_t numBlocks = c.size() / stepSize;
	if (numBlocks % 2 == 0)
		return false;
	leftoverBlock.assign(c.end() - stepSize, c.end());
	c.erase(c.end() - stepSize, c.end());
	return true;
}

template <typename T>
void pairBlocksDescendingVector(std::vector<T> &c, size_t stepSize)
{
	for (size_t i = 0; i + stepSize < c.size(); i += stepSize * 2)
	{
		if (c[i] < c[i + stepSize])
		{
			for (size_t j = 0; j < stepSize; j++)
				std::swap(c[i + j], c[i + j + stepSize]);
		}
	}
}

template <typename T>
void splitBlocksVector(const std::vector<T> &c, size_t stepSize, std::vector<T> &large, std::vector<T> &small)
{
	for (size_t i = 0; i < c.size(); ++i)
	{
		if ((i / stepSize) % 2 == 0)
			large.push_back(c[i]);
		else
			small.push_back(c[i]);
	}
}

template <typename T>
struct ChainInitVector
{
	std::vector<T> smallStripped;
	std::vector<int> order;
	std::vector<T> mergedStripped;
	std::vector<int> mergedOrder;
};

template <typename T>
ChainInitVector<T> initializeChainsVector(size_t stepSize, std::vector<T> &large, const std::vector<T> &small)
{
	ChainInitVector<T> init;
	std::vector<T> largeStripped = stripVectorVector(large, stepSize);
	init.smallStripped = stripVectorVector(small, stepSize);
	init.order = calculateInsertionOrderVector(init.smallStripped.size());
	init.mergedStripped = largeStripped;
	init.mergedOrder = init.order;

	if (!init.smallStripped.empty())
	{
		large.insert(large.begin(), small.begin(), small.begin() + stepSize);
		init.mergedStripped.insert(init.mergedStripped.begin(), init.smallStripped[0]);
		init.mergedOrder = updateOrderVector(init.mergedOrder, 0);
	}
	return init;
}

template <typename T>
void insertPendingBlocksVector(size_t stepSize, const std::vector<T> &small, const std::vector<T> &smallStripped, const std::vector<int> &order, std::vector<T> &mergedStripped, std::vector<int> &mergedOrder, std::vector<T> &large)
{
	for (size_t i = 1; i < order.size(); ++i)
	{
		int index = order[i] - 1;
		int mergedIndex = mergedOrder[i] - 1;
		T target = smallStripped[index];

		typename std::vector<T>::iterator insertpos = std::lower_bound(mergedStripped.begin(), mergedStripped.begin() + mergedIndex, target);
		int mergedInsertPos = std::distance(mergedStripped.begin(), insertpos);

		mergedOrder = updateOrderVector(mergedOrder, mergedInsertPos);
		mergedStripped.insert(insertpos, target);

		large.insert(large.begin() + mergedInsertPos * stepSize, small.begin() + index * stepSize, small.begin() + (index * stepSize) + stepSize);
	}
}

template <typename T>
void insertLeftoverBlockVector(size_t stepSize, const std::vector<T> &leftoverBlock, std::vector<T> &mergedStripped, std::vector<T> &large)
{
	if (leftoverBlock.empty())
		return;

	T target = leftoverBlock[0];
	typename std::vector<T>::iterator insertpos = std::lower_bound(mergedStripped.begin(), mergedStripped.end(), target);
	int insertIndex = std::distance(mergedStripped.begin(), insertpos);

	mergedStripped.insert(insertpos, target);
	large.insert(large.begin() + insertIndex * stepSize, leftoverBlock.begin(), leftoverBlock.end());
}

template <typename T>
void mergeInsertionSortVector(std::vector<T> &c, int iteration)
{
	size_t stepSize = 1 << (iteration);

	if (c.size() / stepSize <= 1)
		return;

	std::vector<T> leftoverBlock;
	bool hasLeftoverBlock = detachLeftoverBlockVector(c, stepSize, leftoverBlock);

	pairBlocksDescendingVector(c, stepSize);

	mergeInsertionSortVector(c, iteration + 1);

	std::vector<T> large;
	std::vector<T> small;
	splitBlocksVector(c, stepSize, large, small);

	ChainInitVector<T> chains = initializeChainsVector(stepSize, large, small);

	insertPendingBlocksVector(stepSize, small, chains.smallStripped, chains.order, chains.mergedStripped, chains.mergedOrder, large);

	if (hasLeftoverBlock)
		insertLeftoverBlockVector(stepSize, leftoverBlock, chains.mergedStripped, large);

	c = large;
}

// ============================================================================
// Deque-based Ford-Johnson merge-insertion sort implementation
// ============================================================================

template <typename T>
std::vector<T> stripVectorDeque(const std::deque<T> &v, size_t stepSize)
{
	std::vector<T> stripped;
	for (size_t i = 0; i < v.size(); i += stepSize)
	{
		stripped.push_back(v[i]);
	}
	return stripped;
}

std::vector<int> calculateInsertionOrderDeque(int inserts)
{
	std::vector<int> order;
	order.reserve(inserts);
	
	int j_prev = 1;
	int j_curr = 3;

	order.push_back(1);

	while ((int)order.size() < inserts)
	{
		if (j_curr < inserts)
			order.push_back(j_curr);
		int i;
		if (j_curr >= inserts)
			i = inserts;
		else
			i = j_curr - 1;

		while (i > j_prev)
		{
			order.push_back(i);
			--i;
		}

		int j_next = j_prev * 2 + j_curr;
		j_prev = j_curr;
		j_curr = j_next;
	}
	return order;
}

std::vector<int> updateOrderDeque(const std::vector<int> &order, int insertedIndex)
{
	std::vector<int> newOrder = order;
	for (size_t i = 0; i < order.size(); ++i)
	{
		if (order[i] >= insertedIndex)
			++newOrder[i];
	}
	return newOrder;
}

template <typename T>
bool detachLeftoverBlockDeque(std::deque<T> &c, size_t stepSize, std::deque<T> &leftoverBlock)
{
	size_t numBlocks = c.size() / stepSize;
	if (numBlocks % 2 == 0)
		return false;
	leftoverBlock.insert(leftoverBlock.end(), c.end() - stepSize, c.end());
	c.erase(c.end() - stepSize, c.end());
	return true;
}

template <typename T>
void pairBlocksDescendingDeque(std::deque<T> &c, size_t stepSize)
{
	for (size_t i = 0; i + stepSize < c.size(); i += stepSize * 2)
	{
		if (c[i] < c[i + stepSize])
		{
			for (size_t j = 0; j < stepSize; j++)
				std::swap(c[i + j], c[i + j + stepSize]);
		}
	}
}

template <typename T>
void splitBlocksDeque(const std::deque<T> &c, size_t stepSize, std::deque<T> &large, std::deque<T> &small)
{
	for (size_t i = 0; i < c.size(); ++i)
	{
		if ((i / stepSize) % 2 == 0)
			large.push_back(c[i]);
		else
			small.push_back(c[i]);
	}
}

template <typename T>
struct ChainInitDeque
{
	std::vector<T> smallStripped;
	std::vector<int> order;
	std::vector<T> mergedStripped;
	std::vector<int> mergedOrder;
};

template <typename T>
ChainInitDeque<T> initializeChainsDeque(size_t stepSize, std::deque<T> &large, const std::deque<T> &small)
{
	ChainInitDeque<T> init;
	std::vector<T> largeStripped = stripVectorDeque(large, stepSize);
	init.smallStripped = stripVectorDeque(small, stepSize);
	init.order = calculateInsertionOrderDeque(init.smallStripped.size());
	init.mergedStripped = largeStripped;
	init.mergedOrder = init.order;

	if (!init.smallStripped.empty())
	{
		large.insert(large.begin(), small.begin(), small.begin() + stepSize);
		init.mergedStripped.insert(init.mergedStripped.begin(), init.smallStripped[0]);
		init.mergedOrder = updateOrderDeque(init.mergedOrder, 0);
	}
	return init;
}

template <typename T>
void insertPendingBlocksDeque(size_t stepSize, const std::deque<T> &small, const std::vector<T> &smallStripped, const std::vector<int> &order, std::vector<T> &mergedStripped, std::vector<int> &mergedOrder, std::deque<T> &large)
{
	for (size_t i = 1; i < order.size(); ++i)
	{
		int index = order[i] - 1;
		int mergedIndex = mergedOrder[i] - 1;
		T target = smallStripped[index];

		typename std::vector<T>::iterator insertpos = std::lower_bound(mergedStripped.begin(), mergedStripped.begin() + mergedIndex, target);
		int mergedInsertPos = std::distance(mergedStripped.begin(), insertpos);

		mergedOrder = updateOrderDeque(mergedOrder, mergedInsertPos);
		mergedStripped.insert(insertpos, target);

		large.insert(large.begin() + mergedInsertPos * stepSize, small.begin() + index * stepSize, small.begin() + (index * stepSize) + stepSize);
	}
}

template <typename T>
void insertLeftoverBlockDeque(size_t stepSize, const std::deque<T> &leftoverBlock, std::vector<T> &mergedStripped, std::deque<T> &large)
{
	if (leftoverBlock.empty())
		return;

	T target = leftoverBlock[0];
	typename std::vector<T>::iterator insertpos = std::lower_bound(mergedStripped.begin(), mergedStripped.end(), target);
	int insertIndex = std::distance(mergedStripped.begin(), insertpos);

	mergedStripped.insert(insertpos, target);
	large.insert(large.begin() + insertIndex * stepSize, leftoverBlock.begin(), leftoverBlock.end());
}

template <typename T>
void mergeInsertionSortDeque(std::deque<T> &c, int iteration)
{
	size_t stepSize = 1 << (iteration);

	if (c.size() / stepSize <= 1)
		return;

	std::deque<T> leftoverBlock;
	bool hasLeftoverBlock = detachLeftoverBlockDeque(c, stepSize, leftoverBlock);

	pairBlocksDescendingDeque(c, stepSize);

	mergeInsertionSortDeque(c, iteration + 1);

	std::deque<T> large;
	std::deque<T> small;
	splitBlocksDeque(c, stepSize, large, small);

	ChainInitDeque<T> chains = initializeChainsDeque(stepSize, large, small);

	insertPendingBlocksDeque(stepSize, small, chains.smallStripped, chains.order, chains.mergedStripped, chains.mergedOrder, large);

	if (hasLeftoverBlock)
		insertLeftoverBlockDeque(stepSize, leftoverBlock, chains.mergedStripped, large);

	c = large;
}

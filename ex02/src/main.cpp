#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>
#include <algorithm>

int binarySearch(std::vector<int> &main, int target, int start, int last, int stepsize)
{
	if (start >= last)
        return start;

    int mid_block = start + (last - start) / 2;
    int mid_index = mid_block * stepsize;

    if (target > main[mid_index])
        return binarySearch(main, target, mid_block + 1, last, stepsize);
    else
        return binarySearch(main, target, start, mid_block, stepsize);
}

std::vector<int> stripVector(const std::vector<int> &v, size_t stepSize)
{
	std::vector<int> stripped;
	for (size_t i = 0; i < v.size(); i += stepSize)
	{
		stripped.push_back(v[i]);
	}
	return stripped;
}

std::vector<int> calculateInsertionOrder(int inserts)
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

std::vector<int> updateOrder(const std::vector<int> &order, int insertedIndex)
{
	std::vector<int> newOrder = order;
	for (size_t i = 0; i < order.size(); ++i)
	{
		if (order[i] >= insertedIndex)
			++newOrder[i];
	}
	return newOrder;
}

void mergeInsertionSort(std::vector<int> &c, int iteration)
{
	size_t stepSize = 1 << (iteration);
	std::cout << "Iteration: " << iteration << ", step size: " << stepSize << std::endl;
	
	if (c.size() / stepSize <= 1)	// don't know if this is correct
		return;

	bool hasleftover = (c.size() % (stepSize * 2) != 0);
	int leftover;
	if (hasleftover)
	{
		leftover = c.back();
		std::cout << "Leftover element: " << leftover << std::endl;
		c.pop_back();
	}

	// 1️⃣ Create pairs (bigger first)
	for (size_t i = 0; i + stepSize < c.size(); i += stepSize * 2)
	{
		int a = c[i];
		int b = c[i + stepSize];
		if (a < b)
		{
			for (size_t j = 0; j < stepSize; j++)
			{
				std::swap(c[i + j], c[i + j + stepSize]);
			}
		}
	}
	for (int i: c)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	// 2️⃣ Recursively sort the 'larger' half
	mergeInsertionSort(c, iteration + 1);

	std::vector<int> large;
	std::vector<int> small;

	for (size_t i = 0; i < c.size(); ++i)
	{
		if ((i / stepSize) % 2 == 0)
			large.push_back(c[i]);
	}
	for (size_t i = 0; i < c.size(); ++i)
	{
		if ((i / stepSize) % 2 != 0)
			small.push_back(c[i]);
	}

	std::cout << "large: ";
	for (int i: large)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::vector<int> largeStripped = stripVector(large, stepSize);
	std::vector<int> smallStripped = stripVector(small, stepSize);
	std::vector<int> mergedStripped = largeStripped;

	std::vector<int> order = calculateInsertionOrder(smallStripped.size());
	std::vector<int> mergedOrder = order;
	large.insert(large.begin(), small.begin(), small.begin() + stepSize);
	mergedStripped.insert(mergedStripped.begin(), smallStripped[0]);
	std::cout << "step size: " << stepSize << std::endl;
	mergedOrder = updateOrder(mergedOrder, 0);

	std::cout << "small stripped: ";
	for (int i: smallStripped)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::cout << "large stripped: ";
	for (int i: largeStripped)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;	

	std::cout << "small: ";
	for (int i: small)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::cout << "large: ";
	for (int i: large)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (size_t i = 1; i < order.size(); ++i)
	{
		int index = order[i] - 1;
		std::cout << "Index " << index << " " << std::endl;
		int mergedIndex = mergedOrder[i] - 1;
		std::cout << "Merged Index " << mergedIndex << std::endl;
		int target = smallStripped[index];
		std::cout << "Target " << target << std::endl;
		auto insertpos = std::lower_bound(mergedStripped.begin(), mergedStripped.begin() + mergedIndex, target);
		int mergedInsertPos = std::distance(mergedStripped.begin(), insertpos);
		std::cout << "Insert Position " << mergedInsertPos << std::endl;
		mergedOrder = updateOrder(mergedOrder, mergedInsertPos);
		mergedStripped.insert(insertpos, target);

		std::cout << "merged stripped after insertion: ";
		for (int i: mergedStripped)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;

		large.insert(large.begin() + mergedInsertPos * stepSize, small.begin() + index * stepSize, small.begin() + (index * stepSize) + stepSize);
		std::cout << "large after insertions: ";
		for (int i: large)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	//binary search for each element in small and insert into large
	std::cout << std::endl;
	//insert all elements from small into large
	if (hasleftover)
	{
		auto insertpos = std::lower_bound(large.begin(), large.end(), leftover);
		large.insert(insertpos, leftover);
	}
	c = large;

	std::cout << "--------------------------------" << std::endl;
}

int main()
{
	std::vector<int> c = {3, 2, 1, 8, 6, 7, 5, 4, 9, 10};
	std::vector<int> order = calculateInsertionOrder(4);
	mergeInsertionSort(c, 0);
	for (int i: c)
	{
		std::cout << i << " ";
	}

	// int stepSize = 4;
	// std::vector<int> large = {8, 1, 3, 2};
	// std::vector<int> small = {7, 6, 5, 4};

	// large.insert(large.begin(), small.begin(), small.begin() + stepSize);
	// for (int i: large)
	// {
	// 	std::cout << i << " ";
	// }
	// std::cout << std::endl;
}
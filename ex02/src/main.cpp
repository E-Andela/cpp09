#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>

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

void mergeInsertionSort(std::vector<int> &c, int iteration)
{
	size_t stepSize = 1 << (iteration);
	std::cout << "Iteration: " << iteration << ", step size: " << stepSize << std::endl;
	
	if (c.size() / stepSize <= 1)	// don't know if this is correct
		return;

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
	//binary search for each element in small and insert into large

	//insert all elements from small into large

}

int main()
{
	std::vector<int> c = {3, 2, 1, 8, 6, 7, 5, 4};
	mergeInsertionSort(c, 0);
}
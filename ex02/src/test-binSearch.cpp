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



int main()
{
	std::vector<int> main = {8, 1, 3, 2};
	std::vector<int> pend = {7, 6, 5, 4};

	int binarySearchResult;
	size_t stepSize = 4;

	binarySearchResult = binarySearch(main, 7, 0, main.size() / stepSize, stepSize);
}
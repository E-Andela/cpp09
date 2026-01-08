#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>

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

size_t boundedLowerBound(
	const std::vector<int> &v,
	int value,
	size_t left,
	size_t right)
{
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (value < v[mid])
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

void mergeInsertionSort(std::vector<std::pair<int, int>> &pairs)
{
	if (pairs.size() <= 1)
		return;

	std::vector<std::pair<int, int>> pairs;
	std::vector<int> larger;
	std::vector<int> smaller;

	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		int a = c[i];
		int b = c[i + 1];
		if (a < b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
		larger.push_back(a);
		smaller.push_back(b);
	}

	bool hasLeftover = (c.size() % 2 != 0);
	int leftover = hasLeftover ? c.back() : 0;

	if (hasLeftover)
	{
		std::cout << "Leftover element: " << leftover << std::endl;
	}

	mergeInsertionSort(larger);
	
	for (int i: larger)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::vector<int> order = calculateInsertionOrder(smaller.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		int idx = order[i] - 1;
		int value = smaller[idx];
		size_t pos = boundedLowerBound(larger, value, 0, idx);
		larger.insert(larger.begin() + pos, value);
	}

	if (hasLeftover)
	{
		size_t pos = boundedLowerBound(larger, leftover, 0, larger.size());
		larger.insert(larger.begin() + pos, leftover);
	}

	c = larger;
}

int main()
{
	std::vector<int> c = {4, 3, 1, 5, 2, 5, 6, 9, 7, 8};
	mergeInsertionSort(c);
	for (int i: c)
	{
		std::cout << i << " " ;
	}
	std::cout << std::endl;
	return 0;
}
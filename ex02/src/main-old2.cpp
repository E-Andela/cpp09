#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>

struct Element
{
	int value;
	int pairIndex;
};

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
	const std::vector<Element> &v,
	Element value,
	size_t left,
	size_t right)
{
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (value.value < v[mid].value)
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

void mergeInsertionSort(std::vector<Element> &c)
{
	if (c.size() <= 1)
		return;

	std::vector<std::pair<Element, Element>> pairs;
	std::vector<Element> larger;
	std::vector<Element> smaller;

	for (size_t i = 0; i + 1 < c.size(); i += 2)
	{
		Element a = c[i];
		Element b = c[i + 1];
		if (a.value < b.value)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
		larger.push_back(Element{a.value, (int)pairs.size() - 1});
	}

	bool hasLeftover = (c.size() % 2 != 0);
	Element leftover = hasLeftover ? c.back() : Element{0, -1};

	if (hasLeftover)
	{
		std::cout << "Leftover element: " << leftover.value << std::endl;
	}

	mergeInsertionSort(larger);
	
	// Rebuild smaller in the same order as larger was sorted
	smaller.clear();
	for (Element i: larger)
	{
		smaller.push_back(pairs[i.pairIndex].second);
	}
	
	std::vector<int> order = calculateInsertionOrder(smaller.size());

	// for (size_t i = 0; i < order.size(); ++i)
	// {
	// 	int idx = order[i] - 1;
	// 	Element value = smaller[idx];
	// 	size_t pos = boundedLowerBound(larger, value, 0, idx);
	// 	larger.insert(larger.begin() + pos, value);
	// }

	// if (hasLeftover)
	// {
	// 	size_t pos = boundedLowerBound(larger, leftover, 0, larger.size());
	// 	larger.insert(larger.begin() + pos, leftover);
	// }

	// c = larger;
}

int main()
{
	std::vector<Element> c = {{3, -1}, {2, -1}, {1, -1}, {8, -1}, {6, -1}, {7, -1}, {5, -1}, {4, -1}};
	mergeInsertionSort(c);
	for (Element i: c)
	{
		std::cout << i.value << " " ;
	}
	std::cout << std::endl;
	return 0;
}
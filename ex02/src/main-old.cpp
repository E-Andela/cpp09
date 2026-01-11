#include <vector>
#include <string>
#include <iostream>
#include <chrono>

void mergeInsertionSort(std::vector<int> &c, int iteration)
{
	if (c.size() <= 1)
        return;

    std::vector<std::pair<int, int>> pairs;
    std::vector<int> larger;
    std::vector<int> smaller;

    // 1️⃣ Create pairs (bigger first)
    for (size_t i = 0; i + 1 < c.size(); i += 2)
    {
        int a = c[i];
        int b = c[i + 1];
		// std::cout << "Iteration " << iteration << ": comparing " << a << " and " << b << std::endl;
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
        larger.push_backa);
        smaller.push_back(b);
    }
	std::cout << "Iteration " << iteration << ": larger half : ";
	for (const auto &p : larger)
		std::cout << p << " ";
	std::cout << std::endl;

	// std::cout << "Iteration " << iteration << ": smaller half: ";
	// for (const auto &p : smaller)
	// 	std::cout << p << " ";
	// std::cout << std::endl;

    // 2️⃣ Handle leftover element if odd
    bool hasLeftover = (c.size() % 2 != 0);
    int leftover = hasLeftover ? c.back() : 0;
	if (hasLeftover)
		std::cout << "Iteration " << iteration << ": leftover element " << leftover << std::endl;

    // 3️⃣ Recursively sort the 'larger' half
    mergeInsertionSort(larger, iteration + 1);
	
	// std::cout << "Iteration " << iteration << ": larger half : ";
	// for (const auto &p : larger)
	// 	std::cout << p << " ";
	// std::cout << std::endl;

	std::cout << "Iteration " << iteration << ": smaller half: ";
	for (const auto &p : smaller)
		std::cout << p << " ";
	std::cout << std::endl;

	std::cout << "Iteration " << iteration << ": pairs: " ;
	for (const auto &p : pairs)
		std::cout << "(" << p.first << ", " << p.second << ") ";
	std::cout << std::endl;

    // 4️⃣ Insert the smaller ones (and leftover if present)
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        int value = smaller[i];
        auto pos = std::lower_bound(larger.begin(), larger.end(), value);
        larger.insert(pos, value);
    }

    if (hasLeftover)
    {
        auto pos = std::lower_bound(larger.begin(), larger.end(), leftover);
        larger.insert(pos, leftover);
    }

	// size_t prev = 0;
	// size_t next = 0;



    // 5️⃣ Copy back the result to 'c'
    c = larger;

	std::cout << "Iteration " << iteration << ": c: ";
	for (const auto &p : c)
		std::cout << p << " ";
	std::cout << std::endl;
}

void insertAtIndex(const std::vector<int> &src, std::vector<int> &dest, size_t stepSize, int destIndex, int srcIndex)
{
	int start = static_cast<int>(srcIndex * stepSize + (stepSize - 1));
	int end = static_cast<int>(stepSize * srcIndex);
	for (int i = start; i >= end; --i)
	{
		dest.insert(dest.begin() + destIndex * stepSize, src[i]);
	}
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

void insertion(std::vector<int> &c, size_t stepSize)
{
	if (c.size() < 0)
		return ;
	std::cout << "Insertion with step size " << stepSize << std::endl;

	int inserts = c.size() / (stepSize * 2);
	
	std::cout << inserts << " numbers to insert" << std::endl;

	std::vector<int> main;
	std::vector<int> insertOrder = calculateInsertionOrder(inserts);

	
	
	// for (size_t i = 0; i < c.size(); i++)
	// {
	// 	std::cout << c[i] << " ";
	// }

	std::cout << "main: " ;

	for (size_t i = 0; i < c.size(); i += stepSize * 2)
	{
		for (size_t j = 0; j < stepSize; j++)
		{	
			main.push_back(c[i + j]);
			std::cout << c[i + j] << " ";
		}
	}
	std::cout << std::endl;
	
	// swap index 0 and 1 for free
	for (size_t i = (stepSize * 2) - 1; i >= stepSize ; i--)
	{
		std::cout << "i: " << i << std::endl;
		// std::swap(c[i], c[i + stepSize]);
		main.insert(main.begin(), c[i]);
	}

	for (int i = 1; i <= inserts; i++)
	{
		int destIndex;
		int srcIndex = insertOrder[i];
		if (i == 1)
		{
			destIndex = 0;
		}
		else
		{
			destIndex = binarySearch(main, c[srcIndex], 0, srcIndex, stepSize);
		}
		insertAtIndex(c, main, stepSize, destIndex, srcIndex);
	}

	std::cout << "main after swap: " ;
	for (size_t i = 0; i < main.size(); i++)
	{
		std::cout << main[i] << " " ;
	}

	std::cout << std::endl;

}

void mergeInsertionSort2(std::vector<int> &c, int iteration)
{
	size_t stepSize = 1 << (iteration - 1);
	size_t pairSize = stepSize * 2;
	size_t amountOfPairs = c.size() / pairSize;
	
	std::cout << "Iteration: " << iteration << std::endl;
	std::cout << "c size: " << c.size() << std::endl;
	std::cout << "step size: " << stepSize << std::endl;

	for (size_t i = 0; (i + stepSize) < c.size(); i += (stepSize * 2))
	{
		int a = c[i];
		int b = c[i + stepSize];
		size_t bIndex = (i + stepSize);
		if (a < b)
		{
			for (size_t j = i; j < bIndex; j++)
			{
				std::swap(c[j], c[j + stepSize]);
			}
		}
	}

	for (size_t i = 0; i < c.size(); i++)
	{
		std::cout << c[i] << " ";
	}

	std::cout << std::endl;

	if (amountOfPairs > 1)
		mergeInsertionSort2(c, iteration + 1);
	// insertion(c, stepSize);
}

int main()
{
	std::vector<int> c = {3, 2, 1, 8, 6, 7, 5, 4};
	for (size_t i = 0; i < c.size(); ++i)
	{
		std::cout << c[i] << " " ;
	}
	std::cout << std::endl;

	mergeInsertionSort2(c, 1);

	for (size_t i = 0; i < c.size(); ++i)
	{
		std::cout << c[i] << " " ;
	}
	std::cout << std::endl;

	return 0;

}
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
        larger.push_back(a);
        smaller.push_back(b);
    }
	std::cout << "Iteration " << iteration << ": larger half: ";
	for (const auto &p : larger)
		std::cout << p << " ";
	std::cout << std::endl;

	std::cout << "Iteration " << iteration << ": smaller half: ";
	for (const auto &p : smaller)
		std::cout << p << " ";
	std::cout << std::endl;

    // 2️⃣ Handle leftover element if odd
    bool hasLeftover = (c.size() % 2 != 0);
    int leftover = hasLeftover ? c.back() : 0;
	if (hasLeftover)
		std::cout << "Iteration " << iteration << ": leftover element " << leftover << std::endl;

    // 3️⃣ Recursively sort the 'larger' half
    mergeInsertionSort(larger, iteration + 1);
	
	std::cout << "Iteration " << iteration << ": larger half: ";
	for (const auto &p : larger)
		std::cout << p << " ";
	std::cout << std::endl;

	std::cout << "Iteration " << iteration << ": smaller half: ";
	for (const auto &p : smaller)
		std::cout << p << " ";
	std::cout << std::endl;

    // 4️⃣ Insert the smaller ones (and leftover if present)
    // for now, we’ll just merge them sequentially for testing
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

    // 5️⃣ Copy back the result to 'c'
    c = larger;
}

int main(int argc, char **argv)
{
	std::vector<int> c;

	try
	{
		if (argc >= 2)
		{
			for (int i = 1; i < argc; i++)
			{
				c.push_back(std::stoi(argv[i]));
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}

	auto start = std::chrono::high_resolution_clock::now();
	mergeInsertionSort(c, 1);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Sorting took " << duration.count() << " milliseconds." << std::endl;

	// for (size_t i = 0; i < c.size(); i++)
	// {
	// 	std::cout << c[i] << " ";
	// }
	// std::cout << std::endl;
}
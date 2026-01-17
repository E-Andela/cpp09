#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cerrno>
#include <climits>

long long parsePositiveInteger(const std::string &str)
{
	char *end = nullptr;
	errno = 0;
	long long value = std::strtoll(str.c_str(), &end, 10);
	
	if (errno == ERANGE || value <= 0 || *end != '\0')
		throw std::invalid_argument("invalid positive integer");
	
	return value;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<long long> input;
	try
	{
		for (int i = 1; i < argc; ++i)
		{
			input.push_back(parsePositiveInteger(argv[i]));
		}
	}
	catch (const std::exception &)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	// Display input
	std::cout << "Before: ";
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (i > 0) std::cout << " ";
		std::cout << input[i];
	}
	std::cout << std::endl;

	// Sort using vector
	std::vector<long long> vecCopy = input;
	auto start = std::chrono::high_resolution_clock::now();
	mergeInsertionSortVector(vecCopy, 0);
	auto end = std::chrono::high_resolution_clock::now();
	double vecTime = std::chrono::duration<double, std::micro>(end - start).count();

	// Sort using deque
	std::deque<long long> deqCopy(input.begin(), input.end());
	start = std::chrono::high_resolution_clock::now();
	mergeInsertionSortDeque(deqCopy, 0);
	end = std::chrono::high_resolution_clock::now();
	double deqTime = std::chrono::duration<double, std::micro>(end - start).count();

	// Display output
	std::cout << "After:  ";
	for (size_t i = 0; i < vecCopy.size(); ++i)
	{
		if (i > 0) std::cout << " ";
		std::cout << vecCopy[i];
	}
	std::cout << std::endl;

	// Display timing with precision
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << input.size() << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << input.size() << " elements with std::deque  : " << deqTime << " us" << std::endl;

	return 0;
}
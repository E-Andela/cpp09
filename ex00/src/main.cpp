#include "../inc/BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	BitcoinExchange wallet(argv[1]);

	try
	{
		wallet.parseData();
		wallet.parseInput();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
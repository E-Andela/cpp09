#include "../inc/BitcoinExchange.hpp"
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange() : m_dataPath {"data.csv"}
{

}

void BitcoinExchange::parseData()
{
	std::fstream data(m_dataPath);
	std::string line;
	int i = 0;

	while(std::getline(data, line))
	{
		if (i >= 1)
		{
			size_t pos = line.find(',');
			std::string date = line.substr(0, pos);
			std::string valueString = line.substr(pos + 1);
			double value = std::stod(valueString);

			m_exchangeRates.insert({date, value});
		}
		++i;
	}

	for (const auto& pair : m_exchangeRates)
	{
		std::cout << pair.first << " => " << pair.second << std::endl;
	}
}
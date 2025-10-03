#include "../inc/BitcoinExchange.hpp"
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange() : m_dataPath {"data.csv"}, m_inputPath {"input.txt"}
{

}

BitcoinExchange::BitcoinExchange(std::string inputFile) : m_dataPath {"data.csv"}, m_inputPath {inputFile}
{

}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : m_exchangeRates(other.m_exchangeRates), m_dataPath(other.m_dataPath), m_inputPath(other.m_inputPath)
{

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		m_exchangeRates = other.m_exchangeRates;
		m_dataPath = other.m_dataPath;
		m_inputPath = other.m_inputPath;
	}
	return *this;
}

void BitcoinExchange::parseData()
{
	std::fstream data(m_dataPath);
	if (!data.is_open())
	{
		throw std::runtime_error("Error: could not open data file.");
	}
	std::string line;
	int i = 0;

	while(std::getline(data, line))
	{
		if (i >= 1)
		{
			size_t pos = line.find(',');
			if (pos == std::string::npos)
				throw std::runtime_error("Error: could not parse data file.");
			std::string date = line.substr(0, pos);
			if (!isValidDate(date))
			{
				throw std::runtime_error("Error: invalid date in data file.");
			}
			std::string valueString = line.substr(pos + 1);
			double value = std::stod(valueString);

			m_exchangeRates.insert({date, value});
		}
		++i;
	}
}

void BitcoinExchange::parseInput()
{
	std::fstream input(m_inputPath);
	if (!input.is_open())
	{
		throw std::runtime_error("Error: could not open input file.");
	}
	std::string line;
	int i = 0;

	while (std::getline(input, line))
	{
		if (i >= 1)
		{
			size_t pos = line.find(" | ");
			if (std::string::npos == pos)
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}
			std::string date = line.substr(0, pos);
			if (!isValidDate(date))
			{
				std::cout << "Error: bad date => " << line << std::endl;
				continue;
			}
			std::string valueString = line.substr(pos + 3);
			double value;
			try
			{
				value = std::stod(valueString);
			}
			catch(const std::exception& e)
			{
				std::cout << "Error: not a number => " << line << std::endl;
				continue;
			}			
			if (value > 1000)
			{
				std::cout << "Error: too large a number => " << line << std::endl;
				continue;
			}
			if (value < 0)
			{
				std::cout << "Error: not a positive number => " << line << std::endl;
				continue;
			}
			// here we have a valid value and a valid date
			std::cout << date << " => " << value << " = " << value * valueAtDate(date) << std::endl;
		}
		++i;
	}
}

bool BitcoinExchange::isValidDate(std::string date)
{
	if (date.length() != 10)
		return false;	
	if (date[4] != '-' || date[7] != '-')
		return false;

	int year;
	int month;
	int day;

	try
	{	
		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
	}
	catch (const std::exception&)
	{
		return false;
	}

	if (month > 12 || month < 1)
		return false;
	if (day < 1)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		daysInMonth[1] = 29;
	
	if (day > daysInMonth[month - 1])
		return false;
	return true;
}

double BitcoinExchange::valueAtDate(std::string date)
{
	double value = 0;
	for (const auto& pair : m_exchangeRates)
	{
		if (date < pair.first)
			break;
		value = pair.second;
	}
	return (value);
}
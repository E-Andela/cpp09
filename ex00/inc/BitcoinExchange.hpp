#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double> m_exchangeRates;
	std::string	m_dataPath;
	std::string m_inputPath;

public:
	BitcoinExchange();
	BitcoinExchange(std::string inputFile);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);

	void parseData();
	void parseInput();

private:
	bool isValidDate(std::string date);
	double valueAtDate(std::string date);
};

#endif
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double> m_exchangeRates;
	std::string	m_dataPath;

public:
	BitcoinExchange();
	void parseData();
};
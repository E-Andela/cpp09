#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
private:
	std::stack<int> m_numbers;

	void add();
	void subtract();
	void multiply();
	void divide();

public:
	RPN();
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);

	int evaluate(std::string expression);
};

#endif
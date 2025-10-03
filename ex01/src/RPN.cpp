#include "../inc/RPN.hpp"
#include <stdexcept>

RPN::RPN() { }

RPN::~RPN() { }

RPN::RPN(const RPN& other) : m_numbers {other.m_numbers} { }

RPN& RPN::operator=(const RPN& other)
{
	m_numbers = other.m_numbers;
	return *this;
}

void RPN::add()
{
	if (m_numbers.size() < 2)
		throw std::runtime_error("Error: not enough numbers in the stack to perform addition.");
	int a = m_numbers.top();
	m_numbers.pop();
	int b = m_numbers.top();
	m_numbers.pop();

	m_numbers.push(a + b);
}

void RPN::subtract()
{
	if (m_numbers.size() < 2)
		throw std::runtime_error("Error: not enough numbers in the stack to perform subtraction.");
	int a = m_numbers.top();
	m_numbers.pop();
	int b = m_numbers.top();
	m_numbers.pop();

	m_numbers.push(b - a);
}

void RPN::multiply()
{
	if (m_numbers.size() < 2)
		throw std::runtime_error("Error: not enough numbers in the stack to perform multiplication.");
	int a = m_numbers.top();
	m_numbers.pop();
	int b = m_numbers.top();
	m_numbers.pop();

	m_numbers.push(a * b);
}

void RPN::divide()
{
	if (m_numbers.size() < 2)
		throw std::runtime_error("Error: not enough numbers in the stack to perform division.");
	int a = m_numbers.top();
	m_numbers.pop();
	if (a == 0)
		throw std::runtime_error("Error: division by zero.");
	int b = m_numbers.top();
	m_numbers.pop();

	m_numbers.push(b / a);
}

int RPN::evaluate(std::string expression)
{
	for (size_t i = 0; i < expression.length(); ++i)
	{
		if (expression[i] == ' ')
			continue;
		else if (expression[i] >= '0' && expression[i] <= '9')
		{
			m_numbers.push(expression[i] - '0');
		}
		else if (expression[i] == '+')
		{
			add();
		}
		else if (expression[i] == '-')
		{
			subtract();
		}
		else if (expression[i] == '*')
		{
			multiply();
		}
		else if (expression[i] == '/')
		{
			divide();
		}
		else
		{
			throw std::runtime_error("Error: invalid character in expression.");
		}
	}
	if (m_numbers.size() != 1)
		throw std::runtime_error("Error: invalid expression.");
	int result = m_numbers.top();
	m_numbers.pop();
	return result;
}
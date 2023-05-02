/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:57:50 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 12:35:47 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(std::string input)
{
	_checkInput(input);
	_calculate(input);
}

RPN::RPN(RPN &src)
{
	this->_calculator = src._calculator;
}

RPN::~RPN(void) {}

RPN	&RPN::operator=(RPN &src)
{
	this->_calculator = src._calculator;
	return (*this);
}

int	RPN::getResult(void)
{
	_checkCalculatorValidity();
	return (_calculator.top());
}

void	RPN::_calculate(std::string &input)
{
	while (1)
	{
		try
		{
			std::string	elem = _getNextElement(input);
			_handleElement(elem);
		}
		catch (RPN::EndOfInputException &e)
		{
			break;
		}
	}
}

void	RPN::_handleElement(std::string &element)
{
	if (_isOperator(element))
		_handleOperator(element);

	else if (_isOperand(element))
		_handleOperand(element);
}

void	RPN::_handleOperand(std::string &element)
{
	int	operand = std::atoi(element.c_str());
	_calculator.push(operand);
}

void	RPN::_handleOperator(std::string &element)
{
	int	second = _getNextOperand();
	int	first = _getNextOperand();
	int	res = _calculateResult(element, first, second);

	_calculator.push(res);
}

// Obtient le prochain opérande à traiter dans le calcul de la NPI
int RPN::_getNextOperand(void)
{
	if (_calculator.empty())
		throw (std::out_of_range("invalid input: missing operands for operator"));

	int operand = _calculator.top(); // on récupère l'opérande situé au sommet de la pile
	_calculator.pop(); // on le retire du sommet de la pile

	return (operand);
}

int	RPN::_calculateResult(std::string &operation, int first, int second)
{
	int	res = 0;

	switch (operation[0])
	{
		case '+':
			res = first + second;
			break;
		case '-':
			res = first - second;
			break;
		case '*':
			res = first * second;
			break;
		case '/':
			res = first / second;
			break;
		default:
			throw (std::runtime_error(operation + ": invalid operator !"));
	}

	return (res);
}

bool	RPN::_isOperand(std::string &string) const
{
	std::string::iterator	it = string.begin();

	for ( ; it != string.end(); it++)
	{
		if (it != string.begin() && !std::isdigit(*it))
			return (false);
	}
	return (true);
}

bool	RPN::_isOperator(std::string &string) const
{
	std::string	operators = "+-*/";
	size_t		pos = string.find_first_not_of(operators, 0);
	
	if (pos == std::string::npos && string.length() == 1)
		return (true);

	return (false);
}

// Extrait et retourne le prochain élément (chiffre/opérateur) de l'input
std::string	RPN::_getNextElement(std::string &input)
{
	// static pour conserver sa position dans la string entrée
	// entre les appels successifs de _getNextElement()
	static	std::string::iterator it = input.begin();

	for ( ; it != input.end(); it++)
	{
		if (*it == ' ')
			continue;

		std::string	elem = std::string(1, *it);
		it++;

		return (elem);
	}

	throw (RPN::EndOfInputException());
}

void	RPN::_checkInput(std::string &input)
{
	std::string	requiredDigits = "0123456789";
	std::string	requiredOperators = "+-*/";
	std::string	allowed = requiredDigits + requiredOperators + " ";

	size_t	pos = input.find_first_not_of(allowed, 0);

	if (pos != std::string::npos)
		throw (std::out_of_range ("invalid input: can only contain " + allowed));

	pos = input.find_first_of(requiredDigits, 0);

	if (pos == std::string::npos)
		throw (std::out_of_range ("invalid input: requires at least one of " + requiredDigits));

	pos = input.find_first_of(requiredOperators, 0);

	if (pos == std::string::npos)
		throw (std::out_of_range ("invalid input: requires at least one of " + requiredOperators));
}

void	RPN::_checkCalculatorValidity(void)
{
	if (_calculator.size() != 1)
		throw (std::out_of_range("invalid input: missing operator(s)"));
}

const char	*RPN::EndOfInputException::what(void) const throw()
{
	return ("end of input");
}
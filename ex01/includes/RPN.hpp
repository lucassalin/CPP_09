/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:57:53 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 11:50:27 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_POLISH_NOTATION_HPP
#define REVERSE_POLISH_NOTATION_HPP

#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class RPN
{
	private:
		std::stack<int>	_calculator;

		void		_calculate(std::string &input);
		std::string	_getNextElement(std::string &input);
		void		_handleElement(std::string &element);
		void		_handleOperand(std::string &element);
		void		_handleOperator(std::string &element);
		int			_getNextOperand(void);
		int			_calculateResult(std::string &operation, int first, int second);

		bool		_isOperand(std::string &string) const;
		bool		_isOperator(std::string &string) const;

		void		_checkInput(std::string &input);
		void		_checkCalculatorValidity(void);

		std::string	_getCalculatorContentsAsString(void);

		RPN(void);

	public:
		RPN(std::string input);
		RPN(RPN &src);
		~RPN(void);

		RPN &operator=(RPN &src);

		int	getResult(void);

		class EndOfInputException : public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};
};

#endif
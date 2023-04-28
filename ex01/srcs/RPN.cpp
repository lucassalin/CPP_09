/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:57:50 by lsalin            #+#    #+#             */
/*   Updated: 2023/04/28 22:16:32 by lsalin           ###   ########.fr       */
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


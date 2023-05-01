/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:37:34 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/01 14:15:08 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &origin)
{
	*this = origin; 
}

PmergeMe    &PmergeMe::operator=(const PmergeMe &origin)
{
	this->_vector = origin._vector;
	this->_deque = origin._deque;
	
	return (*this);
}

void	PmergeMe::printVector()
{
	int i = 0;

	for (std::vector<int>::iterator it = _vector.begin(); it < _vector.end(); it++)
	{
		if (++i > 8)
		{
			std::cout << " [...]";
			break;
		}
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void	PmergeMe::printDeque()
{
	int i = 0;

	for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++)
	{
		if (++i > 8)
		{
			std::cout << " [...]";
			break;
		}
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void	is_Num(char *tab)
{
	std::string	str = tab;

	if (str[0] == '-')
		throw "Error: not a positive number.";

	if (str.length() > 10 || (str.length() == 10 && str > "2147483647"))
		throw "Error: too large a number.";

	if (!str.empty() && str.find_first_not_of("0123456789") != std::string::npos)
		throw "Error: not a number.";
}

void	PmergeMe::ft_sort(char **tab)
{
	std::clock_t	start;
	std::clock_t	end;
	double			Vtime;	// temps ecoule de l'execution du vecteur
	double			Dtime;	// temps ecoule de l'execution du deque
	int				i = 1;
	int				nb = 0;

	// parcourt les arguments du programme
	while (tab[i])
	{
		is_Num(tab[i]);
		std::istringstream(tab[i]) >> nb; // convertit la string en int

		_vector.push_back(nb);
		_deque.push_back(nb);

		i++;
	}

	std::cout << "Before :";
	printVector();

	start = clock();
	merge_sort(_vector, 0, _vector.size() - 1);
	end = clock();
	Vtime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;

	start = clock();
	merge_sort(_deque, 0, _vector.size() - 1);
	end = clock();
	Dtime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;

	std::cout << "After :";
	printVector();
	//printDeque();

	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Time to process a range of "<< _vector.size() <<  " elements with std::vector : " << Vtime << " ms\n";
	std::cout << "Time to process a range of "<< _deque.size() <<  " elements with std::deque : " << Dtime << " ms\n";
}
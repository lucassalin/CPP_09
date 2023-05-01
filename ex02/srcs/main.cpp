/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:37:44 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/01 14:06:39 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	try
	{
		if (ac < 2)
			throw "Error: not the right number of arguments.";

		PmergeMe test;
		test.ft_sort(av);
	}
 	catch (const char *str)
 	{
 		std::cerr << str << '\n';
 	}
}

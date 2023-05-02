/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:01:05 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 11:49:06 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./RPN [reverse Polish notation expression]" << std::endl;
		return (1);
	}

	try
	{
		RPN	rpn((std::string(av[1])));
		int res = rpn.getResult();

		std::cout << res << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return (0);
}
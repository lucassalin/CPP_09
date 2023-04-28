/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:05:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/04/28 12:40:25 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Retourne true si la string est vide/ne contient que des caractères d'espacement
// Retourne false si elle contient au moins 1 caractère

bool	isStringEmpty(std::string string)
{
	if (string.empty())
		return (true);
		
	std::string::iterator	it = string.begin();
	
	for ( ; it != string.end(); it++)
	{
		if (!isblank(*it))
			return (false);
	}
	return (true);
}


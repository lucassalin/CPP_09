/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:37:36 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 14:14:34 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_H
#define PMERGEME_H

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &origin);
		PmergeMe	&operator=(const PmergeMe &origin);
		~PmergeMe();

		void	ft_sort(char **tab);
		void	printVector();
		void	printDeque();

		// merge_sort() divise récursivement le tableau initial en sous-tableaux triés
		// merge() fusionne ces sous-tableaux triés récursivement jusqu'à obtenir le tableau initial trié
		// @param lst : reference a un container (vector ou deque) contenant les éléments a trier

		template< typename T >
		void	merge_sort(T &lst, int beg, int end)
		{
			int	mid;

			if (beg < end)  
			{
				mid = (beg + end) / 2;

				merge_sort(lst, beg, mid);
				merge_sort(lst, mid + 1, end);
				merge(lst, beg, mid, end);
			}
		}

		// Fusionne deux sous-tableaux tries adjacents
		// 1er sous-tableau : left-mid
		// 2e sous-tableau	: mid-right

		template< typename T >
		void	merge(T &lst, int left, int mid, int right)
		{
			std::vector<int>	temp(right - left + 1); // stocke temporairement les elements fusionnes
			int					i = left;				// premier element du premier sous-tableau
			int					j = mid + 1; 			// premier element du deuxieme sous-tableau
			int					k = 0;					// index pour inserer des elements dans temp

			/**
				@example lst = [5, 3, 1, 4, 2]

				1er sous-tableau : [1, 3, 5]
				2e sous-tableau : [2, 4]
				
			*/

			// Compare les éléments des deux sous-tableaux
			// Et les insère dans tmp dans l'ordre croissant

			while (i <= mid && j <= right)
			{
				if (lst[i] <= lst[j])
					temp[k++] = lst[i++];
				else
					temp[k++] = lst[j++];
			}

			// Copie les elements restants du premier sous-tableau (left-mid) dans tmp
			// Arrive si des elements du 2e sous-tableau sont < aux elements restants du premier sous-tableau

			while (i <= mid)
				temp[k++] = lst[i++];

			while (j <= right)
				temp[k++] = lst[j++];

			for (int p = 0; p < k; p++)
				lst[left + p] = temp[p];
		}
};

#endif
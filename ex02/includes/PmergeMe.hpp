/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:37:36 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/01 14:07:03 by lsalin           ###   ########.fr       */
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

		// Implementation de l'algo de tri par fusion
		// @param lst : reference a un container (vector ou deque) contenant les elements a trier

		template< typename T >
		void	merge_sort(T &lst, int beg, int end)
		{
			int	mid;

			if (beg < end)  
			{
				mid = (beg + end) / 2;

				merge_sort(lst, beg, mid); // tri recursif de la premiere moitie du tableau initial
				merge_sort(lst, mid + 1, end); // deuxieme moitie
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
				@example lst = [3, 5, 8, 9, 1, 4, 6, 7]
				
				left = 0
				right = 7
				mid = 3

				1er sous-tableau : [3, 5, 8, 9]
				2e sous-tableau	 : [1, 4, 6, 7]

				- i = 0 (pointe sur 2)
				- j = 4 (pointe sur 1)
				- k = 0
			*/

			// Fusionne les elements des deux sous-tableaux
			// Et les copie de facon croissante dans tmp
			// S'arrete lorsque l'un des deux sous-tableaux est copie trie dans tmp

			while (i <= mid && j <= right)
			{
				if (lst[i] <= lst[j]) // si 2 < 1
					temp[k++] = lst[i++];
				else
					temp[k++] = lst[j++];
			}
			
			// temp = [1, 3, 4, 5]

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
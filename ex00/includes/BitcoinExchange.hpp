/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:05:44 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 11:27:31 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#define BONUS 1
#define DATE 0
#define VALUE 1

#include <cstdlib>
#include <cctype>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <strings.h>
#include <sys/stat.h>

class BitcoinExchange
{
	private:
		std::map<time_t, double>	_exchangeRate;

		void				_fillExchangeRateTable(void);
		void				_fillExchangeRateEntry(std::string line);
		void				_addExchangeRateEntry(time_t date, double value);
		time_t				_getClosestDateInTable(time_t date);
		double				_getExchangeRateOnDate(time_t date);

		time_t				_getEpochFromDateString(std::string &date) const;
		int					_getYearFromString(std::string &dateStr) const;
		int					_getMonthFromString(std::string &dateStr) const;
		int					_getDayFromString(std::string &dateStr) const;
		std::string const	_getDateFromEpoch(time_t epochDate) const;
		double 				_getValueFromString(std::string &valueStr) const;

		void				_checkInputStrings(std::string &dateStr, std::string &valueStr) const;
		void 				_checkValueString(std::string &string) const;
		void 				_checkDateString(std::string &string) const;
		void 				_checkDayString(std::string &string) const;

		void 				_printClosestExchangeRate(time_t date);

	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange &src);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(BitcoinExchange &src);

		void			outputExchangeValueOnDate(std::string &date, std::string &value);
		double			getExchangeValueOnDate(std::string &date, std::string &value);

};

std::string	*splitString(std::string string, std::string sep);
bool		isStringEmpty(std::string string);

#endif

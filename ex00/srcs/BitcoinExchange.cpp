/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:06:00 by lsalin            #+#    #+#             */
/*   Updated: 2023/04/28 21:50:15 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void)
{
	try
	{
		_fillExchangeRateTable();
	}
	catch ( std::exception &e )
	{
		std::string	error = e.what();
		throw (std::runtime_error("Invalid exchange rate data: " + error));
	}
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &src)
{
	this->_exchangeRate = src._exchangeRate;
}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &src)
{
	this->_exchangeRate = src._exchangeRate;
	return (*this);
}

// Lit les donnees du .csv et les ajoutent a la map _exchangeRate
void	BitcoinExchange::_fillExchangeRateTable(void)
{
	std::fstream	fs;
	fs.open("data/data.csv", std::fstream::in);

	if (fs.fail())
		throw (std::runtime_error("Could not open data file"));

	char	line[100];
	fs.getline(line, 100);
	
	while (!fs.eof())
	{
		char	line[100];
		fs.getline(line, 100);

		if (!fs.eof() && line[0] != '\0')
			_fillExchangeRateEntry(std::string(line));
	}
}

// Traite les donnes du .csv et ajoute les taux de change a la map _exchangeRate
// 2009-01-02,0

void	BitcoinExchange::_fillExchangeRateEntry(std::string line)
{
	std::string	*split = splitString(line, ",");

	_checkDateString(split[DATE]);
	_checkValueString(split[VALUE]);

	time_t	date = _getEpochFromDateString(split[DATE]);
	double	value = _getValueFromString(split[VALUE]);

	_addExchangeRateEntry(date, value);
	delete [] (split);
}

// Ajoute une date et une valeur a la map _exchangeRate
void	BitcoinExchange::_addExchangeRateEntry(time_t date, double value)
{
	std::map<time_t, double>::iterator	it = _exchangeRate.find(date);

	if (it != _exchangeRate.end())
		it->second = value;

	else
		_exchangeRate.insert(std::pair<time_t, double>(date, value));
}

// [2012-01-11] 1.00 * 7.10 = 7.10
void	BitcoinExchange::outputExchangeValueOnDate( std::string &dateStr, std::string &valueStr )
{
	_checkInputStrings(dateStr, valueStr);

	time_t	date = _getEpochFromDateString(dateStr);
	double	value = _getValueFromString(valueStr);
	double	exchangeRate = _getExchangeRateOnDate(date);
	double	exchangeValue = getExchangeValueOnDate(dateStr, valueStr);

	if (VERBOSE)
		_printClosestExchangeRate(date);

	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << "[" << _getDateFromEpoch(date) << "] " << value << " * ";
	std::cout << exchangeRate << " = " << exchangeValue << std::endl;
}

// Affiche le taux de change le plus proche de la date donnée
void	BitcoinExchange::_printClosestExchangeRate(time_t date)
{
	time_t		closestEpoch = _getClosestDateInTable(date);
	std::string	closestDate = _getDateFromEpoch(closestEpoch);

	std::cout << YELLOW << "Closest exchange data: " << closestDate << " -> ";

	std::cout << std::fixed; // précision de 2 décimales
	std::cout.precision(2);
	
	std::cout << _exchangeRate[closestEpoch] << RESET << std::endl;
}

// Retourne la valeur du bitcoin multipliée par son taux de change à la date donnée
// Si la date n'existe pas dans la DB, on utilise la plus proche inférieurement

double	BitcoinExchange::getExchangeValueOnDate(std::string &dateStr, std::string &valueStr)
{
	_checkInputStrings(dateStr, valueStr);

	double	rate = _getExchangeRateOnDate(_getEpochFromDateString(dateStr));
	double	value = _getValueFromString(valueStr);

	return (value * rate);
}

// Retourne le taux de change le plus proche pour la date donnée
double	BitcoinExchange::_getExchangeRateOnDate(time_t date)
{
	time_t	closestDate = _getClosestDateInTable(date);

	return (_exchangeRate[closestDate]);
}

/**
	@brief Cherche la date du taux de change le plus proche de la date fournie
	
	@param date : date pour laquelle on souhaite obtenir le taux de change le plus proche (sujet)
				  si elle n'existe pas dans la DB, on prends la plus proche (inférieure et non supérieure !)

	@return time_t : date la plus proche trouvée en temps Epoch

	@example _exchangeRate = 
								10 avril 2023
								12 avril 2023
								13 avril 2023
								15 avril 2023
								18 avril 2023

			On veut obtenir le taux de change du 14 avril 2023
			1) Conversion en temps Epoch (s)
			2) 14 avril 2023 n'est pas présent dans la table
			2) 14 avril 2023 n'est pas antérieure au 10 avril 2023
			3) Soustrait de 1 jour (86400s) la date fournie, à chaque tour de boucle
			   Jusqu'à trouver la date la plus proche inférieurement (13 avril 2023 ici)
 */

time_t	BitcoinExchange::_getClosestDateInTable(time_t date)
{
	// on check si la date recherchée est présente dans la map
	// si oui, it pointe directement dessus
	std::map<time_t, double>::iterator	it = _exchangeRate.find(date);

	// si la date recherchée est antérieure à la première date de la table des taux de change
	// --> on la retourne (car c'est la plus proche de la date recherchée)

	if (date < _exchangeRate.begin()->first)
		return (_exchangeRate.begin()->first);

	// Sinon, on recherche la date la plus proche
	
	for (int i = 0; it == _exchangeRate.end(); i++)
	{
		time_t	newDate = date - i * 24 * 60 * 60; // 24 x 60 x 60 = nombre de s dans 1 journée
		it = _exchangeRate.find(newDate);
	}

	return (it->first);
}

/**
	@brief Convertit dateStr en temps Epoch
	
	@param dateStr : date au format "YYYY-MM-DD"
	
	@return time_t : nombre de secondes écoulées depuis le 01/01/1970
 */

time_t	BitcoinExchange::_getEpochFromDateString(std::string &dateStr) const
{
	struct tm	tm;
	bzero(&tm, sizeof(tm));

	tm.tm_year = _getYearFromString(dateStr) - 1900;
	tm.tm_mon = _getMonthFromString(dateStr) - 1;
	tm.tm_mday = _getDayFromString(dateStr);

	struct tm	copy; // utilisée pour vérifier la validité de la conversion en temps Epoch
	bzero(&copy, sizeof(copy));

	copy.tm_year = tm.tm_year;
	copy.tm_mon = tm.tm_mon;
	copy.tm_mday = tm.tm_mday;

	time_t	date = mktime(&tm); // mktime() renvoie (-1) si temps Epoch invalide

	if (date == -1 || copy.tm_year != tm.tm_year || copy.tm_mon != tm.tm_mon || copy.tm_mday != tm.tm_mday)
		throw (std::out_of_range(dateStr + ": invalid date"));

	return (date);
}

// Extrait l'année d'une date au format string (AAAA-MM-JJ)
// Et la retourne sous forme d'int

int	BitcoinExchange::_getYearFromString(std::string &dateStr) const
{
	size_t		lenYear = dateStr.find("-", 0);
	std::string	yearStr = dateStr.substr(0, lenYear);
	int			year = std::atoi(yearStr.c_str());

	if (yearStr.empty() || year < 0 || year > 2050)
		throw std::out_of_range(dateStr + ": invalid date");
	return (year);
}

// Extrait le mois d'une date au format string (AAAA-MM-JJ)
// Et le retourne sous forme d'int

int	BitcoinExchange::_getMonthFromString(std::string &dateStr) const
{
	size_t		lenYear = dateStr.find("-", 0) + 1;
	size_t		lenMon = dateStr.find("-", lenYear) - lenYear;
	std::string	monthStr = dateStr.substr(lenYear, lenMon);

	int	month = std::atoi(monthStr.c_str());

	if (monthStr.empty() || month < 1 || month > 12)
		throw std::out_of_range(dateStr + ": invalid date");
		
	return (month);
}

// Extrait le jour d'une date au format (AAAA-MM-JJ)
// Et la retourne sous forme d'int

int	BitcoinExchange::_getDayFromString(std::string &dateStr) const
{
	size_t		lenYear = dateStr.find ("-", 0) + 1;
	size_t		lenMon = dateStr.find("-", lenYear) + 1;
	size_t		lenDay = dateStr.length() - lenMon;
	std::string	dayStr = dateStr.substr(lenMon, lenDay);

	try
	{
		_checkDayString(dayStr);
	}
	catch (std::exception &e)
	{
		throw std::out_of_range(dateStr + ": invalid date");
	}

	int	day = std::atoi(dayStr.c_str());
	
	if (dayStr.empty() || day < 1 || day > 31)
		throw std::out_of_range( dateStr + ": invalid date");

	return (day);
}

// Convertit une date (temps Unix) en une string au format "YYYY-MM-DD"
// Epoch = mesure de temps en secondes écoulées depuis 01/01/1970

std::string const	BitcoinExchange::_getDateFromEpoch(time_t epochDate) const
{
	struct tm			*date = localtime(&epochDate);
	std::stringstream	ss;

	// string représentant l'année est ajoutée au flux (+1900 car tm stocke les années depuis 1900)
	ss << std::setfill('0') << std::setw(4) << date->tm_year + 1900;
	ss << "-" << std::setfill('0') << std::setw(2) << date->tm_mon + 1; // + 1 car tm compte les mois de 0 à 11
	ss << "-" << std::setfill('0') << std::setw(2) << date->tm_mday;

	return (ss.str());
}

// Convertit une string représentant un nombre en double
// Une valeur valide doit soit être un float soit être un int entre 0 et 1000

double	BitcoinExchange::_getValueFromString(std::string &valueStr) const
{
	double	value = std::strtod(valueStr.c_str(), NULL);

	if (value < 0)
		throw (std::out_of_range(valueStr + ": not a positive value"));

	else if (value > std::numeric_limits<int>::max())
		throw (std::out_of_range(valueStr + ": value too large"));

	return (value);
}

// Check si date/valeur valide ou non
void	BitcoinExchange::_checkInputStrings(std::string &dateStr, std::string &valueStr) const
{
	_checkDateString(dateStr);
	_checkValueString(valueStr);
}

// Check si la string représente une valeur possible du prix du Bitcoin
// Lève des exceptions sinon

void	BitcoinExchange::_checkValueString(std::string &string) const
{
	if (isStringEmpty(string) == true)
		throw (std::runtime_error("no value provided"));

	std::string	required = "0123456789";
	size_t		pos = string.find_first_of(required, 0);

	if (pos == std::string::npos)
		throw (std::runtime_error(string + ": invalid value"));

	std::string::iterator it = string.begin();

	for ( ; it != string.end(); it++)
	{
		if (std::isalpha(*it) || !std::isprint(*it))
			throw ( std::runtime_error(string + ": invalid value"));
	}
}

// Check si la string représente une date valide "Year-Month-Day"
// Lève une exception si c'est pas le cas

void	BitcoinExchange::_checkDateString(std::string &string) const
{
	if (isStringEmpty(string))
		throw (std::runtime_error("no date provided"));

	std::string	required = "0123456789-";
	// cherche la première occurence d'un caractère appartenant à required dans string
	size_t		pos = string.find_first_of(required, 0);
	
	if (pos == std::string::npos)
		throw (std::runtime_error(string + ": invalid date"));
		
	std::string::iterator	it = string.begin();
	
	for ( ; it != string.end(); it++)
	{
		if (std::isalpha(*it) || !std::isprint(*it))
			throw (std::runtime_error(string + ": invalid date"));
	}
}

// Check si la string ,représentant le jour d'une date, est valide
// Valide = ne contient que des chiffres ou des espaces
// Lève une exception si c'est pas le cas

void	BitcoinExchange::_checkDayString(std::string &string) const
{
	std::string::iterator	it = string.begin();

	for ( ; it != string.end(); it++)
	{
		if (std::isdigit(*it) == false && isblank(*it) == false)
			throw std::out_of_range("invalid date");
	}
}
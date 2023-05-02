/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:05:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/05/02 11:40:39 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	checkArgs(int argc, char **argv);
void	evaluateInput(BitcoinExchange &btc, std::fstream &fs);
bool	shouldLineBeEvaluated(char *line);

int main(int argc, char **argv)
{
	BitcoinExchange *btc = NULL;
	std::fstream	fs;

	try
	{
		checkArgs(argc, argv);
		fs.open(argv[1], std::fstream::in);

		if (fs.fail())
			throw(std::runtime_error("Could not open file"));

		btc = new BitcoinExchange();
		evaluateInput(*btc, fs);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}

	delete btc;
	return (0);
}

void	checkArgs(int argc, char **argv)
{
	if (argc != 2)
		throw (std::runtime_error("Usage: ./btc [file]"));

	if (std::string(argv[1]) != "input.txt")
		throw (std::runtime_error("Error: Only input.txt is allowed"));
}

// Lit les lignes de input.txt
// Analyse et traite chaque demande de taux de change pour une date donnee

void	evaluateInput(BitcoinExchange &btc, std::fstream &fs)
{
	while (!fs.eof())
	{
		char	line[100];
		fs.getline(line, 100);

		if (fs.eof() || shouldLineBeEvaluated(line) == false)
			continue;

		if (BONUS)
			std::cout << std::endl << "Input: " << line << std::endl;

		std::string	*split = NULL;

		try
		{
			split = splitString(line, "|");
			btc.outputExchangeValueOnDate(split[DATE], split[VALUE]);
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

		delete [] (split);
	}
}

// Retourne true si la ligne doit etre evaluee
// Sinon false

bool	shouldLineBeEvaluated(char *line)
{
	std::string	lineStr(line);

	if (isStringEmpty(line) == true || lineStr == "date | value")
		return (false);

	return (true);
}

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

// Separe les dates et les valeurs des fichiers input.txt et data.csv
std::string	*splitString(std::string string, std::string sep)
{
	std::string	*split = new std::string[2];
	size_t		delim = string.find(sep, 0);

	if (delim == std::string::npos)
	{
		delete [] (split);
		throw (std::out_of_range(string + ": invalid input"));
	}

	split[DATE] = string.substr(0, delim);
	split[VALUE] = string.substr(delim + sep.length(), std::string::npos);

	return (split);
}
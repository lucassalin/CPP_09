/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:05:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/04/28 21:45:12 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void			checkArgs(int ac, char **av);
std::fstream	*openFileStream(char *filename);
void			evaluateInput(BitcoinExchange &btc, std::fstream &fs);
bool			shouldLineBeEvaluated(char *line);

int	main(int ac, char **av)
{
	BitcoinExchange	*btc = NULL;
	std::fstream	*fs = NULL;

	try
	{
		checkArgs(ac, av);
		fs = openFileStream(av[1]);
		
		(void)fs;
		
		btc = new BitcoinExchange();
		evaluateInput(*btc, *fs);
	}
	catch (std::exception &e)
	{
		std::cerr << RED "Error: " << e.what() << RESET << std::endl;
		return (1);
	}

	delete btc;
	delete fs;

	return (0);
}

void	checkArgs(int ac, char **av)
{
	(void)av;

	if (ac != 2)
		throw (std::runtime_error("Usage: ./btc [file]"));
}

std::fstream	*openFileStream(char *filename)
{
	std::string	path = filename;
	struct stat	filecheck;

	if (stat(filename, &filecheck) != 0)
		throw (std::runtime_error(path + ": invalid file"));

	if ((filecheck.st_mode & S_IFREG) == 0)
		throw (std::runtime_error(path + ": is a directory"));

	std::fstream	*fs = new std::fstream();
	fs->open(filename, std::fstream::in);

	if (fs->fail())
		throw (std::runtime_error(path + ": could not open file"));

	return (fs);
}

// Lit les lignes de input.txt
// Analyse et traite chaque demande de taux de change pour une date donnee

void	evaluateInput(BitcoinExchange &btc, std::fstream &fs)
{
	int	i = 0;

	while (!fs.eof())
	{
		char	line[100];
		fs.getline(line, 100);

		if (fs.eof() || shouldLineBeEvaluated(line) == false)
		{
			i++;
			continue;
		}

		if (VERBOSE)
			std::cout << std::endl << CYAN "Input: " << line << RESET << std::endl;

		std::string	*split = NULL;

		try
		{
			split = splitString(line, "|");
			btc.outputExchangeValueOnDate(split[DATE], split[VALUE]);
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << " (line " << i << ": " << line << ")" << std::endl;
		}

		delete [] (split);
		i++;
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
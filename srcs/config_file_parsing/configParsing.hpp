/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <gkoechli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:42:09 by gkoechli          #+#    #+#             */
/*   Updated: 2023/08/10 10:49:59 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSING_HPP
# define CONFIGPARSING_HPP
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>
# define START -1
# define OPENBRACKET 0
# define CLOSEDBRACKET 1
# define SERVER 2
# define SEMICOLUMN 3
# define LOCATION 4
# define NAME 5
# define VALUE 6

class configParsing
{
	public:
		configParsing();
		~configParsing();
		configParsing(std::string);
		void	printConfFile();
		void	printLines();
		int		routine();
		std::vector<std::string> stringSplitIntoWords(std::string);
		int		identifyTokenType(std::string);
	private:
		std::string _confFile;
		std::vector<std::string> lineList;
};

#endif
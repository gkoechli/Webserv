/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:42:09 by gkoechli          #+#    #+#             */
/*   Updated: 2023/10/24 15:19:00 by rokerjea         ###   ########.fr       */
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
# include "serverClass.hpp"
# include "locationClass.hpp"

class configParsing
{
	public:
		~configParsing();
		configParsing(std::string);
		configParsing(configParsing &);
		void	printConfFile();
		void	printLines();
		int		routine();
		std::vector<std::string> stringSplitIntoWords(std::string);
		int		identifyTokenType(std::string);
		std::pair<std::string, std::string> getListenPort();
		std::string getKeyContent(std::string);
		void	set_file_values();
		void	set_server_values(std::vector<std::string>::iterator);
		std::pair<std::string, locationClass> set_location_values(std::vector<std::string>::iterator);
		int		findServer(std::string);
		void	printServerInfo();
		void	printServerList();
		serverClass&	getServerRef(std::string);
		std::map<std::string, serverClass> serverList;

	private:
		std::string _confFile;
		std::vector<std::string> lineList;
		std::map<std::string, std::string> file;
};

#endif
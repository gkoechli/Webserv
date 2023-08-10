/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <gkoechli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:43:02 by gkoechli          #+#    #+#             */
/*   Updated: 2023/08/10 15:25:44 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configParsing.hpp"

std::pair<std::string, std::string> pairIt(std::string key, std::string value)
{
	std::pair<std::string, std::string> ret(key, value);
	return ret;
}

configParsing::configParsing()
{

}

configParsing::configParsing(std::string obj)
{
	std::fstream file;
	std::string tmp;

	file.open(obj.c_str());
	if (!file)
		throw std::exception();
	while (file.good())
	{	
		std::getline(file, tmp);
		this->_confFile += tmp += "\n";
		lineList.push_back(tmp);
	}
	this->file.insert(pairIt("allow","PUT GET DELETE POST"));
	this->file.insert(pairIt("listen", "127.0.0.1:8080"));
	this->file.insert(pairIt("cli_max_size","1200000"));
	this->file.insert(pairIt("error_page","404 error.html"));
	this->file.insert(pairIt("server_name", "rokekoe"));
	this->file.insert(pairIt("index","index.html"));
	this->file.insert(pairIt("cgi_pass","/usr/bin/php-cgi"));
	this->file.insert(pairIt("autoindex", "on"));
	this->routine();
	this->set_file_values();
}

configParsing::~configParsing()
{

}

void	configParsing::printConfFile()
{
	std::cout << this->_confFile;
}

void	configParsing::printLines()
{
	std::vector<std::string>::iterator it = this->lineList.begin();
	while (it != this->lineList.end())
	{
		std::cout << *it;
		it++;
	}
}

std::vector<std::string> configParsing::stringSplitIntoWords(std::string obj)
{
	std::vector<std::string> wordSplitStr;
	std::string word;
	std::string tmp = "";
	int i = 1;
	int flag = 0;
	std::stringstream ss(obj);
	while (ss >> word) 
	{
		if (word.find(";") != std::string::npos)
		{
			std::string::iterator it = word.end();
			it--;
			if (*it-- != ';' || word.find(";") != word.find_last_of(";"))
				throw std::exception();
			tmp += word.substr(0, word.size() - 1);
			wordSplitStr.push_back(tmp);
			wordSplitStr.push_back(";");
			flag = 0;
		}
		else
			wordSplitStr.push_back(word);
		i++;
	}
	return wordSplitStr;
}

int	configParsing::identifyTokenType(std::string token)
{
	if (token == "server")
		return (SERVER);
	if (token == "{")
		return (OPENBRACKET);
	if (token == "}")
		return (CLOSEDBRACKET);
	if (token == "location")
		return (LOCATION);
	if (token == ";")
		return (SEMICOLUMN);
	return (NAME);
}

void checkPreviousAndCurrentMatch(int previousToken, int currentToken)
{
	if (previousToken == START && (currentToken == NAME || currentToken == SERVER))
		return;
	if (previousToken == OPENBRACKET && (currentToken == CLOSEDBRACKET || currentToken == NAME))
		return;
	if (previousToken == CLOSEDBRACKET && (currentToken == CLOSEDBRACKET || currentToken == SERVER || currentToken == LOCATION || currentToken == NAME))
		return;
	if (previousToken == SERVER && currentToken == OPENBRACKET)
		return;
	if (previousToken == SEMICOLUMN && (currentToken == CLOSEDBRACKET || currentToken == SERVER || currentToken == LOCATION || currentToken == NAME))
		return;
	if (previousToken == LOCATION && currentToken == VALUE)
		return;
	if (previousToken == NAME && currentToken == VALUE)
		return;
	if (previousToken == VALUE && (currentToken == SEMICOLUMN || currentToken == OPENBRACKET || currentToken == VALUE))
		return;
	throw std::exception();
}

int	configParsing::routine()
{
	int previousToken = START;
	int currentToken = START;

	std::vector<std::string>::iterator it = this->lineList.begin();
	while (it != this->lineList.end())
	{
		while (*it == "\n")
			it++;
		if (it == this->lineList.end())
			break;
		std::vector<std::string> temp;
		temp = stringSplitIntoWords(*it);
		std::vector<std::string>::iterator itemp = temp.begin();
		while (itemp != temp.end())
		{
			currentToken = identifyTokenType(*itemp);
			if ((previousToken == NAME || previousToken == LOCATION || previousToken == VALUE) && currentToken == NAME)
					currentToken = VALUE;
			checkPreviousAndCurrentMatch(previousToken, currentToken);
			itemp++;
			previousToken = currentToken;
		}
		it++;
	}
	return (0);
}

void	configParsing::set_file_values()
{
	std::vector<std::string>::iterator it = this->lineList.begin();
	std::string one;
	std::string two;
	while (it != this->lineList.end())
	{
		while (*it == "\n")
			it++;
		if (it == this->lineList.end())
			break;
		std::vector<std::string> temp;
		temp = stringSplitIntoWords(*it);
		std::vector<std::string>::iterator itemp = temp.begin();
		if (identifyTokenType(*itemp) == NAME)
		{
			one = *itemp;
			++itemp;
			while (itemp != temp.end())
			{
				two += *itemp;
				itemp++;
				if (identifyTokenType(*itemp) == SEMICOLUMN)
					break;
				if (itemp != temp.end())
					two += " ";
			}
			this->file.insert(pairIt(one, two));
			two = "";
		}	
		it++;
	}
	printFileValues();
}

std::pair<std::string, std::string> configParsing::getListenPort()
{
	std::string tmp = this->file.find("listen")->second;
	
	std::string pop1;
	std::string pop2;
	

	pop1 = tmp.substr(0, tmp.find(":"));
	
	pop2 = tmp.substr(tmp.find(":") + 1, tmp.size() - tmp.find(":"));
	std::cout << pop1 << " " << pop2 << std::endl;
	return pairIt(pop1, pop2);
}

std::string configParsing::getKeyContent(std::string key)
{
	std::string ret = this->file.find(key)->second;
	return (ret);
}

void	configParsing::printFileValues()
{
	std::map<std::string, std::string>::iterator it = this->file.begin();
	while (it != this->file.end())
	{
		std::cout << it->first << " || " << it->second << std::endl << std::endl;
		it++;
	}
}
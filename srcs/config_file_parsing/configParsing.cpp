/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <gkoechli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:43:02 by gkoechli          #+#    #+#             */
/*   Updated: 2023/08/06 16:39:17 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configParsing.hpp"

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
			// std::cout << *itemp << " //value : " << currentToken <<  std::endl;
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
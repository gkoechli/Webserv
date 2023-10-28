/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <gkoechli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:43:02 by gkoechli          #+#    #+#             */
/*   Updated: 2023/10/28 15:30:19 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configParsing.hpp"

std::pair<std::string, std::string> pairIt(std::string key, std::string value)
{
	std::pair<std::string, std::string> ret(key, value);
	return ret;
}


configParsing::configParsing(std::string obj)
{
	std::fstream file;
	std::string tmp;
	std::string word;

	file.open(obj.c_str());
	if (!file)
		throw std::exception();
	while (file.good())
	{	
		std::getline(file, tmp);
		std::stringstream stmp(tmp);
		tmp = "";
		int start = 0;
		while (stmp >> word)
		{
			if (start == 1)
				tmp += " ";
			tmp += word;
			start = 1;
		}
		// std::cout << "tmp = |" << tmp << "|\n";
		if (tmp != "\n" && tmp.size() > 0 && tmp != "")
			lineList.push_back(tmp);
		this->_confFile += tmp += "\n";
	}
	this->routine();
	// std::cout << "ROUTINE DONE \n";
	// this->printLines();
	// this->printConfFile();
	this->set_file_values();
}

configParsing::~configParsing()
{

}

configParsing::configParsing(configParsing &obj): serverList(obj.serverList), _confFile(obj._confFile), lineList(obj.lineList), file(obj.file)
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
		std::cout << "printline : |" << *it << "|"<< std::endl;
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
	// std::cout << token << std::endl;
	if ((token.find("{") != std::string::npos || token.find("}") != std::string::npos) && token != "{" && token != "}")
		throw std::exception();
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
	// looping until we find a SERVER, set its values, then proceeds to the next entry;
	// std::cout << "SET_FILE_VALUES -------------------------------------------------------------------------\n";
	// still need to fix weird bugs with the iterator going 1 + too much, or with random empty lines. i think theres an issue with the end bracket of each server + location section 
	std::vector<std::string>::iterator it = this->lineList.begin();
	while (it != this->lineList.end())
	{
		std::vector<std::string> temp;
		temp = stringSplitIntoWords(*it);
		// std::vector<std::string>::iterator itemptest = temp.begin();
		// while (itemptest != temp.end())
		// {
		// 	std::cout << *itemptest << std::endl;
		// 	itemptest++;
		// }
		std::vector<std::string>::iterator itemp = temp.begin();
		if (identifyTokenType(*itemp) == SERVER)
			set_server_values(it);
		it++;
	}
}

void	configParsing::set_server_values(std::vector<std::string>::iterator itori)
{
	// std::cout << "================================= SET_SERVER_VALUES ======================================\n";
	serverClass new_server;
	int flag = 0;
	std::string one;
	std::string two;
	std::vector<std::string>::iterator it = itori;
	while (it != this->lineList.end())
	{
		// std::cout << "current line = " << *it << std::endl;
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
			// std::cout << "name: " << one << " // " << two << std::endl;
			// std::cout << "*itemp = " << *itemp << std::endl;
			new_server.insertPair(pairIt(one, two));
			two = "";
		}
		else if (identifyTokenType(*itemp) == LOCATION)
		{
			// std::cout << "location: " << *itemp << std::endl;
			new_server.insert_location(set_location_values(it));
			while (*it != "}" && it != this->lineList.end())
			{
				// std::cout << "while blabla.... on est sur : |" << *it << "|" << std::endl;
				it++;

			}
			// std::cout << "SORTIE DE LOCATION = " << *it << std::endl;
		}
		else if (identifyTokenType(*itemp) == CLOSEDBRACKET) // end of server scope
		{
			// std::cout << "bracket: " << *itemp << std::endl;
			// std::cout << " ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> adding server " << new_server.getName() << std::endl; ;
			// new_server.printServerData();
			// new_server.printLocationList();
			std::pair<std::string, serverClass> ret(new_server.getName(), new_server);
			this->serverList.insert(ret);
			break;
		}
		it++;
		// std::cout << "*it = |" << *it << "|" << std::endl;
	}
	// std::map<std::string, serverClass>::iterator mop = this->serverList.begin();
	// while (mop != serverList.end())
	// {
	// 	std::cout << mop->first << std::endl;
	// 	mop->second.printServerValues();
	// 	mop++;
	// }
	// ajouter un compte de brackets pour savoir quand close le parsing
}

std::pair<std::string, locationClass>	configParsing::set_location_values(std::vector<std::string>::iterator it)
{
	// std::cout << "================================= SET_LOCATION_VALUES ======================================\n";
	locationClass new_location;
	std::string one;
	std::string two;
	while (it != this->lineList.end())
	{
		// while (*it == "\n")
		// 	it++;
		// if (it == this->lineList.end())
		// 	break;
		std::vector<std::string> temp;
		temp = stringSplitIntoWords(*it); 
		std::vector<std::string>::iterator itemp = temp.begin();
		if (identifyTokenType(*itemp) == LOCATION)
		{
			++itemp;
			new_location.setName(*itemp);
			// std::cout << "location name = " << new_location.getName() << std::endl;
		}
		else if (identifyTokenType(*itemp) == NAME)
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
			// std::cout << "location values: " << one << " // " << two << std::endl;
			new_location.insertPair(pairIt(one, two));
			two = "";
		}
		it++;
		if (*it == "}")
			break;
		// std::cout << "*it before newloop = " << *it << std::endl;
	}
	new_location.insertPair(pairIt("index", "index.html"));
	// new_location.printLocationValues();
	std::pair<std::string, locationClass> ret(new_location.getName(), new_location);
	return ret;

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
	std::string ret;
	if (key.empty() != 0)
	{
		ret = this->file.find(key)->second;
	}
	// std::cout << "ret in getKeyContent = " << ret << std::endl;
	return (ret);
}

void	configParsing::printServerInfo()
{
	std::map<std::string, serverClass>::iterator it = this->serverList.begin();
	while (it != this->serverList.end())
	{
		it->second.printServerValues();
		it++;
	}
}
void	configParsing::printServerList()
{
	std::map<std::string, serverClass>::iterator it = this->serverList.begin();
	while (it != this->serverList.end())
	{
		std::cout << it->first << std::endl;
		it++;
	}
}


serverClass&	configParsing::getServerRef(std::string name)
{
	if (this->serverList.find(name) != this->serverList.end())
		return this->serverList[name];
	else
		throw std::exception();
}

int		configParsing::findServer(std::string name)
{
	if (name.empty() == true)
		return (3500);
	if (this->serverList.find(name) != this->serverList.end())
	{
		// std::cout <<  "server found : " << this->serverList.find(name)->first << std::endl;
		return (200);
	}
	return (5000);
}

std::map<std::string, serverClass>::iterator configParsing::getBeginServerListIterator()
{
	std::map<std::string, serverClass>::iterator it;

	it = this->serverList.begin();
	return it;
}

std::map<std::string, serverClass>::iterator configParsing::getEndServerListIterator()
{
	std::map<std::string, serverClass>::iterator it;

	it = this->serverList.end();
	return it;
}
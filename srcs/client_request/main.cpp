#include "ClientRequest.hpp"

void	fill_basic_content(ClientRequest &obj);

int main()
{
	try
	{
		std::string insert_string_here = "POST THE HELL HTTP/1.1\nme out of here\nfucking hell\n\nNOWTHISISTH\nEBODDY\nITSHUGE\nITSMARV\n\nELOUS";
		ClientRequest test((insert_string_here)); 
		std::cout << test.getMethod()<< std::endl;
		std::cout << test.getTarget();
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}
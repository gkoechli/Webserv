#include "ClientRequest.hpp"

void	fill_basic_content(ClientRequest &obj);

int main()
{
	try
	{
		std::string insert_string_here = "POST THE HELL HTTP/1.1\nme out of here\nfucking hell\n\nNOWTHISISTHEBODDYITSHUGEITSMARVELOUS";
		ClientRequest test((insert_string_here)); 
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}
#include "ClientRequest.hpp"

void	fill_basic_content(ClientRequest &obj);

int main()
{
	try
	{
		std::string insert_string_here = "POST THE HELL OUT\nme out of here\nfucking hell\n";
		ClientRequest test((insert_string_here)); 
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}
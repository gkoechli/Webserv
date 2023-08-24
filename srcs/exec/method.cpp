#include "method.hpp"

Method::Method(std::string path)
{
	get_content_from_file(path);
	status_code = 200;
}

Method::~Method(){}

bool is_empty(std::ifstream File)
{
    return File.peek() == std::ifstream::traits_type::eof();
}

bool	check_error(std::ifstream file)
{
	if (!file.is_open())
	{
		status_code = 404;
		return (true);
	}
	if (is_empty(file))
	{
		status_code = 204;
		return (true);
	}
	return (false);
}

void	method_get()
{
	std::ifstream file(path);
	if (check_error(file))
	{
		return ;
	}
	std::string line;
	while (std::getline(file, line))
	{
		content += line;
	}
	file.close();
}//just the content of a file open/read/close
		//if file not found, return 404
		//if file is a directory, return 403
		//if file is not readable, return 403
		//if file is not a regular file, return 403
		//if file is empty, return 204
		//if file is too big, return 413
		//if file is ok, return 200

int get	status_code()
{
	return (status_code);
}

std::string get_content()
{
	return (content);
}
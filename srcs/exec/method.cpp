#include "method.hpp"

Method::Method(std::string path)
{
	// get_content_from_file(path);
	_path = path;
	status_code = 200;
}

Method::~Method(){}

bool Method::is_empty()
{
	std::ifstream File(_path);
    return File.peek() == std::ifstream::traits_type::eof();
}

bool	Method::check_error()
{

	if (is_empty())
	{
		status_code = 204;
		return (true);
	}
	return (false);
}

/*
get
post -> need to create a file, check if creation and content is correct
-> then only need to return status code,
so void method, and status code getter
delete -> delete file at path
if error (access right, doesn't exist, etc) status code
else normal status
void method, return status

whats needed to be returned in each cases?
status code
content if there is any

response object :
a single one, created with value depending on result of exec
and empty variables to be filled later?
or an intermediate object to be used in construction of response header?

what does response object need?
status code
body content, if any
everything else needed to construct a valid response header:
*Content-Length:
*Content-Type:
*Connection: keep-alive/else
*Content-Language:
*Date:
*Server:
*HTTP/1.1 (status code) (OK)

most of those can be easily determined or have default values
need infos from request header (connection keep-alive, Server)




*/
// void	method_get()
// {
// 	std::ifstream file(path);
// 	if (check_error(file))
// 	{
// 		return ;
// 	}
// 	std::string line;
// 	while (std::getline(file, line))
// 	{
// 		content += line;
// 	}
// 	file.close();
// }
//just the content of a file open/read/close
		//if file not found, return 404
		//if file is a directory, return 403
		//if file is not readable, return 403
		//if file is not a regular file, return 403
		//if file is empty, return 204
		//if file is too big, return 413
		//if file is ok, return 200

int Method::get_status_code()
{
	return (status_code);
}
std::string Method::get_path()
{
	return (_path);
}
// std::string Method::get_content()
// {
// 	return (content);
// }
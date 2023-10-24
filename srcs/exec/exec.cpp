#include "exec.hpp"

Exec::Exec(std::string request_string, configParsing &settings_arg) : config(settings_arg)
{
	request_as_string = request_string;
	// config = settings_arg;
	// recuperer le vrai path : virer le server neame et remplacer par path absolu.
	// request_as_string = request_string;
	std::cout << "request string received in exec : \n" << request_as_string << std::endl; //Del
}

Exec::~Exec()
{}

// void Exec::print_response()
// {
// 	std::cout << "current content of response object:" << std::endl;
// 	// std::string body = response.getbody();
// 	// std::cout << body << std::endl;
// 	std::cout << response.getPath() << std::endl;
// 	std::cout << response.getLocation() << std::endl;
// 	std::cout << response.getHeaderContent("Content-Type:") << std::endl;
// 	std::cout << response.getHeaderContent("Content-Length:") << std::endl;
// 	std::cout << response.getHeaderContent("Connection:") << std::endl;
// 	std::cout << response.getHeaderContent("Content-Language:") << std::endl;
// 	std::cout << response.getHeaderContent("Date:") << std::endl;
// 	std::cout << response.getHeaderContent("Server:") << std::endl;
// 	std::cout << response.getbody() << std::endl;
// 	std::cout << "end of response object." << std::endl;
// }

// void	Exec::mockup_response_object()
// {
// 	response.setHTTPCode(404);
// 	response.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
// 	response.setLocation("Website/folder/file.extension");
// 	response.setCGI(false);
// 	response.setbody("\n"
// 	"<!DOCTYPE html>\n"
// 	"<html lang=\"en\">\n"
// 	"<head>\n"
// 	"<meta charset=\"utf-8\">\n"
// 	"<title>A simple webpage</title>\n"
// 	"</head>\n"
// 	"<body>\n"
// 	"<h1>Simple HTML webpage</h1>\n"
// 	"<p>Hello, world!</p>\n"
// 	"</body>\n"
// 	"</html>\n"
// 	"\n"
// 	"\n");
// 	// response.insertHeaderPair(std::make_pair("HTTP/1.1", "200 OK\n"));
// 	response.insertHeaderPair(std::make_pair("Content-Type:", "text/html; charset=utf-8\n"));
// 	response.insertHeaderPair(std::make_pair("Content-Length:", "55743\n"));
// 	response.insertHeaderPair(std::make_pair("Connection:", "keep-alive\n"));
// 	response.insertHeaderPair(std::make_pair("Content-Language:", "en-US\n"));
// 	response.insertHeaderPair(std::make_pair("Date:", "Thu, 06 Dec 2018 17:37:18 GMT\n"));
// 	response.insertHeaderPair(std::make_pair("Server:", "meinheld/0.6.1\n"));
// 	// std::string test = response.getPath();
// 	// test = response.getbody();
// 	//ERROR, if i delete last line exec fail immediatly
// 	//wich means a memory error usually
// 	//i might have made a mistake somewhere with pair or map, maybe an error of initialisation
// }

std::string int_to_string2(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

int	identifiy_cases (std::string method)
{
	std::string type[3] = {"GET", "POST", "DELETE"};
	for (int i = 0; i < 3; i++)
	{
		if (method == type[i])
			return (i);
	}
	return (3);
}

typedef void(Model::*ptr_func)(void);

std::vector<char> Exec::error_response_constructor(int error_code)
{
	std::string error_message;
	std::string response_str;
	if (error_code == 400)
		error_message = "Bad Request";
	else if (error_code == 404)
		error_message = "Not Found";
	else if (error_code == 405)
		error_message = "Method Not Allowed";
	else if (error_code == 413)
		error_message = "Request Entity Too Large";
	else if (error_code == 500)
		error_message = "Internal Server Error";
	else if (error_code == 501)
		error_message = "Not Implemented";
	else
		error_message = "Unknown Error";

	response_str = std::string("HTTP/1.1 " + int_to_string2(error_code) + " " + error_message + "\r\n\r\n").c_str();
    std::vector<char> res(response_str.begin(), response_str.end());
	return res;
}

std::vector<char> Exec::return_final_response()
{
	std::vector<char> response_str;
	try
	{
		ClientRequest request(request_as_string, config);
		request.printPath();
		request.printTarget();
		request.printHeader();
		request.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
		Model model_handler(request);
		model_handler.mockup_response_object(); //will be replaced by "execute request"

		ptr_func functions[3] = {&Model::method_get, &Model::method_post, &Model::method_delete};
		int cases = identifiy_cases(request.getMethod());
		if (cases <= 2)
			(model_handler.*functions[cases])();
		response_str = model_handler.get_full_response_str();
	}
	catch (int error_code)
	{
		response_str = error_response_constructor(error_code);
	}
	return response_str;
}
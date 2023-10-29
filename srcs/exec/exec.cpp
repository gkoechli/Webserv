#include "exec.hpp"

Exec::Exec(std::string request_string, configParsing &settings_arg) : config(settings_arg)
{
	request_as_string = request_string;
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

// std::string Exec::error_in_settings(int current_error_code)
// {
// 	std::string error = config.getServerRef(request.getHost()).getKeyContent("error_page");
// 	if (error.size() == 0)
// 		return "";
// 	std::stringstream wording(error);
// 	int error_code;
// 	int first = 1;
// 	std::string error_path;
// 	std::string word;
// 	while (wording >> word)
// 	{
// 		if (first == 1) // each first element of line will be the token
// 		{
// 			error_code = atoi(word);
// 			first = 0;
// 		}
// 		else
// 			error_path = word; // the rest is setup as std::vector<string> and added as value to the map
// 	}
// 	if (error_code != current_error_code)
// 		return "";
// 	if (access(error_path.c_str(), F_OK) == -1)
// 		return "";
// 	return error_path;
// }

std::vector<char> Exec::error_response_constructor(int error_code)
{
	// std::string error_path = error_in_settings(error_code);
	// if(!error_path.empty())
	// {
	// 	request.setPath(error_path);
	// 	model_handler.*functions[0];
	// 	return (model_handler.get_full_response_str());
	// }
	// else //no error page defined in settings
	// {
		HttpCodes code_list;
		std::string error_message;
		error_message = code_list.get_code_value(error_code);;
		std::string response_str;
		response_str = std::string("HTTP/1.1 " + int_to_string2(error_code) + " " + error_message + "\r\n\r\n").c_str();
		std::vector<char> res(response_str.begin(), response_str.end());
		return res;
	// }
}

bool Exec::is_cgi(ClientRequest &request)
{
	if (request.getPath().find(".php") != std::string::npos)
		return true;
	return false;
}

std::vector<char> Exec::return_final_response()
{
	std::vector<char> response_str;
	try
	{
		ClientRequest request(request_as_string, config);
		std::cerr << "body = " << request.getBody() << std::endl;
		request.printPath();
		request.printTarget();
		request.printHeader();
		// request.setPath("index.php");
		request.printPath();
		Model model_handler(request);
		// model_handler.mockup_response_object(); //will be replaced by "execute request"
		if (is_cgi(request))
		{
			model_handler.cgi_operation();
		}
		else
		{
			ptr_func functions[3] = {&Model::method_get, &Model::method_post, &Model::method_delete};
			int cases = identifiy_cases(request.getMethod());
			if (cases <= 2)
				(model_handler.*functions[cases])();
		}
		response_str = model_handler.get_full_response_str();
	}
	catch (int error_code)
	{
		response_str = error_response_constructor(error_code);
	}
	return response_str;
}
#include "exec.hpp"

Exec::Exec(std::string request_string, configParsing &settings_arg) : config(settings_arg)
{
	request_as_string = request_string;
	// std::cout << "request string received in exec : \n" << request_as_string << std::endl; //Del
}

Exec::~Exec()
{}

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

void Exec::error_in_settings(std::string error_path)
{
	if (error_path.size() == 0)
	{
		default_error_code = 200;
		default_error_path = "";
		return ;
	}
	std::stringstream wording(error_path);
	int first = 1;
	std::string word;
	while (wording >> word)
	{
		if (first == 1)
		{
			default_error_code = atoi(word.c_str());
			first = 0;
		}
		else
			default_error_path = word;
	}
}

std::vector<char> Exec::error_response_constructor(int error_code)
{
	if(error_code == default_error_code)
	{
		std::string error_response;
		std::ifstream error_file(default_error_path.c_str());
		std::string error_body = std::string((std::istreambuf_iterator<char>(error_file)), std::istreambuf_iterator<char>());
		error_response = std::string("HTTP/1.1 " + int_to_string2(error_code) + " " + "\r\n\r\n" + error_body).c_str();
		error_response += "Content-Length: " + int_to_string2(error_body.size()) + "\r\n";
		error_response += "Content-Type: text/html\r\n";
		error_response += error_body;
		std::vector<char> res(error_response.begin(), error_response.end());
		return res;
	}
	else //no error page defined in settings
	{
		HttpCodes code_list;
		std::string error_message;
		error_message = code_list.get_code_value(error_code);;
		std::string response_str;
		response_str = std::string("HTTP/1.1 " + int_to_string2(error_code) + " " + error_message + "\r\n\r\n").c_str();
		std::vector<char> res(response_str.begin(), response_str.end());
		return res;
	}
}

bool Exec::is_cgi(ClientRequest &request)
{
	if (request.getPath().find(".php") != std::string::npos)
		return true;
	return false;
}

std::vector<char> Exec::return_final_response()
{
	int is_cgi_flag = 0;
	std::vector<char> response_str;
	try
	{
		ClientRequest request(request_as_string, config);
		std::string port = request.getPort();
		// std::cerr << "port = " << port << std::endl;//TODEL
		serverClass server = config.getServerRef(port);
		default_error_path = server.getKeyContent("error_page");
		error_in_settings(default_error_path);
		// std::cerr << "body = " << request.getBody() << std::endl;//TODEL
		// request.printPath();//TODEL
		// request.printTarget();//TODEL
		// request.printHeader();//TODEL
		// request.printPath();//TODEL
		Model model_handler(request);
		if (is_cgi(request))
		{
			is_cgi_flag = 1;
			model_handler.cgi_operation();
		}
		else
		{
			ptr_func functions[3] = {&Model::method_get, &Model::method_post, &Model::method_delete};
			int cases = identifiy_cases(request.getMethod());
			if (cases <= 2)
				(model_handler.*functions[cases])();
		}
		response_str = model_handler.get_full_response_str(is_cgi_flag);
	}
	catch (int error_code)
	{
		response_str = error_response_constructor(error_code);
	}
	return response_str;
}
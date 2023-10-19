#include "exec.hpp"

Exec::Exec(std::string request_string, configParsing &settings_arg) :
	request(request_string, settings_arg)//will need settings and request string as argument
{
	// recuperer le vrai path : virer le server neame et remplacer par path absolu.
	request.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
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

// std::string int_to_string(int i)
// {
//     std::stringstream ss;
//     ss << i;
//     return ss.str();
// }



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

std::vector<char> Exec::return_final_response()
{
	// do i instanciate request here or in exec constructor ?
	//try
	//{
	// ClientRequest request(request_as_string);
	//}
	//catch (int error_code)
	// {
	// 	create error response here and return it?
		// error error_response(error_code);
		// return (error_response.get_full_response_str());
	// }
	Model model_handler(request);
	model_handler.mockup_response_object();//will be replaced by "execute request"

	// model_handler.method_get();//work, but exceptions aren't managed
	// model_handler.method_post();//work, but exceptions aren't managed
	// model_handler.method_delete();
	try {
		ptr_func functions[3] = {&Model::method_get, &Model::method_post, &Model::method_delete};
		int cases = identifiy_cases (request.getMethod());
		if (cases <= 2)
			(model_handler.*functions[cases])();
	}
	catch (int error_code) {
		model_handler.set_status_code(error_code);
	}
	return (model_handler.get_full_response_str());
}
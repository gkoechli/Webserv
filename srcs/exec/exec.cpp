#include "exec.hpp"

Exec::Exec(std::string request_string/* configParsing settings_arg*/) :
	request(request_string)//will need settings and request string as argument
{
	request.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
	request_as_string = request_string;
	std::cout << "request string received in exec : \n" << request_as_string << std::endl; //Del
	//settings = settings_arg;
	//need to create request obj with request_string as arg, with constructor or a builder object
}

Exec::~Exec()
{}

void	Exec::main_exec_loop()
{
	//start of exec, current data: request_string, settings
	//empty data: request and response objects
	//STEP 1
	//use request string to fill request object
	//instanciate a request builder to do it?

	std::cout << "exec parsed request" << std::endl;
	// request.print();
	//STEP 2, request object is complete
	//handle request => fill response object as much as possible
	//real exec => from request obj, determine method/CGI, execute it
	//note: we need all the info we need to select if CGI/method
	//AAND what they should do precisely
	//after exec CGI/method, all operations should be over, fd closed.
	// exec_method();
	// build_response();//just set body/httpcode
	//from result, get statuscode and set it in response
	//get body as string and set it in response
	//finish now and tcp use it by doing Exec(arg); exec.main_exec_loop(); Exec.return_final_response();
	//wich is easier to use step by step
	//we can know immediatly what's the current state of everything after each step
}

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

std::vector<char> Exec::return_final_response()
{
	//model.exec_action();
	Model model_handler(request);
	// model_handler.mockup_response_object();//will be replaced by "execute request"
	model_handler.method_get();//work, but exceptions aren't managed
	// model_handler.method_delete();
	return (model_handler.get_full_response_str());
	// std::string full_response;
	// full_response = "HTTP/1.1 ";
	// full_response += int_to_string(response.getHTTPCode());//TODO: check status and add OK or fail depending on value
	// full_response += " OK\n";
	// full_response += response.getFullHeader();
	// full_response += response.getbody();
    // std::vector<char> res(full_response.begin(), full_response.end());
	// return (res);
}
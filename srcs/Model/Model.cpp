#include "Model.hpp"

Model::Model(ClientRequest &request) : request(request), file(request.getPath())
{
	status_code = 200;
	//response should stay empty until there is something to set inside

}

Model::~Model()
{}

std::string int_to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::vector<char> Model::get_full_response_str()
{
	response.setHTTPCode(status_code);
	std::string full_response;

	full_response = request.getHttpVersion();
	full_response += " ";
	full_response += int_to_string(response.getHTTPCode());//TODO: check status and add OK or fail depending on value
	full_response += " OK\n";
	full_response += response.getFullHeader();
	full_response += response.getbody();
    std::vector<char> res(full_response.begin(), full_response.end());
	return (res);
}

void Model::method_get()
{
	file.open();
	response.setbody(file.get_content_from_file());
	file.close();
	status_code = 200;
}

void Model::method_delete()
{
	if (!file.exist())
	{
		status_code = 404;
		return;
	}
	file.open();
	file.unlink();
	file.close();
	response.setbody("\n<!DOCTYPE html>\n\
            <html>\n\
            <body>\n\
              <h1>File deleted</h1>\n\
            </body>\n\
            </html>\n\n\n");
	//TODO : add length of body and format of response (html)
	status_code = 200;
}

void	Model::mockup_response_object()
{
	response.setHTTPCode(404);
	response.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
	response.setLocation("Website/folder/file.extension");
	response.setCGI(false);
	response.setbody("\n"
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
	"<head>\n"
	"<meta charset=\"utf-8\">\n"
	"<title>A simple webpage</title>\n"
	"</head>\n"
	"<body>\n"
	"<h1>Simple HTML webpage</h1>\n"
	"<p>Hello, world!</p>\n"
	"</body>\n"
	"</html>\n"
	"\n"
	"\n");
	// response.insertHeaderPair(std::make_pair("HTTP/1.1", "200 OK\n"));
	response.insertHeaderPair(std::make_pair("Content-Type:", "text/html; charset=utf-8\n"));
	response.insertHeaderPair(std::make_pair("Content-Length:", "55743\n"));
	response.insertHeaderPair(std::make_pair("Connection:", "keep-alive\n"));
	response.insertHeaderPair(std::make_pair("Content-Language:", "en-US\n"));
	response.insertHeaderPair(std::make_pair("Date:", "Thu, 06 Dec 2018 17:37:18 GMT\n"));
	response.insertHeaderPair(std::make_pair("Server:", "meinheld/0.6.1\n"));
	// std::string test = response.getPath();
	// test = response.getbody();
	//ERROR, if i delete last line exec fail immediatly
	//wich means a memory error usually
	//i might have made a mistake somewhere with pair or map, maybe an error of initialisation
}
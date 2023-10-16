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

// void Model::method_post()
// {
// 	//check if exist
// 	file.open();
// 	file.append(request.getbody());
// 	file.close();
// 	response.setbody("\n<!DOCTYPE html>\n\
// 			<html>\n\
// 			<body>\n\
// 			  <h1>File modified</h1>\n\
// 			</body>\n\
// 			</html>\n\n\n");
// 	//TODO : add length of body and format of response (html)

// 	status_code = 200;
// }

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

// char* get_binary_name(std::string path)
// {
// 	std::string binary_name;
// 	size_t pos = path.find_last_of('/');
// 	if (pos != std::string::npos)
// 		binary_name = path.substr(pos + 1);
// 	else
// 		binary_name = path;
// 	return (binary_name.c_str());
// }

// void Model::cgi_operation()
// {
// 	int pid, fd[2];
// 	if (access(request.getPath().c_str(), X_OK) == -1)
// 	{
// 		status_code = 403;
// 		return;
// 	}
// 	if (pipe(fd) == -1)
// 	{
// 		status_code = 503;
// 		return;
// 	}

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		status_code = 500;
// 		return;
// 	}
// 	if (pid == 0)//child
// 	{
// 		close(fd[0]);
// 		close(STDOUT_FILENO);
// 		close(STDIN_FILENO);
// 		//need dup2 for stdin to get the body of the request to the cgi
// 		std::string body = request.getbody();
// 		std::FILE* body_file = std::tmpfile();
// 		std::fputs(body.c_str(), body_file);
// 		std::rewind(body_file);
// 		if (dup2(body_file, STDIN_FILENO) == -1)
// 			exit(1);
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 			exit(1);

// 		char* binary_name = strdup(get_binary_name(request.getPath()).c_str());
// 		char* binary_path = strdup(request.getPath().c_str());
// 		char* argv[3] = {binary_name, binary_path, NULL};
// 		execve(binary_path, argv, envp);
// 		for (int i = 0; envp[i] != NULL; i++)
// 			free(envp[i]);
// 		free(binary_path);
// 		free(argv);
// 		free(envp);
// 		exit(0);
// 	}
// 	else if (pid > 0) //parent
// 	{
// 		close(fd[1]);
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			if (WEXITSTATUS(status) == 0)
// 			{
// 				status_code = 200;
// 				response.setbody("CGI OK");
// 			}
// 			else
// 			{
// 				status_code = 500;
// 				response.setbody("CGI ERROR");
// 			}
// 		}
// 		int ret = 0;
// 		std::vector	<char> buffer(4096 + 1, 0);
// 		while ((ret = read(fd[0], buffer.data(), 4096)) > 0)//need to use something else than read
// 		{
// 			response.setbody(response.getbody() + std::string(buffer.begin(), buffer.end()));
// 			buffer.clear();
// 			buffer.resize(4096 + 1, 0);
// 		}
// 		if (ret == -1)
// 		{
// 			status_code = 500;
// 			response.setbody("CGI ERROR");
// 		}
// 		close(fd[0]);
// 	}
// }

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
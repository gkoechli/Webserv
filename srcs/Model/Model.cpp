#include "Model.hpp"

Model::Model(ClientRequest &request) : request(request), file(request.getPath())
{
	status_code = 200;
}

Model::~Model()
{}

void	Model::set_status_code(int code)
{
	status_code = code;
}

std::string int_to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
std::vector<char> Model::get_full_response_str(int is_cgi)
{
	response.setHTTPCode(status_code);
	std::string full_response;
	std::string temp = response.getbody();
	if (is_cgi == 1)
	{
		size_t pos = temp.find('\n');
		if (pos != std::string::npos)
			temp = temp.substr(pos + 1);
	}
	response.insertHeaderPair(std::make_pair("Content-Length:", int_to_string(temp.size()) + "\n"));
	response.insertHeaderPair(std::make_pair("Content-type:", "text/html; charset=utf-8\n"));
	std::string port = request.getPort();
	serverClass server = request.getConfigServerRef(port);
	response.insertHeaderPair(std::make_pair("server:", server.getName() +"\n"));
	full_response = request.getHttpVersion();
	full_response += " ";
	full_response += int_to_string(response.getHTTPCode());
	full_response += " OK\n";
	full_response += response.getFullHeader();
	full_response += "\n";
	full_response += temp;
    std::vector<char> res(full_response.begin(), full_response.end());
	return (res);
}

void Model::method_get()
{
	if (file.is_directory())
	{
		listing();
		return;
	}
	file.open();
	response.setbody(file.get_content_from_file());
	file.close();
	status_code = 200;
}

void Model::listing()
{
	DIR*			dir;
	struct dirent*	dirent;
	std::string		add_str_to_body;
	std::string		path = request.getPath();
	path += "/";
	dir = opendir(path.c_str());
	if (dir == NULL)
		throw 404;
	add_str_to_body = "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"utf-8\" />\n\t\t<title>\n\t\t\tlisting\n\t\t</title>\n\t</head>\n\n\t<body>\n\t\t<h2>\n\t\t\tWEBSERV listing: ";
	add_str_to_body += path;
	add_str_to_body += "\n\t\t</h2>\n";
    while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_type == DT_DIR)
			add_str_to_body += "\t\t<h4 style=\"color:blue;\"><a href=\"";
		else
			add_str_to_body += "\t\t<h4 style=\"color:black;\"><a href=\"";
		add_str_to_body += dirent->d_name;
		if (dirent->d_type == DT_DIR)
			add_str_to_body += "/";
		add_str_to_body += "\">\n\t\t\t";
		add_str_to_body += dirent->d_name;
		add_str_to_body += "\n\t\t</a></h4>\n";
	}
	closedir(dir);
	add_str_to_body += "\t</body>\n</html>";
	response.setbody(add_str_to_body);
}

void Model::method_post()
{
	if (!file.exist())
		file.create(request.getBody());
	else
	{
		file.open();
		file.append(request.getBody());
		file.close();
	}
	response.setbody("\n<!DOCTYPE html>\n\
			<html>\n\
			<body>\n\
			  <h1>File modified</h1>\n\
			</body>\n\
			</html>\n\n\n");
	status_code = 201;
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
	status_code = 200;
}

char** Model::mapToEnvp(const std::map<std::string, std::string>& m)
{
	std::vector<std::string> v;
	for (std::map<std::string, std::string>::const_iterator it = m.begin() ; it != m.end() ; it++)
		v.push_back(it->first + "=" + it->second);
	char** arr = (char**)malloc((v.size() + 1) * sizeof(*arr));
	if (arr == NULL)
		exit(500);
	std::vector<std::string>::size_type index = 0;
	for (std::vector<std::string>::iterator it = v.begin() ; it != v.end() ; it++)
	{
		arr[index] = strdup(it->c_str());
		if (arr[index] == NULL)
			exit(500);
		index++;
	}
	arr[index] = NULL;
	return arr;
}

char** Model::create_envp()
{
	std::map<std::string, std::string> envp;

	// SERVER VARIABLES
	envp["SERVER_SOFTWARE"] = "WEBSERV/42.0";
	envp["SERVER_NAME"] = "127.0.0.1";//need ip from current server(or maybe name of server?) TODO
	envp["GATEWAY_INTERFACE"] = "CGI/1.1";

	// REQUEST DEFINED VARIABLES
	envp["SERVER_PROTOCOL"] = "HTTP/1.1";
	envp["SERVER_PORT"] = request.getPort();
	if (request.getMethod() == "GET")
		envp["REQUEST_METHOD"] = "GET";
	else if (request.getMethod() == "POST")
		envp["REQUEST_METHOD"] = "POST";
	envp["REDIRECT_STATUS"] = ft::itostr(200);
	envp["PATH_INFO"] = request.getPath();;
	envp["PATH_TRANSLATED"] = request.getPath();;
	envp["SCRIPT_NAME"] = request.getPath();;
	envp["SCRIPT_FILENAME"] = request.getPath();
	envp["QUERY_STRING"] = "";
	envp["REMOTE_HOST"] = "";
	envp["REMOTE_ADDR"] = "";
	envp["AUTH_TYPE"] = "";
	envp["REMOTE_USER"] = "";
	envp["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	envp["CONTENT_LENGTH"] = ft::itostr(request.getBody().size());

	// CLIENT VARIABLES
	envp["HTTP_ACCEPT"] = "*/*";
	envp["HTTP_ACCEPT_LANGUAGE"] = "en-US,en";
	envp["HTTP_REFERER"] = "";

	return mapToEnvp(envp);
}

void print_envp(char** envp)
{
	std::cerr << "this is the env :" << std::endl;
	for (int i = 0; envp[i] != NULL; i++)
		std::cerr << envp[i] << std::endl;
	std::cerr << "end of env :" << std::endl;
}

void Model::cgi_operation()
{
	int pid, fd[2];
	if (access(request.getPath().c_str(), X_OK) == -1)
		throw 403;
	if (pipe(fd) == -1)
		throw 503;
	pid = fork();
	if (pid == -1)
		throw 503;
	if (pid == 0)//child
	{
		close(fd[0]);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		//need dup2 for stdin to get the body of the request to the cgi
		std::string body = request.getBody();
		std::FILE* body_file = std::tmpfile();
		std::fputs(body.c_str(), body_file);
		std::rewind(body_file);
		if (dup2(fileno(body_file), STDIN_FILENO) == -1)
			exit(1);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
		std::string name = "/usr/bin/php-cgi";//maybe need to change this to a config variable, or if it's a Python CGI
		char* binary_path = strdup(name.c_str());
		char* progPath = strdup(request.getPath().c_str());
		char* argv[3] = {binary_path, progPath, NULL};
		char** envp = create_envp();
		execve(binary_path, argv, envp);
		for (int i = 0; envp[i] != NULL; i++)
			free(envp[i]);
		free(binary_path);
		free(progPath);
		free(envp);
		exit(0);
	}
	else if (pid > 0) //parent
	{
		int status;
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 0)
			{
				status_code = 200;
			}
			else
			{
				status_code = 500;
				response.setbody("CGI ERROR");
			}
		}
		int ret = 0;
		std::vector	<char> buffer(4096 + 1, 0);
		while ((ret = read(fd[0], buffer.data(), 4096)) > 0)
		{
			response.setbody(response.getbody() + std::string(buffer.begin(), buffer.end()));
			buffer.clear();
			buffer.resize(4096 + 1, 0);
		}
		close(fd[0]);
		if (ret == -1)
			throw 500;
	}
}
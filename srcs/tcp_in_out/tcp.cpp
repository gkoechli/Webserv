#include "tcp.hpp"
#include <sys/socket.h>
#include <cstdlib>

//SETUP
Tcp_handler::Tcp_handler(char *config_file) : config_parser(config_file), multiplex(config_parser)
{

}

Tcp_handler::~Tcp_handler() {}

//MAIN LOOP

void	Tcp_handler::main_tcp_loop()
{
	 try {
        multiplex.init_epoll_events();
		while (1) //possibly signal catch to stop program correctly?
		{
			int	ready_fd_count;
			ready_fd_count = multiplex.get_count_of_ready_connections();//function to get num of ready fd from epoll struct (epoll_wait)
			// std::cout << "ready_fd = "<< ready_fd_count << std::endl;
			for (int i = 0; i < ready_fd_count; i++)
			{
				// std::cout << "event found"<< std::endl;
				struct epoll_event current_event;
				current_event = multiplex.get_ready_event(i);//function to get event 'i' in the list of ready events
				if (multiplex.is_valid_server_socket(current_event))
					multiplex.add_new_client_fd(current_event);
				else if (multiplex.is_event_request(current_event))
					read_from_client(current_event);
				else if (multiplex.is_event_response(current_event))
					write_to_client(current_event);
			}
		}
	}
	catch(const std::exception& e) {
		std::cerr << "Exception: "<< e.what() << '\n';
	}
}


void	Tcp_handler::read_from_client(struct epoll_event current_event)
{
	std::cout << "start or read op"<< std::endl;
	int fd = current_event.data.fd;
	std::vector<char> client_request_chunk = multiplex.read_request(fd);
	if (!client_request_chunk.size())
	{
		std::cout << "client_request_chunk empty"<< std::endl;
		return ;
	}
	buffer.add_chunk_to_request_buffer(fd, client_request_chunk);
	if (buffer.is_request_complete(fd))
	{
		std::vector<char> response;
		// try {
			response = parse_request(buffer.get_full_request(fd));//To complete, only print full request for now
		// } catch {
			// manage_error()
		// }
		multiplex.update_connection_status(fd, EPOLLOUT);//TODO!
		buffer.empty_request_buffer(fd);
		buffer.add_full_response_to_response_buffer(fd, response);
	}
}

void Tcp_handler::write_to_client(struct epoll_event current_event)
{
	int fd = current_event.data.fd;
	std::vector<char> next_chunk = buffer.get_next_response_bloc(fd);
	int	send_count = buffer.get_count_send(fd);
	std::vector<char> response;

	response = next_chunk;
	response.push_back('\r');
	response.push_back('\n');//maybe should be done in get_next_response method?
	multiplex.send_response(response, fd);
	if (!next_chunk.size() && send_count % 2 == 1)
		multiplex.update_connection_status(fd, EPOLLIN);
	if (!next_chunk.size() && send_count % 2 == 1)
	{
		buffer.empty_response_buffer(fd);
		close (fd);
	}
	else
		buffer.increment_response_count(fd);
}

std::vector<char> response_mockup_builder()
{
	std::string mock = "HTTP/1.1 200 OK\n"
	"Content-Type: text/html; charset=utf-8\n"
	"Content-Length: 55743\n"
	"Connection: keep-alive\n"
	"Cache-Control: s-maxage=300, public, max-age=0\n"
	"Content-Language: en-US\n"
	"Date: Thu, 06 Dec 2018 17:37:18 GMT\n"
	"ETag: /\"2e77ad1dc6ab0b53a2996dfd4653c1c3\"\n"
	"Server: meinheld/0.6.1\n"
	"Strict-Transport-Security: max-age=63072000\n"
	"X-Content-Type-Options: nosniff\n"
	"X-Frame-Options: DENY\n"
	"X-XSS-Protection: 1; mode=block\n"
	"Vary: Accept-Encoding,Cookie\n"
	"Age: 7\n"
	"\n"
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
	"\n";
	// std::string s = "Hello World!";

    std::vector<char> res(mock.begin(), mock.end());

	return (res);
}

std::vector<char>	Tcp_handler::parse_request(std::vector<char> request)
{

	std::vector<char> response_mockup;
	response_mockup = response_mockup_builder();
	//TODO
	//Exec execution(request, &config_parser);
	//return(execution.get_response_as_string());

	//just need to print full request for now
	std::string output(request.begin(), request.end());
	std::cout << "content of request buffer = " << output << std::endl;
	return(response_mockup);
}
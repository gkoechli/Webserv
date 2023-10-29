#include "tcp.hpp"
#include <sys/socket.h>
#include <cstdlib>

//SETUP
Tcp_handler::Tcp_handler(char *config_file) : config_parser(config_file), multiplex(config_parser)
{}

Tcp_handler::~Tcp_handler()
{}

//MAIN LOOP
void	Tcp_handler::main_tcp_loop()
{
	try {
        multiplex.init_epoll_events();
		while (1) //possibly signal catch to stop program correctly?
		{
			int	ready_fd_count;
			ready_fd_count = multiplex.get_count_of_ready_connections();//function to get num of ready fd from epoll struct (epoll_wait)
			std::cout << "ready_fd = "<< ready_fd_count << std::endl;//only for debug, TODELETE
			for (int i = 0; i < ready_fd_count; i++)
			{
				std::cout << "event found"<< std::endl;//only for debug, TODELETE
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
	std::cout << "start or read op"<< std::endl;//only for debug, TODELETE
	int fd = current_event.data.fd;
	std::vector<char> client_request_chunk = multiplex.read_request(fd);
	if (!client_request_chunk.size())
	{
		std::cout << "client_request_chunk empty"<< std::endl;//only for debug, TODELETE
		//TODO throw error
		return ;
	}
	buffer.add_chunk_to_request_buffer(fd, client_request_chunk);
	if (buffer.is_request_complete(fd))
	{
		std::cout << "request is complete2"<< std::endl;//only for debug, TODELETE
		std::vector<char> response;
		response = parse_request(buffer.get_full_request(fd));
		multiplex.update_connection_status(fd, EPOLLOUT);
		buffer.empty_request_buffer(fd);
		buffer.add_full_response_to_response_buffer(fd, response);
	}
}

void Tcp_handler::write_to_client(struct epoll_event current_event)
{
	try {
		std::cout << "start of write to client"<< std::endl;//only for debug, TODELETE
		int fd = current_event.data.fd;
		std::vector<char> next_chunk = buffer.get_next_response_bloc(fd);
		std::vector<char> response;

		response = next_chunk;
		response.push_back('\r');
		response.push_back('\n');//maybe should be done in get_next_response method?

		std::string output(response.begin(), response.end());//only for debug, TODELETE
		std::cout << output <<std::endl;//only for debug, TODELETE
		multiplex.send_response(response, fd);
		if (!next_chunk.size() || buffer.is_request_fully_sent(fd))
		{
			std::cerr << "finished writing to client"<< std::endl;//only for debug, TODELETE
			multiplex.update_connection_status(fd, EPOLLIN);
			buffer.empty_response_buffer(fd);
			close (fd);
			return;
		}
		else
			buffer.increment_response_count(fd);
	}
	catch(const std::exception& e) {
		close(current_event.data.fd);
		buffer.empty_response_buffer(current_event.data.fd);
		std::cerr << "Exception: "<< e.what() << '\n';
	}
}

std::vector<char>	Tcp_handler::parse_request(std::vector<char> request)
{
	std::string request_as_string(request.begin(), request.end());
	Exec	current_exec(request_as_string, config_parser);
	std::vector<char> response;
	response = current_exec.return_final_response();
	// std::string output(request.begin(), request.end());//just to print full request
	// std::cout << "content of request buffer = " << output << std::endl;
	return(response);
}
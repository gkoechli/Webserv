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
				// else if (is_event_response(current_event))
					// write_to_client(current_event);
			}
		}
	}
	catch(const std::exception& e) {
		std::cerr << "Exception: "<< e.what() << '\n';
	}
}

// bool	Tcp_handler::is_event_response(struct epoll_event current_event)
// {
// 	if (current_event.events & EPOLLOUT)
// 		return true;
// 	return false;
// }

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
		// try {
			parse_request(buffer.get_full_request(fd));//To complete, only print full request for now
		// } catch {
			// manage_error()
		// }
		//update_connection_status(fd, EPOLLOUT);//TODO!
		buffer.empty_request_buffer(fd);
	}
}

// void Tcp_handler::write_to_client(struct epoll_event current_event)
// {
// 	int fd = current_event.data.fd;
// 	std::vector<char> next_chunk = buffer.get_next_response_bloc(fd);
// 	std::vector<char> response;

// 	response = chunk;
// 	response.push_back('\r');
// 	response.push_back('\n');//maybe should be done in get_next_response method?
// 	send_response(response, fd);
// 	if (!is_request_over())
// 		update_connection_status(fd, EPOLLIN);
// 	if (is_request_over() && is_connection_over(fd))
// 	{
// 		buffer.empty_response_buffer(fd);
// 		close (fd);
// 	}
// 	else
// 		buffer.increment_response_count(fd);
// }

// void	Tcp_handler::send_response(std::vector<char> response, int fd)
// {
// 	if (send(fd, &request[0], request.size(), 0) <= 0)
// 		throw;
// }

void	Tcp_handler::parse_request(std::vector<char> request)
{
	//TODO
	//just need to print full request for now
	std::string output(request.begin(), request.end());
	std::cout << "content of request buffer = " << output << std::endl;
}
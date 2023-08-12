#include "tcp.hpp"
#include <sys/socket.h>
#include <cstdlib>

//SETUP
Tcp_handler::Tcp_handler(char *config_file) : config_parser(config_file)
{
	//launch epoll bind for main port, depending on settings
	//can't do too much of it without a proper setting parser yet
	// this->settings.set_settings(this->config_parser);
	epoll_instance_fd = epoll_create(10);
	// for (int i = 0; i < listen_port_count; i++)
	// {
		// bind_port_to_socket(atoi(tmp.second.c_str()), INADDR_ANY);
	// }
	std::pair<std::string, std::string> tmp = config_parser.getListenPort();
	std::cout << tmp.first << " ----------> " << tmp.second << std::endl;
	std::cout << config_parser.getKeyContent("cli_max_size") << std::endl;
	bind_port_to_socket(atoi(tmp.second.c_str()), 16777343);
	//maybe need to use inet_aton() to convert ip string to correct format?
	//probably need to reimplement it
}

Tcp_handler::~Tcp_handler() {}

void	Tcp_handler::bind_port_to_socket(int port, int ip)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd <= 0)
	{
		std::cout << "error"<< std::endl;
	}
	struct sockaddr_in address = init_address(port, ip);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cout << "error"<< std::endl;
	}
	if (listen(server_fd, 100) < 0)
	{
		std::cout << "error"<< std::endl;
	}
	add_socket_to_epoll_list(server_fd);
}

struct sockaddr_in Tcp_handler::init_address(int port, int ip)
{
	(void)ip;
	struct sockaddr_in address;

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	return (address);
}

//MAIN LOOP

void	Tcp_handler::main_tcp_loop()
{
	while (1) //possibly signal catch to stop program correctly?
	{
		// std::cout << "lol4"<< std::endl;
		int	ready_fd_count;
		ready_fd_count = get_count_of_ready_connections();//function to get num of ready fd from epoll struct (epoll_wait)
		// std::cout << "ready_fd = "<< ready_fd_count << std::endl;
		for (int i = 0; i < ready_fd_count; i++)
		{
			// std::cout << "event found"<< std::endl;
			struct epoll_event current_event;
			current_event = get_ready_event(i);//function to get event 'i' in the list of ready events
			if (is_new_connection(current_event))
				add_new_client_fd(current_event);
			else if (is_event_request(current_event))
				read_from_client(current_event);
			// else if (is_event_response(current_event))
				// write_to_client(current_event);
		}
	}
}

int	Tcp_handler::get_count_of_ready_connections()
{
	int ready_fd_count;
	ready_fd_count = epoll_wait(epoll_instance_fd, epoll_ready_event_list, 64, 5000);
	if (ready_fd_count == -1)
	{
		std::cout << "error epollwait"<< std::endl;
		throw;
	}
	return ready_fd_count;
}

struct epoll_event Tcp_handler::get_ready_event(int i)
{
	return epoll_ready_event_list[i];
}

//ACCEPT NEW CONNECTIONS

void	Tcp_handler::add_new_client_fd(struct epoll_event current_event)
{
	std::cout << "new connection"<< std::endl;
	int new_fd = current_event.data.fd;
	int	new_connection = accept_new_fd(new_fd);

	setup_connection(new_connection);
	add_socket_to_epoll_list(new_connection);
}

int	Tcp_handler::accept_new_fd(int new_fd)
{
	int new_connection = accept(new_fd, NULL, NULL);
	if (new_connection < 0)
	{
		//throw
	}
	return new_connection;
}

void	Tcp_handler::setup_connection(int new_connection)
{
	int optval = 1;
	if (setsockopt(new_connection, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(int)) < 0)
	{
		//throw
	}
}

void	Tcp_handler::add_socket_to_epoll_list(int new_connection)
{
	struct epoll_event	events_to_monitor;

	memset((char *)&events_to_monitor, 0, sizeof(events_to_monitor));
	events_to_monitor.events = EPOLLIN | EPOLLRDHUP;// EPOLLRDHUP is for monitoring peer shutdown, need more research
	events_to_monitor.data.fd = new_connection;
	if (epoll_ctl(epoll_instance_fd, EPOLL_CTL_ADD, new_connection, &events_to_monitor) == -1)
	{
		// throw
	}
	// list_of_listen_sockets_fd.push_back(new_connection);
}

//BOOL FUNCTIONS

bool	Tcp_handler::is_new_connection(struct epoll_event current_event)
{
	int fd = current_event.data.fd;
	for (std::vector<int>::iterator it = list_of_listen_sockets_fd.begin(); it != list_of_listen_sockets_fd.end(); it++)
	{
		if (fd == *it)
		return false;
	}
	return true;
}

bool	Tcp_handler::is_event_request(struct epoll_event current_event)
{
	if (current_event.events & EPOLLIN)
		return true;
	return false;
}

bool	Tcp_handler::is_event_response(struct epoll_event current_event)
{
	if (current_event.events & EPOLLOUT)
		return true;
	return false;
}

//BULLSHIT

void	Tcp_handler::read_from_client(struct epoll_event current_event)
{
	int fd = current_event.data.fd;
	std::vector<char> client_request_chunk = read_request(fd);

	if (!client_request_chunk.size())
		return ;
	buffer.add_chunk_to_request_buffer(fd, client_request_chunk);
	if (buffer.is_request_complete(fd))
	{
		// try {
			parse_request(buffer.get_full_request(fd));//To complete, only print full request for now
		// } catch {
			// manage_error()
		// }
		//update_connection_status(fd, EPOLLOUT);
		buffer.empty_request_buffer(fd);
	}
}

std::vector<char> Tcp_handler::read_request(int client_fd)
{
	std::vector<char> buffer(8192, '\0');
	int ret;

	ret = recv(client_fd, &buffer[0], buffer.size(), 0);
	buffer.resize(ret);
	return (buffer);
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
	//just need to print full request
	std::string output(request.begin(), request.end());
	std::cout << output;
}
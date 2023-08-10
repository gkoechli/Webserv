#include "tcp.hpp"
#include <sys/socket.h>
#include <cstdlib>

//SETUP
Tcp_handler::Tcp_handler(char *config_file) : config_parser(config_file)
{
	//launch epoll bind for main port, depending on settings
	//can't do too much of it without a proper setting parser yet
	// this->settings.set_settings(this->config_parser);
	epoll_instance_fd = epoll_create(1);
	// for (int i = 0; i < listen_port_count; i++)
	// {
		// bind_port_to_socket(atoi(tmp.second.c_str()), INADDR_ANY);
	// }
	std::pair<std::string, std::string> tmp = config_parser.getListenPort();
	std::cout << tmp.first << " ----------> " << tmp.second << std::endl;
	std::cout << config_parser.getKeyContent("cli_max_size") << std::endl;
	bind_port_to_socket(atoi(tmp.second.c_str()), INADDR_ANY);
	//maybe need to use inet_aton() to convert ip string to correct format?
	//probably need to reimplement it
}

Tcp_handler::~Tcp_handler() {}

void	Tcp_handler::bind_port_to_socket(int port, int ip)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd <= 0)
	{
		//throw
	}
	struct sockaddr_in address = init_address(port, ip);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		// throw
	}
}

struct sockaddr_in Tcp_handler::init_address(int port, int ip)
{
	struct sockaddr_in address;

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(ip);
	address.sin_port = htons(port);

	return (address);
}

//MAIN LOOP

void	Tcp_handler::main_tcp_loop()
{
	while (1) //possibly signal catch to stop program correctly?
	{
		int	ready_fd_count;
		ready_fd_count = get_count_of_ready_connections();//function to get num of ready fd from epoll struct (epoll_wait)
		for (int i = 0; i < ready_fd_count; i++)
		{
			struct epoll_event current_event;
			current_event = get_ready_event(i);//function to get event 'i' in the list of ready events
			if (is_new_connection(current_event))
				add_new_client_fd(current_event);
			// else if (is_event_request(current_event))
			// 	// read_from_client(current_event);
			// else if (is_event_response(current_event))
			// 	// write_to_client(current_event);
		}
	}
}

int	Tcp_handler::get_count_of_ready_connections()
{
	int ready_fd_count;
	ready_fd_count = epoll_wait(epoll_instance_fd, epoll_ready_event_list, MAX_EVENTS, 5000);
	if (ready_fd_count == -1)
	{
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
	if (epoll_ctl(epoll_instance_fd, EPOLL_CTL_ADD, new_connection, &events_to_monitor))
	{
		// throw
	}
}

//BOOL FUNCTIONS

bool	Tcp_handler::is_new_connection(struct epoll_event current_event)
{
	(void)current_event;
	// for (/*vector of current connections*/)
	// {
	// 	if (current_event_.data.fd == current_vector_fd)
	// 	return false;
	// }
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

// void	Tcp_handler::read_from_client(int fd)
// {
// 	struct epoll_event& epoll_event = epoll_event_buffer[i];
// 	// Handle the event now, by reading in data and printing it.
// 	const int fd = epoll_event.data.fd;
// 	char buffer[1024] = {0};

// 	//need a function to know if request is in or out
// 	/*//if (request_is_in()) do i check if EPOLLIN is set? or do i just see if it's ready?
// 	{
// 		read in request(need to start parsing if in request is done)
// 	}
// 	else
// 		write out request
// 	*/
// 	int valread = read(fd, buffer, 1024);
// 	printf("%s\n", buffer);
// 	printf("Bytes read: %d\n", valread);
// 	std::string s ="Hello from the server";
// 	const char *hello = s.c_str();
// 	write(fd, hello, strlen(hello));
// 	epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &epoll_event);
// 	close(fd);
// }
#include "multiplexer.hpp"

Multiplexer::Multiplexer(configParsing config_parser) : epoll_instance_fd(-1)
{
	try {
		std::pair<std::string, std::string> tmp = config_parser.getListenPort();
		std::cout << tmp.first << " ----------> " << tmp.second << std::endl;
		std::cout << config_parser.getKeyContent("cli_max_size") << std::endl;
		// for (int i = 0; i < listen_port_count; i++)//need a loop to manage multiple server/ip/port
	// {
			int	server_socket = create_server_socket(atoi(tmp.second.c_str()), 16777343);
	// }
		list_of_listen_sockets_fd.push_back(server_socket);
		//maybe need to use inet_aton() to convert ip string to correct format?
		//probably need to reimplement it
	}
	catch (const std::exception &e) {
        throw (MultiplexerException(LISTENERR));
    }
	// std::cout << "multiplexer constructed"<< std::endl;
}

Multiplexer::~Multiplexer() {
	//TODO
	// will need a clean fd close loop
}

	//Start of server
int	Multiplexer::create_server_socket(int port, int ip)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd <= 0)
        throw (MultiplexerException(INITSOCKERR));
	struct sockaddr_in address = init_address(port, ip);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw (MultiplexerException(BINDERR));
	if (listen(server_fd, 100) < 0)
        throw (MultiplexerException(LISTENERR));
	return (server_fd);
}

struct sockaddr_in Multiplexer::init_address(int port, int ip)
{
	(void)ip;
	struct sockaddr_in address;

	std::memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	return (address);
}

void	Multiplexer::add_socket_to_epoll_list(int new_connection)
{
	struct epoll_event	events_to_monitor;

	memset((char *)&events_to_monitor, 0, sizeof(events_to_monitor));
	events_to_monitor.events = EPOLLIN | EPOLLRDHUP;// EPOLLRDHUP is for monitoring peer shutdown, need more research
	events_to_monitor.data.fd = new_connection;
	if (epoll_ctl(epoll_instance_fd, EPOLL_CTL_ADD, new_connection, &events_to_monitor) == -1)
        throw (MultiplexerException(EPOLLCTLERR));
}
	//New connection
void	Multiplexer::setup_connection(int new_connection)
{
	int optval = 1;
	if (setsockopt(new_connection, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(int)) < 0)
        throw (MultiplexerException(SETSOCKOPTERR));
}

	//Main loop

void	Multiplexer::init_epoll_events()
{
	if ((epoll_instance_fd = epoll_create(10)) < 0){
		throw (MultiplexerException(EPOLLCREATEERR));
	}
	for (size_t i = 0; i < list_of_listen_sockets_fd.size(); i++)
		add_socket_to_epoll_list(list_of_listen_sockets_fd[i]);
}

int	Multiplexer::get_count_of_ready_connections()
{
	int ready_fd_count;
	ready_fd_count = epoll_wait(epoll_instance_fd, epoll_ready_event_list, 5, 5000);
	if (ready_fd_count == -1)
        throw (MultiplexerException(EPOLLWAITERR));
	return ready_fd_count;
}

struct epoll_event Multiplexer::get_ready_event(int i)
{
	return epoll_ready_event_list[i];
}

void	Multiplexer::add_new_client_fd(struct epoll_event current_event)
{
	std::cout << "start of add client op"<< std::endl;
	int new_fd = current_event.data.fd;
	int	new_connection = accept_new_fd(new_fd);
	std::cout << "fd = " << new_fd <<" socket= " <<new_connection<< std::endl;

	setup_connection(new_connection);
	add_socket_to_epoll_list(new_connection);
}

int	Multiplexer::accept_new_fd(int new_fd)
{
	int new_connection = accept(new_fd, NULL, NULL);
	if (new_connection < 0)
        throw (MultiplexerException(ACCEPTERR));
	return new_connection;
}

bool	Multiplexer::is_valid_server_socket(struct epoll_event current_event)
{
	int fd = current_event.data.fd;
	for (std::vector<int>::iterator it = list_of_listen_sockets_fd.begin(); it != list_of_listen_sockets_fd.end(); it++)
	{
		if (fd == *it)
		{
			std::cout << "i got a new connection, fd = "<< fd << std::endl;
			return true;
		}
	}
	return false;
}

bool	Multiplexer::is_event_request(struct epoll_event current_event)
{
	if (current_event.events & EPOLLIN)
		return true;
	return false;
}


bool	Multiplexer::is_event_response(struct epoll_event current_event)
{
	if (current_event.events & EPOLLOUT)
		return true;
	return false;
}

std::vector<char> Multiplexer::read_request(int client_fd)
{
	std::cout << "start of client rcv string op"<< std::endl;
	std::vector<char> bufferres(MAXBUF, '\0');

	int ret;

	std::cout << "gate0 fd = "<< client_fd << std::endl;
	if ((ret = recv(client_fd, &bufferres[0], bufferres.size(), 0)) < 0)
        throw (MultiplexerException(RECEIVEERR));
	std::cout << "gate1 "<<std::endl;
	bufferres.resize(ret);
	std::cout << "gate2"<< std::endl;
	return (bufferres);
}


void	Multiplexer::update_connection_status(int fd, int event)
{
	struct epoll_event new_event;

	memset((char *)&new_event, 0, sizeof(new_event));
	new_event.events = event | EPOLLRDHUP;
	new_event.data.fd = fd;
	if (epoll_ctl(epoll_instance_fd, EPOLL_CTL_MOD, fd, &new_event) == -1)
        throw (MultiplexerException(EPOLLCTLERR));
}

/** EXCEPTIONS **/

Multiplexer::MultiplexerException::MultiplexerException(std::string msg) : m_msg(msg) {}

Multiplexer::MultiplexerException::~MultiplexerException() throw() {}

const char *Multiplexer::MultiplexerException::what() const throw() {
    return (m_msg.c_str());
}
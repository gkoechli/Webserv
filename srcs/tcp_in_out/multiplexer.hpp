#ifndef MULTIPLEXER
# define MULTIPLEXER

#include <sys/epoll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>//needed for sockaddr_in
#include <iostream>
#include <string.h>
#include "../config_file_parsing/configParsing.hpp"
#include "utils.hpp"

# define INITSOCKERR            "Socket() failed."
# define SETSOCKOPTERR          "setsockopt() failed."
# define FCNTLERR               "fcntl() failed : could not set socket to be non blocking."
# define BINDERR                "bind() failed."
# define LISTENERR              "listen() failed."
# define EPOLLCREATEERR         "epoll_create() failed."
# define EPOLLCTLERR            "epoll_ctl() failed."
# define EPOLLWAITERR           "epoll_wait() failed."
# define ACCEPTERR              "accept() failed."
# define RECEIVEERR             "receive() failed."
# define SENDERR                "send() failed."
# define IPERR                	"Wrong Ip address format."

# define MAXBUF 8192
# define MAX_EVENTS 5

class Multiplexer {
	private:
		int	epoll_instance_fd;
		struct epoll_event	epoll_ready_event_list[MAX_EVENTS];
		std::vector<int> list_of_listen_sockets_fd;
	public:
		Multiplexer(configParsing config_parser);
		~Multiplexer();

	class MultiplexerException : public std::exception {
		private:
			std::string m_msg;

		public:
			MultiplexerException(std::string msg);
			~MultiplexerException() throw();
			const char *what() const throw();
    };
		//Start of server
		int	create_server_socket(int port, int ip);
		struct sockaddr_in init_address(int port, int ip);
		void	add_socket_to_epoll_list(int new_connection);
		void	setup_connection(int new_connection);
		//New connection
		//Main loop
		void	init_epoll_events();
		int		get_count_of_ready_connections();
		struct	epoll_event get_ready_event(int i);
		void	add_new_client_fd(struct epoll_event current_event);
		int		accept_new_fd(int new_fd);
		bool	is_valid_server_socket(struct epoll_event current_event);
		bool	is_event_request(struct epoll_event current_event);
		bool	is_event_response(struct epoll_event current_event);
		std::vector<char> read_request(int client_fd);
		void	send_response(std::vector <char> response, int fd);
		void	update_connection_status(int fd, int event);


		uint32_t convert_ip_to_int(std::string string_ip);

};

#endif
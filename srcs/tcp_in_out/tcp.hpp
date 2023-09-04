#ifndef TCP_HANDLER
# define TCP_HANDLER

#include <sys/epoll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>//needed for sockaddr_in
#include <iostream>
#include <string.h>
#include <cstring>
#include "../config_file_parsing/configParsing.hpp"
#include "../exec/exec.hpp"
#include "./client_buffer.hpp"
#include "./multiplexer.hpp"

// #include "client_buffer.hpp"

class Tcp_handler
{
	private:
		configParsing config_parser;
		// configClass settings;
		ClientBuffer buffer;
		Multiplexer multiplex;
		// setting_obj settings; // for parameters at start (listen ports and max request size)
		// int	epoll_instance_fd;
		// struct epoll_event	epoll_ready_event_list[MAX_EVENTS];
		// std::vector<int> list_of_listen_sockets_fd;
	public:
		//setup/teardown step
		Tcp_handler(char *config_file);//builder, will need settings to properly setup
		~Tcp_handler();
		// sockaddr_in init_address(int port, int ip);
		// void	bind_port_to_socket(int port, int ip);

		//start of main loop
		void	main_tcp_loop();
		int		get_count_of_ready_connections();
		// struct epoll_event get_ready_event(int i);
		// int		accept_new_fd(int new_fd);
		// void	setup_connection(int new_connection);
		// void	add_socket_to_epoll_list(int new_connection);

		//get info
		bool	is_new_connection(struct epoll_event current_event);
		bool	is_event_request(struct epoll_event current_event);
		bool	is_event_response(struct epoll_event current_event);

		//actions
		// void	add_new_client_fd(struct epoll_event current_event);

		// std::vector<char> read_request(int client_fd);
		void	read_from_client(struct epoll_event current_event);
		std::vector<char> read_request(int client_fd);
		void	write_to_client(struct epoll_event current_event);
		std::vector<char>	parse_request(std::vector<char> request);
};

#endif
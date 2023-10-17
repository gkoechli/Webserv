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

#define ERROR 1
#define SUCCESS 0 

class Tcp_handler
{
	private:
		configParsing config_parser;
		ClientBuffer buffer;
		Multiplexer multiplex;
		// setting_obj settings; // for parameters at start (listen ports and max request size)
	public:
		Tcp_handler(char *config_file);//builder, will need settings to properly setup
		~Tcp_handler();

		//start of main loop
		void	main_tcp_loop();
		int		get_count_of_ready_connections();

		//get info
		bool	is_new_connection(struct epoll_event current_event);
		bool	is_event_request(struct epoll_event current_event);
		bool	is_event_response(struct epoll_event current_event);

		//actions
		void				read_from_client(struct epoll_event current_event);
		std::vector<char>	read_request(int client_fd);
		void				write_to_client(struct epoll_event current_event);
		std::vector<char>	parse_request(std::vector<char> request);
};

#endif
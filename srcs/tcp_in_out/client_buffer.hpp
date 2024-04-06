#ifndef BUFFER_CLIENT
# define BUFFER_CLIENT

# include <map>
# include <vector>
# include <algorithm>
# include <string>
# include <iostream>
# include <sstream>
# include <iostream>
#include "utils.hpp"

# define CHUNK_SIZEMAX  32768

class ClientBuffer{
	private:
		std::map<int, std::vector<char> >	request_buffer;//map of request from clients, with int corresponding to individual client socket
		std::map<int, std::pair<int, std::vector<char> > >	response_buffer;//map of response for clients, with int corresponding to individual client socket
	public:
		ClientBuffer(void);
		~ClientBuffer();

		void	add_chunk_to_request_buffer(int fd, std::vector<char>);
		void	add_full_response_to_response_buffer(int fd, std::vector<char>);
		void	empty_request_buffer(int fd);
		void	empty_response_buffer(int fd);
		//getter
		std::vector<char>	get_full_request(int fd);//to send full html client request to request parser/exec
		std::vector<char>	get_next_response_bloc(int fd);//to send next part of response to client asking it

		void	increment_response_count(int fd);
		int		get_count_send(int fd);

		//bool function
		bool	is_request_existing(int fd);
		bool	is_request_fully_sent(int fd);
		bool	is_request_complete(int fd);
};

#endif
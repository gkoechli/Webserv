#ifndef BUFFER_CLIENT
# define BUFFER_CLIENT

# include <map>
# include <vector>
#include <iostream>
# include <string>

# define CHUNK_SIZEMAX  32768

class ClientBuffer{
	private:
		std::map<int, std::vector<char> >	request_buffer;//map of request from clients, with int corresponding to individual client socket
		std::map<int, std::vector<char>>	response_buffer;//map of response for clients, with int corresponding to individual client socket
	public:
		ClientBuffer(void);
		~ClientBuffer();

		void	add_chunk_to_request_buffer(int fd, std::vector<char>);
		// void	add_full_response_to_response_buffer(int fd, std::vector<char>);
		void	empty_request_buffer(int fd);
		// void	empty_response_buffer(int fd);
		//getter
		std::vector<char>	get_full_request(int fd);//to send full html client request to request parser/exec
		std::vector<char>	get_next_response_bloc(fd);//to send next part of response to client asking it
		//will probably need subfunctions to work
		//bool function
		bool	is_request_existing(int fd);
		// bool	is_request_oversized(int fd);
		bool	is_request_complete(int fd);
};

#endif
#include "client_buffer.hpp"

	ClientBuffer(void){}

	~ClientBuffer(){}

	void	add_bloc_to_request_buffer(int fd, std::vector<char>)
	void	add_full_response_to_response_buffer(int fd, std::vector<char>)
	void	empty_request_buffer(int fd)
	void	empty_response_buffer(int fd)
	//getter
	std::vector<char>	get_full_request(fd)//to send full html client request to request parser/exec
	std::vector<char>	get_next_response_bloc(fd)//to send next part of response to client asking it
	//will probably need subfunctions to work

	//bool function
	bool	is_request_existing(int fd)
	{
		//TODO
		//if fd is allready in map -> false
	}
	bool	is_request_oversized(int fd)
	{
		//TODO
		//check num of char and compare to maxsize
		//will need hexa conversion i think
	}
	bool	is_request_complete(int fd)
	{
		//TODO
		//if maxsize or if end char are expected for end (/r/n or something)
	}
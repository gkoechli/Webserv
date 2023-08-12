#include "client_buffer.hpp"

	ClientBuffer::ClientBuffer(void){}

	ClientBuffer::~ClientBuffer(){}

	void	ClientBuffer::add_chunk_to_request_buffer(int fd, std::vector<char> chunk)
	{
		std::map<int, std::vector<char> >::iterator it = request_buffer.find(fd);
		if (!is_request_existing(fd))
			request_buffer.insert(std::make_pair(fd, chunk));
		else {
			it->second.insert(it->second.end(), chunk.begin(), chunk.begin() + chunk.size());
		}
	}
	// void	add_full_response_to_response_buffer(int fd, std::vector<char> response)
	// {
	// 	response_buffer.insert(std::make_pair(fd, std::vector<char>(response.begin(), response.end())));
	// }
	void	ClientBuffer::empty_request_buffer(int fd)
	{
		request_buffer.erase(fd);
	}

	// void	empty_response_buffer(int fd)
	// {
	// 	response_buffer.erase(fd);
	// }

	//getter
	std::vector<char>	ClientBuffer::get_full_request(int fd)//to send full html client request to request parser/exec
	{
		std::vector<char> request = request_buffer.find(fd)->second;
		return request;
	}
	// std::vector<char>	get_next_response_bloc(int fd)//to send next part of response to client asking it
	// {

	// }

	//will probably need subfunctions to work

	//bool function
	bool	ClientBuffer::is_request_existing(int fd)
	{
		if (request_buffer.find(fd) == request_buffer.end())
			return (false);
		return (true);
	}

	// bool	is_request_oversized(int fd)
	// {
	// 	//TODO
	// 	//check num of char and compare to maxsize
	// 	//will need hexa conversion i think
	// }
	bool	ClientBuffer::is_request_complete(int fd)
	{
		(void)fd;
		return (true);
		//TODO
		//if maxsize or if end char are expected for end (/r/n or something)
	}
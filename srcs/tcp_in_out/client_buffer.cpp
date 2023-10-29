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
void	ClientBuffer::add_full_response_to_response_buffer(int fd, std::vector<char> response)
{
    response_buffer.insert(std::make_pair(fd, std::make_pair(2, std::vector<char>(response.begin(), response.end()))));

	std::vector<char> response_in_buffer = (response_buffer.find(fd))->second.second;
	std::string output(response_in_buffer.begin(), response_in_buffer.end());
	std::cout << "content of response buffer added = " << output << std::endl;
}

void	ClientBuffer::empty_request_buffer(int fd)
{
	request_buffer.erase(fd);
}

void	ClientBuffer::empty_response_buffer(int fd)
{
	response_buffer.erase(fd);
}

//getter
std::vector<char>	ClientBuffer::get_full_request(int fd)//to send full html client request to request parser/exec
{
	std::vector<char> request = request_buffer.find(fd)->second;
	return request;
}

std::vector<char>	ClientBuffer::get_next_response_bloc(int fd)//to send next part of response to client asking it
{

	std::vector<char>   response = (response_buffer.find(fd))->second.second;
    std::vector<char>   new_response;
    std::vector<char>   chunk;
    int                 size_return = (response_buffer.find(fd))->second.first;

    if (response.size() && response.size() >= CHUNK_SIZEMAX)
        chunk.insert(chunk.end(), response.begin(), response.begin() + CHUNK_SIZEMAX);
    else if (response.size() && response.size() < CHUNK_SIZEMAX)
        chunk.insert(chunk.end(), response.begin(), response.end());
    if (size_return % 2 == 0)
        return (chunk);
    if (response.size() >= CHUNK_SIZEMAX)
        new_response.insert(new_response.end(), response.begin() + CHUNK_SIZEMAX, response.end());
    response_buffer.erase(fd);
    response_buffer.insert(std::make_pair(fd, std::make_pair(size_return, new_response)));
    return (chunk);
}

//bool function
bool	ClientBuffer::is_request_existing(int fd)
{
	if (request_buffer.find(fd) == request_buffer.end())
		return (false);
	return (true);
}

int	search_vector_char(std::vector<char> tab, const char *to_find, size_t index)
{
	std::vector<char>::iterator it = std::search(tab.begin() + index, tab.end(), to_find, to_find + std::strlen(to_find));
	if (it == tab.end())
		return (-1);
	return (it - tab.begin());
}

bool	ClientBuffer::is_request_complete(int fd)
{
	std::vector<char>       req = request_buffer.find(fd)->second;
    size_t                  size_begin = search_vector_char(req, "Content-Length: ", 0) + 16;

    if (size_begin == 15)//if find == -1, there is no content-length, so request is complete
	{
        return (true);
	}
    size_t                  size_end = search_vector_char(req, "\r\n\r\n", size_begin);
    size_t                  size = ft::lexical_cast<size_t>(std::string(req.begin() + size_begin, req.begin() + size_end));
    size_t                  size_body = 0;

    for (std::vector<char>::iterator it = req.begin() + search_vector_char(req, "\r\n\r\n", 0) + 4; it != req.end(); it++)
        size_body++;
    if (size_body >= size)
	{
        return (true);
	}
    return (false);
}

bool ClientBuffer::is_request_fully_sent(int fd)
{
	std::vector<char> response = (response_buffer.find(fd))->second.second;
	if ((response_buffer.find(fd))->second.first * CHUNK_SIZEMAX >= static_cast<int>(response.size()))
		return true;
	return false;
}

void	ClientBuffer::increment_response_count(int fd)
{
	response_buffer.find(fd)->second.first++;
}


int		ClientBuffer::get_count_send(int fd)
{
	return (response_buffer.find(fd)->second.first);
}
#include "file_manager.hpp"

file_manager::file_manager(std::string path_to_file): fd(0)
{
	path = path_to_file;
	parse_name();
}

file_manager::~file_manager()
{
	close();
}

void file_manager::create(const std::string &file_content)
{
	fd = ::open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 00755);
	if (fd <= 0)
	{
		//TODO error to manage:  can't create file
	}
	if (file_content.length() && write(fd, file_content.c_str(), file_content.length()) <= 0)
	{
		//TODO error to manage:  can't write to new file that has been created
	}
}

bool file_manager::open()
{
	close();//should not be necessary, normally
	fd = ::open(path.c_str(), O_RDONLY);
		//TODO manage error: can't open file
	return fd > 0;
}

void file_manager::close()
{
	if (fd > 0)
	{
		::close(fd);
		fd = 0;
	}
}

void file_manager::append(const std::string &file_content) {
	close();
	fd = ::open(path.c_str(), O_RDWR | O_APPEND);
	if (fd < 0)
		return ;
	if (file_content.length() && write(fd, file_content.c_str(), file_content.length()) <= 0)
	{
		//TODO manage error: can't append to file that has been opened in O_APPEND mode (weird, meybe not really necessary)
	}
}

void file_manager::unlink()
{
	if (!exist())
		return ;
	if (::unlink(path.c_str()) == -1)
	{
	//TODO manage error:can't unlink file that exist (possible right problem?)
	}
}

void file_manager::parse_name()
{
	std::string name_with_extension = path.substr(path.find_last_of("/") + 1);
	file_name = name_with_extension;//do we need file extension?
	// std::string name = name_with_extension.substr(0, name_with_extension.find("."));
	// std::string extension = name_with_extension;
	// extension.erase(0, file,find("."));
}

bool file_manager::is_directory()
{
	struct stat file_stat;
	stat(path.c_str(), &file_stat);
	return S_ISDIR(file_stat.st_mode);
}

bool file_manager::exist()
{
	struct stat file_stat;
	return stat(path.c_str(), &file_stat) == 0;
}

// bool file_manager::is_empty()
// {
// 	std::ifstream File(path);
//     return File.peek() == std::ifstream::traits_type::eof();
// }

std::string file_manager::get_content_from_file()
{
	if (!exist() || is_directory())
	{
		throw 404;
	}
	if (access(path.c_str(), R_OK) == -1)
	{
		throw 403;
	}
	std::ifstream file(path.c_str());
	if (not file.good())
	{
		throw 503;
	}
	return (std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
}

// int file_manager::get_fd()
// {
// 	return fd;
// }
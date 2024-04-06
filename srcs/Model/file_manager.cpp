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
	std::ofstream ofs;
	ofs.open(path.c_str());

	if (file_content.length() && ofs.bad())
	{
		throw 403;
	}
	ofs	<< file_content;
	ofs.close();
}

bool file_manager::open()
{
	if (!exist())
	{
		throw 404;
	}
	close();//should not be necessary, normally
	fd = ::open(path.c_str(), O_RDONLY);
	if (fd <= 0)
		throw 401;
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
	close();
	std::ofstream ofs;
	ofs.open(path.c_str());

	if (file_content.length() && ofs.bad())
	{
		throw 422;
	}
	ofs	<< file_content;
	ofs.close();
}

void file_manager::unlink()
{
	if (!exist())
		return ;
	if (::unlink(path.c_str()) == -1)
	{
		throw 409;
	}
}

void file_manager::parse_name()
{
	std::string name_with_extension = path.substr(path.find_last_of("/") + 1);
	file_name = name_with_extension;
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

std::string file_manager::get_content_from_file()
{
	if (!exist())
	{
		throw 404;
	}
	if (is_directory())
	{
		throw 403;
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

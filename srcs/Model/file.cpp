#include "file.hpp"

File::File(std::string path_to_file) fd(0)
{
	path = path_to_file;
	parse_name();
}

File::~File()
{
	close();
}

void File::create(std::string &file_content)
{
	fd = ::open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 00755);
	if fd == 0
	(
		//TODO error to manage:  can't create file
	)
	if (file_content.length && write(fd, file_content.c_str(), file_content.length()) <= 0)
	{
	//TODO error to manage:  can't write to new file that has been created*/
	}
}

bool File::open()
{
	close();//should not be necessary, normally
	fd = ::open(path.c_str(), O_RDONLY);
	return fd > 0;
}

void File::close()
{
	if (fd > 0)
	{
		::close(fd);
		fd = 0;
	}
}

void File::append(std::string &file_content) {
	close();
	fd = ::open(path_.c_str(), O_RDWR | O_APPEND);
	if (fd < 0)
		return ;
	if (file_content.length() && write(fd, file_content.c_str(), file_content.length()) <= 0)
	{
		//TODO manage error: can't append to file that has been opened in O_APPEND mode (weird, meybe not really necessary)
	}
}

void File::unlink()
{
	if (!exist())
		return ;
	if (::unlink(path.c_str()) == -1)
	{
	//TODO manage error:can't unlink file that exist (possible right problem?)
	}
}

void File::parse_name()
{
	std::string name_with_extension = path.substr(path.find_last_of("/") + 1);
	file_name = name_with_extension;//do we need file extension?
	// std::string name = name_with_extension.substr(0, name_with_extension.find("."));
	// std::string extension = name_with_extension;
	// extension.erase(0, file,find("."));
}

bool File::is_directory()
{
	struct stat file_stat;
	stat(path.c_str(), &statbuf);
	return S_ISDIR(file_stat.st_mode);
}

bool File::exist()
{
	struct stat file_stat;
	return stat(path.c_str(), &file_stat) == 0;
}

bool File::is_empty()
{
	std::ifstream File(path);
    return File.peek() == std::ifstream::traits_type::eof();
}

std::string File::get_content_from_file()
{
	std::string content;
	char buffer[4096 + 1];
	int read_return;

	lseek(fd, 0, SEEK_SET);
	while (( read_return = read(fd, buffer, 4096)) != 0)
	{
		if (read_return < 0)
		{
			return "";
		}
		buffer[read_return] == '\0';
		content.insert(content.length(), buffer, read_return);
	}
	return content;
}

int &get_fd()
{
	return fd;
}
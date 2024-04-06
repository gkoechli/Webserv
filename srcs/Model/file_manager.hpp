#ifndef FILE_HPP
#define FILE_HPP


# include <sys/stat.h>
# include <utility>
# include <string>
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <fstream>
# include <vector>

# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>
# include <errno.h>
# include <cstdlib>
# include <algorithm>

class file_manager {
	private:
		int fd;
		std::string file_name;
		std::string path;

	public:
		file_manager(std::string path_to_file);
		~file_manager();

		void create(const std::string &file_content);
		void append(const std::string &file_content);
		bool open();
		void close();
		void unlink();

		void	parse_name();
		std::string get_content_from_file();
		bool exist();
		bool is_directory();
};

#endif
#ifndef FILE_HPP
#define FILE_HPP


# include <sys/stat.h>

class File {
	private:
		int fd;
		std::string file_name;
		std::string path;

	public:
		File(std::string path_to_file);
		~File();

		void create()
		void append()
		bool open();
		void close();
		void unlink();

		void	parse_name();
		std::string get_content_from_file();
		bool exist();
		bool is_empty();
		bool is_directory();

		// std::string last_modified();//not sure of use yet


	//Note: unless CGI need more infos, this should be enough for our current ambitions (no need to deal with file that are not texts)
};

#endif
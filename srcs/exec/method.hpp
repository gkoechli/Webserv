#ifndef METHOD
#define METHOD
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

//to use only once every possible check is done on request object
//should be garanteed do have all data necessary to at least try to exec the method
//once executed, get status and body => no more uses for current object
class Method{
	private:
		int	status_code;
		std::string response_content;
		std::string _path;
		//File_manip file;
		//Request_obj &request;//need to have all infos needed to exec
		//maybe a pointer to settings/request?
	public:
		Method(std::string path/*Request_obj &request*/);
		~Method();

		bool	is_empty();
		bool	check_error();
		// void extract_path_from_request(/*request object*/);

		void	method_get();
		// void	method_post();
		// void	method_delete();

		// std::string get_content();
		std::string get_path();
		int get_status_code();

};

// maybe make all that's possible here
//have CGI as a submodule of this object
//keep all datas here until response build step in exec;

#endif
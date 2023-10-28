#ifndef HTTPCODES_HPP
# define HTTPCODES_HPP

# include <string>

# define MAX_VALUE 599

class HttpCodes {

	private:
		std::string m_codes[MAX_VALUE + 1];
	public:
		HttpCodes();
		~HttpCodes();

		bool codeExist(int code) const;

		const std::string get_code_value(int code) const;
};

#endif
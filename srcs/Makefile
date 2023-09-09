NAME			=	ConfigParse

CXX 		=	c++

CXXFLAGS			= -Wall -Wextra -Werror -std=c++98

SRCS			=		main.cpp\
						client_request/ClientRequest.cpp \
						client_request/ClientBaseSettings.cpp \
						config_file_parsing/configParsing.cpp\
						config_file_parsing/serverClass.cpp\
						config_file_parsing/locationClass.cpp\
						tcp_in_out/tcp.cpp \
						tcp_in_out/multiplexer.cpp \
						tcp_in_out/client_buffer.cpp \
						exec/exec.cpp \
						exec/response.cpp

HEADERS		=	config_file_parsing/configParsing.hpp\
				config_file_parsing/serverClass.hpp\
				config_file_parsing/locationClass.hpp\
				tcp_in_out/tcp.hpp \
				tcp_in_out/multiplexer.hpp \
				tcp_in_out/client_buffer.hpp \
				exec/exec.hpp \
				exec/response.hpp

OBJ			=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all
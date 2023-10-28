NAME			=	Webserv

CXX 		=	c++

CXXFLAGS			= -Wall -Wextra -Werror -std=c++98

SRCS			=		srcs/main.cpp\
						srcs/client_request/ClientRequest.cpp \
						srcs/client_request/ClientBaseSettings.cpp \
						srcs/config_file_parsing/configParsing.cpp\
						srcs/config_file_parsing/serverClass.cpp\
						srcs/config_file_parsing/locationClass.cpp\
						srcs/tcp_in_out/tcp.cpp \
						srcs/tcp_in_out/multiplexer.cpp \
						srcs/tcp_in_out/client_buffer.cpp \
						srcs/Model/Model.cpp \
						srcs/Model/file_manager.cpp \
						srcs/exec/exec.cpp \
						srcs/exec/HttpCodes.cpp \
						srcs/exec/response.cpp

HEADERS		=	srcs/config_file_parsing/configParsing.hpp\
				srcs/config_file_parsing/serverClass.hpp\
				srcs/config_file_parsing/locationClass.hpp\
				srcs/client_request/ClientRequest.hpp \
				srcs/tcp_in_out/tcp.hpp \
				srcs/tcp_in_out/multiplexer.hpp \
				srcs/tcp_in_out/utils.hpp \
				srcs/tcp_in_out/client_buffer.hpp \
				srcs/Model/Model.hpp \
				srcs/Model/file_manager.hpp \
				srcs/exec/exec.hpp \
				srcs/exec/HttpCodes.hpp \
				srcs/exec/response.hpp

OBJ			=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all
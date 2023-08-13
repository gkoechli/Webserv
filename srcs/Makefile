NAME			=	ConfigParse

CXX 		=	c++

CXXFLAGS			= -Wall -Wextra -Werror -std=c++98

SRCS			=		main.cpp\
						config_file_parsing/configParsing.cpp\
						tcp_in_out/tcp.cpp \
						tcp_in_out/multiplexer.cpp \
						tcp_in_out/client_buffer.cpp

HEADERS		=	config_file_parsing/configParsing.hpp\
				tcp_in_out/tcp.hpp \
				tcp_in_out/multiplexer.hpp \
				tcp_in_out/client_buffer.hpp

OBJ			=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all
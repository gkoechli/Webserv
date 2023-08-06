NAME			=	ConfigParse

CXX 		=	c++

CXXFLAGS			= -Wall -Wextra -Werror -std=c++98

SRCS			=		main.cpp\
						config_file_parsing/configParsing.cpp\
						config_file_parsing/configClass.cpp \
						tcp_in_out/tcp.cpp

HEADERS		=	config_file_parsing/configClass.hpp\
				config_file_parsing/configParsing.hpp\
				tcp_in_out/tcp.hpp

OBJ			=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all
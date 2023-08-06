NAME			=	ConfigParse

CXX 		=	c++

CXXFLAGS			= -Wall -Wextra -Werror -std=c++98

SRCS			=		main.cpp\
						configParsing.cpp\
						configClass.cpp

HEADERS		=	configClass.hpp\
				configParsing.hpp\

OBJ			=	$(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all
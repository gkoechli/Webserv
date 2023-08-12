# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

SRCS		= 	client.cpp

#HEADER		= 	Span.hpp

RM			= rm -rf
NAME		= Client
CC			= c++ $(CFLAGS)

OBJECTS		= $(subst /,/build/,${SRCS:.cpp=.o})
DEPEND		= ${OBJECTS:.o=.d}
CFLAGS		= -Wall -Werror -Wextra -g3 -std=c++98


all:	$(NAME)

${NAME}:	${OBJECTS}
	@echo "${_UNDER}${_RED}Creating Executable${_END}"
	@echo "${_BOLD}${_GREEN}${CC} -o ${NAME} ${OBJECTS}${_END}"
	@${CC} -o ${NAME} ${OBJECTS}

-include ${DEPEND}

${OBJECTS}: $(subst .o,.cpp,$(subst /build/,/,$@))
	@if [ ! -d "./$(dir $@)" ]; then\
		echo "${_BOLD}${_UNDER}${_BLUE}"mkdir -p $(dir $@)"${_END}";\
		mkdir -p $(dir $@);\
	fi
	@echo "${_BOLD}${_BLUE}"$(CC) -MMD -I ./include -c $(subst .o,.cpp,$(subst /build/,/,$@)) -o $@"${_END}"
	@$(CC) -MMD -I ./include -c $(subst .o,.cpp,$(subst /build/,/,$@)) -o $@

clean:
	@echo "${_UNDER}${_RED}Deleting Objects and Dependencies${_END}"
	@echo "${_BOLD}${_YELLOW}"${RM} ${OBJECTS} ${DEPEND}"${_END}"
	@${RM} ${OBJECTS} ${DEPEND}

fclean: clean
	@echo "${_UNDER}${_RED}Deleting Executable${_END}"
	@echo "${_BOLD}${_RED}"${RM} ${NAME}"${_END}"
	@${RM} ${NAME}

gitm: fclean
	git add .
	git commit
	git push

# VER_H = include/Version_philo.h
# USER := $(shell env | grep USER | tail --bytes=+6)
# TIME=$(shell date +"%d %m %Y %Hh%M %Z")

# git: fclean
# 	$(eval MIN=$(shell expr $$(awk '/# define MINOR_VERSION/' $(VER_H) | tr -cd "[0-9]") + 1))
# 	$(eval MAJ=$(shell awk '/# define MAJOR_VERSION/' $(VER_H) | tr -cd "[0-9]"))
# 	sed -i 's/# define MINOR_VERSION .*/# define MINOR_VERSION \"$(MIN)\"/' $(VER_H)
# 	sed -i 's/# define BUILD_DATE .*/# define BUILD_DATE \"$(TIME)\"/' $(VER_H)
# 	git add .
# 	git commit -m "V$(MAJ).$(MIN) by $(USER) at $(TIME)"
# 	git push

re:	fclean all

.PHONY:		all clean fclean re gitm git printstart

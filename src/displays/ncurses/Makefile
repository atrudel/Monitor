NAME = __test

CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98

SRC = test.cpp NcursesDisplay.cpp Module.cpp

HDR = NcursesDisplay.hpp Module.hpp

OBJ = $(SRC:.cpp=.o)

all: ${NAME}

${NAME}: #${OBJ} ${HDR}
	c++ -lcurses ${CPPFLAGS} -I. -I./../ -o $@ $(SRC) #${OBJ}

clean:
	@/bin/rm -f ${OBJ}

fclean: clean
	@/bin/rm -f ${NAME}

re: fclean all

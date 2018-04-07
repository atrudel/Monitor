# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:59:39 by agrumbac          #+#    #+#              #
#    Updated: 2018/04/07 17:01:08 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

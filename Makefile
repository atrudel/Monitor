NAME = ft_gkrellm
CC = clang++
FILES =\
main.cpp

SRC = src/
DIRS = bin

SYSTEM = $(shell uname -s)

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

OBJS = $(addprefix bin/,$(FILES:.cpp=.o))

DEPS =
INCLUDES = -I includes/

ifeq (SYSTEM, Darwin)
	DEPSFLAGS =
else
	DEPSFLAGS =
endif

CXXFLAGS =	-Wall -Wextra -std=c++11
FLAGS = $(CXXFLAGS) $(INCLUDES)

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

$(NAME): $(DIRS) $(OBJS)
	@printf "\r$(GREEN)Compiling sources: DONE !                      $(NO_COLOR)\n";

	@printf "Building objects...\r"
	@$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Building objects: DONE !$(NO_COLOR)\n";
	@printf "\n$(GREEN)Building done: $(GREEN_BG)$(NAME)$(NO_COLOR)\n"

$(DIRS):
	@$(MKDIR) $(dir $(OBJS))

bin/%.o: src/%.cpp
	@printf "\rCompiling sources: $^                          \r";
	@$(CC) -MMD -c $^ -o $@ $(CXXFLAGS) $(INCLUDES)

.PHONY: all clean clean-libs fclean-libs fclean re

all: $(NAME)

clean:
	@printf "Cleaning objects..."
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objects: DONE !$(NO_COLOR)\n";

clean-libs: clean


fclean-libs: clean-libs
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY : clean, fclean, re, all, $(NAME), lanch, debug, install, uninstall
.SUFFIXES :
# Colors :
WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m


NAME = ft_gkrellm

SYSTEM = $(shell uname -s)

DEBUG = no
OPTI_FLAGS = -O2
DEBUG_FLAG = -pedantic -Weverything -std=c++98

CC = clang++
FLAG = -Wall -Wextra -Werror
ifeq ($(DEBUG), yes)
        SPE_FLAGS = $(DEBUG_FLAG)
else ifeq ($(OPTI), yes)
        SPE_FLAGS = $(OPTI_FLAGS)
else
		SPE_FLAGS =
endif
ifeq (SYSTEM, Darwin)
	DEPSFLAGS =
else
	DEPSFLAGS =
endif

INCLUDE_LIBS := -lncurses

SRC = src/

FILES =\
Core.cpp\
displays/beautiful/BeautifulDisplay.cpp\
displays/beautiful/SdlDisplay.cpp\
displays/ncurses/NcursesDisplay.cpp\
main.cpp\
modules/Cat/Cat.cpp\
modules/Hostname/Hostname.cpp\
modules/mainCpu/MainCpu.cpp\
modules/memory/MainMemory.cpp\
modules/Network/NetworkModule.cpp\
modules/Os/OSModule.cpp\
modules/time/TimeModule.cpp

OBJ_DIR = bin/
OBJ_PATHS = $(addprefix $(OBJ_DIR), $(dir $(OBJ)))
OBJ = $(FILES:.cpp=.o)

INC_DIR = ./includes
INC = $(SRC)
INC_FILES = #$(SRC:.cpp=.hpp)# ls -1 > src.txt &&

DEPS_DIR = dep
SDL_DIR = $(DEPS_DIR)/SDL2-2.0.8
SDL_TTF_DIR = $(DEPS_DIR)/SDL2_ttf-2.0.14
FREE_TYPE_DIR = $(DEPS_DIR)/freetype-2.9
SDL_LIB_DIR = $(SDL_DIR)/build/.libs
SDL_LIB = $(SDL_LIB_DIR)/libSDL2.a
SDL_INCLUDES = $(SDL_DIR)/include
SDL_MAC_FLAGS = -lSDL2 -framework Cocoa -framework CoreAudio\
  				-framework AudioToolbox -framework ForceFeedback\
 				-framework CoreVideo -framework Carbon -framework Metal -framework IOKit -liconv

AUTOR = auteur

all : $(NAME)

$(NAME) : install $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(INC), $(INC_FILES)) $(AUTOR)
	@($(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -I$(INC) $(INCLUDE_LIBS) -L $(SDL_LIB_DIR) $(SDL_MAC_FLAGS) -I $(SDL_INCLUDES) -o $(NAME))
	@(echo creation de $(NAME))

$(OBJ_DIR)%.o : $(addprefix $(SRC), %.cpp) $(addprefix $(INC), $(INC_FILES))
	@($(CC) $(FLAG) $(SPE_FLAGS) -I $(SDL_INCLUDES) -I $(INC) -c $< -o $@)
	@(echo $< " created")

$(OBJ_DIR) :
	mkdir -p $(OBJ_PATHS)

$(AUTOR) :
#	@(echo "" > ./auteur;) // fichier auteur

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)))
	@(rm -rf $(OBJ_DIR))
	@(echo suppression des $(OBJ_DIR).o)

fclean : clean
	@(rm -f $(NAME))
	@(echo suppression de $(NAME))

re : fclean all

debug :
	@($(CC) $(DEBUG_FLAG) $(addprefix $(SRC), $(FILES)) -I$(INC) -o $(NAME))
	./$(NAME)

lanch : re
	./$(NAME)

install : $(SDL_LIB)


$(SDL_LIB):
	@printf "\r$(YELLOW)  Building SDL2...$(NO_COLOR)                   \r";
	@$(shell tar -xzf $(SDL_DIR).tar.gz -C $(DEPS_DIR))
	# @$(shell tar -xzf $(SDL_TTF_DIR).tar.gz -C $(DEPS_DIR))
	# @$(shell tar -xzf $(FREE_TYPE_DIR).tar.bz2 -C $(DEPS_DIR))


	# @printf "\r$(YELLOW)  Building SDL2: Freetype...$(NO_COLOR)      \r";
	# @cd $(FREE_TYPE_DIR) && ./configure > /dev/null
	# # @make -C $(FREE_TYPE_DIR) -j4 > /dev/null 2> /dev/null
	# # @make -C $(FREE_TYPE_DIR) install > /dev/null 2> /dev/null

	# @printf "\r$(YELLOW)  Building SDL2: SDL2 ttf...$(NO_COLOR)           \r";
	# @cd $(SDL_TTF_DIR) && ./configure --with-freetype-prefix=$(FREE_TYPE_DIR) > /dev/null
	# @make -C $(SDL_TTF_DIR) -j4 > /dev/null 2> /dev/null


	@printf "\r$(YELLOW)  Building SDL2: SDL2 core...$(NO_COLOR)           \r";
	@cd $(SDL_DIR) && ./configure > /dev/null
	@make -C $(SDL_DIR) -j4 > /dev/null 2> /dev/null


	@printf "\r$(YELLOW)  Building SDL2: Removing dylib...$(NO_COLOR)   \r";
	@rm -rf $(SDL_LIB_DIR)/libSDL2-2.0.0.dylib
	@printf "\r$(GREEN)Building SDL2: DONE !$(NO_COLOR)                 \n";

uninstall : fclean
	@(rm -rf $(SDL_LIB))

horse:
	@(echo "	                                               \`T\",.\`-, ");
	@(echo "                                                     '8, :. ");
	@(echo "                                              \`\"\"\`oooob.\"T,. ");
	@(echo "                                            ,-\`\".)O;8:doob.'-. ");
	@(echo "                                     ,..\`'.'' -dP()d8O8Yo8:,..\`, ");
	@(echo "                                   -o8b-     ,..)doOO8:':o; \`Y8.\`, ");
	@(echo "                                  ,..bo.,.....)OOO888o' :oO.  \".  \`-. ");
	@(echo "                                , \"\`\"d....88OOOOO8O88o  :O8o;.    ;;,b ");
	@(echo "                               ,dOOOOO\"\"\"\"\"\"\"\"O88888o:  :O88Oo.;:o888d ");
	@(echo "                               \"\"888Ob...,-- :o88O88o:. :o'\"\"\"\"\"\"\"Y8OP ");
	@(echo "                               d8888.....,.. :o8OO888:: :: ");
	@(echo "                              \"\" .dOO8bo\`'',,;O88O:O8o: ::, ");
	@(echo "                                 ,dd8\".  ,-)do8O8o:\"\"\"; ::: ");
	@(echo "                                 ,db(.  T)8P:8o:::::    ::: ");
	@(echo "                                 -\"\",\`(;O\"KdOo::        ::: ");
	@(echo "                                   ,K,'\".doo:::'        :o: ");
	@(echo "                                    .doo:::\"\"\"::  :.    'o: ");
	@(echo "        ,..            .;ooooooo..o:\"\"\"\"\"     ::;. ::;.  'o. ");
	@(echo "   ,, \"'    \` ..   .d;o:\"\"\"'                  ::o:;::o::  :; ");
	@(echo "   d,         , ..ooo::;                      ::oo:;::o\"'.:o ");
	@(echo "  ,d'.       :OOOOO8Oo::\" '.. .               ::o8Ooo:;  ;o: ");
	@(echo "  'P\"   ;  ;.OPd8888O8::;. 'oOoo:.;..         ;:O88Ooo:' O\"' ");
	@(echo "  ,8:   o::oO\` 88888OOo:::  o8O8Oo:::;;     ,;:oO88OOo;  ' ");
	@(echo " ,YP  ,::;:O:  888888o::::  :8888Ooo::::::::::oo888888o;. , ");
	@(echo " ',d: :;;O;:   :888888::o;  :8888888Ooooooooooo88888888Oo; , ");
	@(echo " dPY:  :o8O     YO8888O:O:;  O8888888888OOOO888\"\" Y8o:O88o; , ");
	@(echo ",' O:  'ob\`      \"8888888Oo;;o8888888888888'\"'     \`8OO:.\`OOb . ");
	@(echo "'  Y:  ,:o:       \`8O88888OOoo\"\"\"\"\"\"\"\"\"\"\"'           \`OOob\`Y8b\` ");
	@(echo "   ::  ';o:        \`8O88o:oOoP                        \`8Oo \`YO. ");
	@(echo "   \`:   Oo:         \`888O::oP                          88O  :OY ");
	@(echo "    :o; 8oP         :888o::P                           do:  8O: ");
	@(echo "   ,ooO:8O'       ,d8888o:O'                          dOo   ;:. ");
	@(echo "   ;O8odo'        88888O:o'                          do::  oo.: ");
	@(echo "  d\"\`)8O'         \"YO88Oo'                          \"8O:   o8b' ");
	@(echo " ''-'\`\"            d:O8oK  -hrr-                   dOOo'  :o\": ");
	@(echo "                   O:8o:b.                        :88o:   \`8:, ");
	@(echo "                   \`8O:;7b,.                       \`\"8'     Y: ");
	@(echo "                    \`YO;\`8b' ");
	@(echo "                     \`Oo; 8:. ");
	@(echo "                      \`OP\"8.\` ");
	@(echo "                       :  Y8P ");
	@(echo "                       \`o  \`, ");
	@(echo "                        Y8bod. ");
	@(echo "                        \`\"\"\"\"' ");

tank :
	@(echo "\033[2J")
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      __    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      _.    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      /`    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      /_    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(echo '          ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '     |-._   ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '    \;":-   ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '    -;":- ')
	@(echo '    \| |  ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     | ;- ')
	@(echo '    \| |  ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     |`+ ')
	@(echo '    \| |  ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     ^-^     __,-.  ')
	@(echo '    \| |    ( .`-)  ')
	@(echo '    |"""\-=(_ (_,_)    ')
	@(echo "    (____)   \`--' ")
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     ^-^     __,-.  ')
	@(echo "    \| |    ( .\`-')_.o  ")
	@(echo '    |"""\-=(_ (_,_)    ')
	@(echo "    (____)   \`--' ")
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     ^-^     ..,-.      _.--""""o  ')
	@(echo "    \| |    : .\`-';_.-''  ")
	@(echo '    |"""\-=:. (.,.)   ')
	@(echo "    (____)   \`:-' ")
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._ ')
	@(echo '     ^-^     .. .       _.--""""--.')
	@(echo '    \| |    : . : ; . "             "-.')
	@(echo '    |"""\-=:. :.,.;                    `.')
	@(echo "    (____)   \`:-'                         o")
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._                                      ')
	@(echo '     ^-^                                      ')
	@(echo '    \| |                                       ')
	@(echo '    |"""\-=                                         ')
	@(echo '    (____)                                         ')
	@(echo '                                                 ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '    _.-._                                      ')
	@(echo "     \`-'                                      ")
	@(echo '    \| |                                       ')
	@(echo '    |"""\-=                                         ')
	@(echo '    (____)                                         ')
	@(echo '                                                 ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '    -;":- ')
	@(echo '    \| |  ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '    \;":-   ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      /_    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(echo '          ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '          ')
	@(echo '          ')
	@(echo '      __    ')
	@(echo '    |"""\-=    ')
	@(echo '    (____)    ')
	@(echo '            ')
	@(echo '          ')
	@(sleep 1)
	@(echo "\033[0;0H")
	@(echo '                                                     _..----.._                                   ')
	@(echo '                                                    ]_.--._____[                                  ')
	@(echo '                                                  ___|$'--$'__..|--._                               ')
	@(echo '                              __               """    ;            :                              ')
	@(echo '                            ()_ """"---...__.$'""!":  /    ___       :                             ')
	@(echo '                               """---...__\]..__] | /    [ 0 ]      :                             ')
	@(echo '                                          """!--./ /      """        :                            ')
	@(echo '                                   __  ...._____;""$'.__________..--..:_                           ')
	@(echo '                                  /  !"$'$'$'$'$'$'!$'$'$'$'$'$'$'$'$'$'|$'$'$'$'/$' $' $' $' \"--..__  __..              ')
	@(echo '                                 /  /.--.    |          |  .$'          \$' $' $'.""--.{$'.            ')
	@(echo '             _...__            >=7 //.-.:    |          |.$'             \ ._.__  $' $'""$'.          ')
	@(echo '          .-$' /    """"----..../ "">==7-.....:______    |                \| |  "";.;-"> \         ')
	@(echo '          """";           __.."   .--"/"""""----...."""""----.....H_______\_!....$'----""""]       ')
	@(echo '        _..---|._ __..--""       _!.-=_.            """""""""""""""                   ;"""        ')
	@(echo '       /   .-";-.$'--...___     ." .-""; $';""-""-...^..__...-v.^___,  ,__v.__..--^"--""-v.^v,      ')
	@(echo '      ;   ;   |$'.         """-/ ./;  ;   ;\P.        ;   ;        """"____;  ;.--""""// $'""<,     ')
	@(echo '      ;   ;   | 1            ;  ;  $'.: .$'  ;<   ___.-$'._.$'------""""""____$'..$'.--""";;$'  o $';     ')
	@(echo '      $'.   \__:/__           ;  ;--""()_   ;$'  /___ .-" ____---""""""" __.._ __._   $'>.,  ,/;     ')
	@(echo '        \   \    /"""<--...__;  $'_.-$'/; ""; ;.$'.$'  "-..$'    "-.      /"/    `__. $'.   "---";      ')
	@(echo '         $'.  $'v ; ;     ;;    \  \ .$'  \ ; ////    _.-" "-._   ;    : ;   .-$'__ $'. ;   .^".$'      ')
	@(echo '           $'.  $'; $'.   .$'/     $'. `-.__.$' /;;;   .o__.---.__o. ;    : ;   $'"";;""$' ;v^" .^        ')
	@(echo '             $'-. $'-.___.$'<__v.^,v$'.  $'-.-$' ;|:   $'    :      ` ;v^v^$'.$'.    .;$'.__/_..-$'          ')
	@(echo '                $'-...__.___...---""$'-.   $'-$'.;\     $'WW\     .$'_____..>."^"-""""""""    fsc       ')
	@(echo '                                      $'--..__ $'"._..$'  $'"-;;"""                                   ')
	@(echo '                                             """---$'""""""                                        ')
	@(echo '                                                                          ')

cafe : coffee

coffee :
	@(echo "\033[2J")
	@(echo "\033[0;0H")
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '                                                                 ')
	@(echo '            $$o$$o$$o$$o$$$$o$$$$$$o$$$$o$$o$$$$o$$$$o$$$$$$o$$o$$o$$o$$o$$o$$o$$o$$o$$ooo')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   " $$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$      "$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     o$$$$$$$$"')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooooo$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"""""')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '"$$o$$o$$o$$o$$o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '  "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '    "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"""')
	@(echo '       """""""""""""""""""""""""""""""""""""""""""""""""""""')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                      o$$$$$$$$$$$$oo                        ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                        o$$$$$$$$$$$$oo                        ')
	@(echo '                     o$$"        "$$oo                        ')
	@(echo '                     $$   o""""$$o  "$$o                        ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                             o$$$$$$$$$$$$oo                                                ')
	@(echo '                          o$$"        "$$oo                                                ')
	@(echo '                          $$   o""""$$o  "$$o                                                ')
	@(echo '                         "$$  o  "o  "o   $$                                                 ')
	@(echo '                         "$$   $$o $$   $$   o$$                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                              o$$$$$$$$$$$$oo                                                ')
	@(echo '                           o$$"        "$$oo                                                ')
	@(echo '                           $$   o""""$$o  "$$o                                                ')
	@(echo '                          "$$  o  "o  "o   $$                                                 ')
	@(echo '                          "$$   $$o $$   $$   o$$                                                ')
	@(echo '                           "$$       o$$"$$  o$$                                                ')
	@(echo '                            "$$ooooo$$$$  $$  o$$                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                    o$$$$$$$$$$$$oo                                                ')
	@(echo '                                 o$$"        "$$oo                                                ')
	@(echo '                                 $$   o""""$$o  "$$o                                                ')
	@(echo '                                "$$  o  "o  "o   $$                                                 ')
	@(echo '                                "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                 "$$       o$$"$$  o$$                                                ')
	@(echo '                                  "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                        o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                      o$$        $$o    $$$$"   "   "                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                     o$$$$$$$$$$$$oo                                                ')
	@(echo '                                  o$$"        "$$oo                                                ')
	@(echo '                                  $$   o""""$$o  "$$o                                                ')
	@(echo '                                 "$$  o  "o  "o   $$                                                 ')
	@(echo '                                 "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                  "$$       o$$"$$  o$$                                                ')
	@(echo '                                   "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                         o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                       o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                      $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                      $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                      $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                      o$$$$$$$$$$$$oo                                                ')
	@(echo '                                   o$$"        "$$oo                                                ')
	@(echo '                                   $$   o""""$$o  "$$o                                                ')
	@(echo '                                  "$$  o  "o  "o   $$                                                 ')
	@(echo '                                  "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                   "$$       o$$"$$  o$$                                                ')
	@(echo '                                    "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                          o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                        o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                       $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                       $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                       $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                        "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                         ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                          o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                     o$$$$$$$$$$$$oo                                                ')
	@(echo '                                  o$$"        "$$oo                                                ')
	@(echo '                                  $$   o""""$$o  "$$o                                                ')
	@(echo '                                 "$$  o  "o  "o   $$                                                 ')
	@(echo '                                 "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                  "$$       o$$"$$  o$$                                                ')
	@(echo '                                   "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                         o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                       o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                      $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                      $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                      $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                       "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                        ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                         o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(echo '                         o" o oo""  "" "$$o                                                ')
	@(echo '                        o$$o" ""          $$                                                ')
	@(echo '                       $$" " o"   " " "   "o                                                ')
	@(echo '                      $$$$ "  "  o$$ o$$o "   $$                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                   o$$$$$$$$$$$$oo                                                ')
	@(echo '                                o$$"        "$$oo                                                ')
	@(echo '                                $$   o""""$$o  "$$o                                                ')
	@(echo '                               "$$  o  "o  "o   $$                                                 ')
	@(echo '                               "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                "$$       o$$"$$  o$$                                                ')
	@(echo '                                 "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                       o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                     o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                    $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                    $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                    $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                     "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                      ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                       o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(echo '                       o" o oo""  "" "$$o                                                ')
	@(echo '                      o$$o" ""          $$                                                ')
	@(echo '                     $$" " o"   " " "   "o                                                ')
	@(echo '                    $$$$ "  "  o$$ o$$o "   $$                                                ')
	@(echo '                   o$$ $$  $$  o$$$$ "  "   ""                                                ')
	@(echo '                   o  $$ $$"  " "o      o$$                                                ')
	@(echo '                   $$ o         $$o$$oo$$""                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo ' ')
	@(echo '                                        o$$$$$$$$$$$$oo                                                ')
	@(echo '                                     o$$"        "$$oo                                                ')
	@(echo '                                     $$   o""""$$o  "$$o                                                ')
	@(echo '                                    "$$  o  "o  "o   $$                                                 ')
	@(echo '                                    "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                     "$$       o$$"$$  o$$                                                ')
	@(echo '                                      "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                            o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                          o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                         $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                         $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                         $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                          "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                           ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                            o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(echo '                            o" o oo""  "" "$$o                                                ')
	@(echo '                           o$$o" ""          $$                                                ')
	@(echo '                          $$" " o"   " " "   "o                                                ')
	@(echo '                         $$$$ "  "  o$$ o$$o "   $$                                                ')
	@(echo '                        o$$ $$  $$  o$$$$ "  "   ""                                                ')
	@(echo '                        o  $$ $$"  " "o      o$$                                                ')
	@(echo '                        $$ o         $$o$$oo$$""                                                ')
	@(echo '                       $$o $$   o  o  o"$$$$                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo ' ')
	@(echo ' ')
	@(echo '                                   o$$$$$$$$$$$$oo                                                ')
	@(echo '                                o$$"        "$$oo                                                ')
	@(echo '                                $$   o""""$$o  "$$o                                                ')
	@(echo '                               "$$  o  "o  "o   $$                                                 ')
	@(echo '                               "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                "$$       o$$"$$  o$$                                                ')
	@(echo '                                 "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                       o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                     o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                    $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                    $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                    $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                     "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                      ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                       o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(echo '                       o" o oo""  "" "$$o                                                ')
	@(echo '                      o$$o" ""          $$                                                ')
	@(echo '                     $$" " o"   " " "   "o                                                ')
	@(echo '                    $$$$ "  "  o$$ o$$o "   $$                                                ')
	@(echo '                   o$$ $$  $$  o$$$$ "  "   ""                                                ')
	@(echo '                   o  $$ $$"  " "o      o$$                                                ')
	@(echo '                   $$ o         $$o$$oo$$""                                                ')
	@(echo '                  $$o $$   o  o  o"$$$$                                                ')
	@(echo '                  $$o  o  $$  $$    "$$o                                                ')
	@(echo '                  $$o  $$   o  $$  $$ "o                                                ')
	@(sleep 0.1)
	@(echo "\033[0;0H")
	@(echo '                                    o$$$$$$$$$$$$oo                                                ')
	@(echo '                                 o$$"        "$$oo                                                ')
	@(echo '                                 $$   o""""$$o  "$$o                                                ')
	@(echo '                                "$$  o  "o  "o   $$                                                 ')
	@(echo '                                "$$   $$o $$   $$   o$$                                                ')
	@(echo '                                 "$$       o$$"$$  o$$                                                ')
	@(echo '                                  "$$ooooo$$$$  $$  o$$                                                ')
	@(echo '                        o$$ """ $$     " $$$$$$   "  $$                                                ')
	@(echo '                      o$$        $$o    $$$$"   "   "                                                ')
	@(echo '                     $$$$  $$ " $$   $$$$$$o"$$    o  o$$"                                                ')
	@(echo '                     $$"  o "" $$   $$" "   o"  $$$$                                                ')
	@(echo '                     $$o  " "  $$  o$$"   o"  o$$"                                                ')
	@(echo '                      "$$o    $$$$  $$   o"  o$$$$"                                                ')
	@(echo '                       ""o$$o"$$"  $$oo"  o$$"                                                ')
	@(echo '                        o$$$$ $$   $$$$$$  o$$$$                                                ')
	@(echo '                        o" o oo""  "" "$$o                                                ')
	@(echo '                       o$$o" ""          $$                                                ')
	@(echo '                      $$" " o"   " " "   "o                                                ')
	@(echo '                     $$$$ "  "  o$$ o$$o "   $$                                                ')
	@(echo '                    o$$ $$  $$  o$$$$ "  "   ""                                                ')
	@(echo '                    o  $$ $$"  " "o      o$$                                                ')
	@(echo '                    $$ o         $$o$$oo$$""                                                ')
	@(echo '                   $$o $$   o  o  o"$$$$                                                ')
	@(echo '                   $$o  o  $$  $$    "$$o                                                ')
	@(echo '                   $$o  $$   o  $$  $$ "o                                                ')
	@(echo '                    $$  $$   "o  $$  "o"$$o                                                ')
	@(echo '                    $$   "   o   $$   o $$$$                                                ')
	@(echo '            $$o$$o$$o$$o$$$$o$$$$$$o$$$$o$$o$$$$o$$$$o$$$$$$o$$o$$o$$o$$o$$o$$o$$o$$o$$ooo')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   " $$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$      "$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     o$$$$$$$$"')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooooo$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"""""')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$')
	@(echo '            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '"$$o$$o$$o$$o$$o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '  "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"')
	@(echo '    "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"""')
	@(echo '       """""""""""""""""""""""""""""""""""""""""""""""""""""')

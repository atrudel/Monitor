#include <iostream>
#include "Core.hpp"
#include <fstream>

void printUsage(void) {
		std::cout << "usage: ./ft_gkrellm [-lhtcrnao] \n-l: display ncurses mode \n-h: Hostname \n-t: Time info \n-c: CPU info \n-r: RAM info \n-n: Network info \n-a: display cat \n-o: OS info\n--help: print usage" << std::endl;
}

int main(int ac, char **av)
{
	// std::ofstream out("logs.txt");
	// std::streambuf *coutbuf = // std::cout.rdbuf();
	// std::cout.rdbuf(out.rdbuf());

	int j, i = 1, c = 0;
	char display_options[SIZE_OPT];
	Core core;

	if (ac == 2 && !strcmp(av[1], "--help")) {
		printUsage();
		return 0;
	}
	bzero(display_options, SIZE_OPT);
	if (ac == 1 || (ac == 2 && !strcmp(av[1], "-l"))) {
		display_options[0] = 'h';
		display_options[1] = 't';
		display_options[2] = 'c';
		display_options[3] = 'r';
		display_options[4] = 'n';
		display_options[5] = 'a';
		display_options[6] = 'o';
		if (ac == 2 && !strcmp(av[1], "-l"))
			display_options[7] = 'l';
	} else {
		while (i < ac) {
			j = 0;
			while (av[i][j]) {
				if ((j == 0) && av[i][j] && av[i][j++] != '-')
					continue ;
				if (av[i][j] == 'l')
					display_options[c++] = 'l';
				else if (av[i][j] == 'h')
					display_options[c++] = 'h';
				else if (av[i][j] == 't')
					display_options[c++] = 't';
				else if (av[i][j] == 'c')
					display_options[c++] = 'c';
				else if (av[i][j] == 'r')
					display_options[c++] = 'r';
				else if (av[i][j] == 'n')
					display_options[c++] = 'n';
				else if (av[i][j] == 'a')
					display_options[c++] = 'a';
				else if (av[i][j] == 'o')
					display_options[c++] = 'o';
				else
				{
					printUsage();
					return (1);
				}
				j++;
			}
			i++;
		}
	}
	core.start(display_options);
	// std::cout.rdbuf(coutbuf);
}

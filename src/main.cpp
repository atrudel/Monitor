#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
	int j, i = 1, c = 0;
	char display_options[SIZE_OPT];
	Core core;

	if (ac == 2 && !strcmp(av[1], "-help")) {
		std::cout << "usage: ./ft_gkrellm [-locrtn] \n-l: display ncurses mode\n-o: OS info\n-c: CPU info\n-r: RAM info\n-t: Time info\n-n: Network info" << std::endl;
		return 0;
	}
	bzero(display_options, SIZE_OPT);
	while (i < ac) {
		j = 0;
		while (av[i][j]) {
			if ((j == 0) && av[i][j] && av[i][j++] != '-')
				continue ;
			if (av[i][j] == 'h')
				display_options[c++] = 'h';
			if (av[i][j] == 'l')
				display_options[c++] = 'l';
			if (av[i][j] == 'o')
				display_options[c++] = 'o';
			if (av[i][j] == 'c')
				display_options[c++] = 'c';
			if (av[i][j] == 'r')
				display_options[c++] = 'r';
			if (av[i][j] == 't')
				display_options[c++] = 't';
			if (av[i][j] == 'n')
				display_options[c++] = 'n';
			if (av[i][j] == 'a')
				display_options[c++] = 'a';
			j++;
		}
		i++;
	}
	core.start(display_options);
//	 core.test();
}

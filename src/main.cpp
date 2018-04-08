#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
	int j, i = 1, display_options = 0;
	Core core;

	if (ac == 2 && !strcmp(av[1], "-help")) {
		std::cout << "usage: ./ft_gkrellm [-locrtn] \n-l: display ncurses mode\n-o: OS info\n-c: CPU info\n-r: RAM info\n-t: Time info\n-n: Network info" << std::endl;
		return 0;
	}

	while (i < ac) {
		j = 0;
		while (av[i][j]) {
			if ((j == 0) && av[i][j] && av[i][j++] != '-')
				continue ;
			if (av[i][j] == 'l')
				display_options |= LIB_OPT;
			if (av[i][j] == 'o')
				display_options |= OS_OPT;
			if (av[i][j] == 'c')
				display_options |= CPU_OPT;
			if (av[i][j] == 'r')
				display_options |= RAM_OPT;
			if (av[i][j] == 't')
				display_options |= TIME_OPT;
			if (av[i][j] == 'n')
				display_options |= NETWORK_OPT;
			j++;
		}
		i++;
	}
	core.start(display_options);
//	 core.test();
}

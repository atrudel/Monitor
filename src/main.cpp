#include <iostream>
#include "Core.hpp"
#include <fstream>

int main()
{
	std::ofstream out("logs.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	Core core;

	std::cout << "Hello 42" << std::endl;
	core.start();
//	 core.test();

	std::cout.rdbuf(coutbuf);
}

#include <fstream>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{

	std::ifstream ifs("../test.txt");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::cout << content;

	return 0;
}
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>

int main(int argc, char** argv)
{
	for (int i = 0; i < argc; ++i)
	{
		std::string argument = argv[i];

		//argument[0]

		std::cout << "Argument " << i << ": " << argument << std::endl;
	}

	std::cout << "Working Directory : " << std::filesystem::current_path() << std::endl;
}

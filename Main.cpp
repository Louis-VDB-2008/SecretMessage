#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <exception>
#include <vector>

#include "CommandLine.h"
#include "Image.h"

int main(int argc, char** argv)
{
	for (int i = 0; i < argc; ++i)
	{
		std::string argument = argv[i];
		std::cout << "Argument " << i << ": " << argument << std::endl;
	}

	std::cout << "Working Directory : " << std::filesystem::current_path() << std::endl; // Affiche le répertoire de travail actuel
	
	CommandLine commandLine; // créer une instance de la classe CommandLine
	commandLine.CommandGo(argc, argv); // lance 
    return 0;
}
#include "CommandLine.h"


int CommandLine::MinimumArguments(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Missing command\n";
        return 0;
    }
}

int CommandLine::CommandChoice(int argc, char** argv)
{
    std::string command = argv[0];

    if (command == "encode")
    {
        if (argc != 5)
        {
            std::cerr << "Invalid encode arguments\n";
            return 1;
        }
    }
    else if (command == "decode")
    {
        if (argc != 3)
        {
            std::cerr << "Invalid decode arguments\n";
            return 2;
        }
    }
    else
    {
        std::cerr << "Unknown command\n";
        return 0;
    }
}

int CommandLine::ImageFileCheck(int argc, char** argv)
{
    std::ifstream file(argv[2], std::ios::binary);

    if (!file)
    {
        std::cerr << "Failed to open file\n";
        return 0;
    }
    return 1;
}

int CommandLine::CommandCheck(int argc, char** argv)
{
	if (!MinimumArguments(argc, argv))
	{
		return 0;
	}
	if (!CommandChoice(argc, argv))
	{
		return 0;
	}
	if (!ImageFileCheck(argc, argv))
	{
		return 0;
	}
	return 1;
 }

int CommandLine::CommandGo(int argc, char** argv)
{
	if (!CommandCheck(argc, argv))
	{
		return 0;
	}
	if (CommandChoice(argc, argv) == 1)
	{
		CommandEncode(argc, argv);
	}
	else if (CommandChoice(argc, argv) == 2)
	{
		CommandDecode(argc, argv);
	}
}
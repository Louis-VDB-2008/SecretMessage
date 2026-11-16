#include "CommandLine.h"

int CommandLine::MinimumArguments(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Missing command\n";
        return 1;
    }

    std::string command = argv[1];

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
            return 1;
        }
    }
    else
    {
        std::cerr << "Unknown command\n";
        return 1;
    }
}

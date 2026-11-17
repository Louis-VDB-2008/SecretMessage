#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CommandLine.h"
#include "XOR.h"
#include "Image.h"


int CommandLine::MinimumArguments(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Missing command\n";
        return 0;
    }
	return 1;
}

int CommandLine::CommandChoice(int argc, char** argv)
{
    std::string command = argv[1];

    if (command == "encode")
    {
        if (argc != 5)
        {
            std::cerr << "Invalid encode arguments\n";
            return 0;
        }
		return 1;
    }
    else if (command == "decode")
    {
        if (argc != 4)
        {
            std::cerr << "Invalid decode arguments\n";
            return 0;
        }
		return 2;
    }
	else if (command == "help")
	{
		std::cout << "Usage:\n";
		std::cout << "  encode <image_file> <key> <message>\n";
		std::cout << "  decode <image_file> <key>\n";
		std::cout << "  help\n";
		return 0;
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
	//BmpInfo info = ValidateBMPHeader(bmp_data); // a remetre une fois merge

    return 1;
}

int CommandLine::CommandKey(int argc, char** argv)
{
    std::string key = argv[3];
    if (key.empty())
    {
        std::cerr << "Key is empty\n";
        return 0;
    }
	int keyInt = std::stoi(key);
    if (keyInt < 0 || keyInt >= 10)
    {
        std::cerr << "Invalid key\n";
        return 0;
    }
    return 1;
}

int CommandLine::CommandMessage(int argc, char** argv)
{
	std::string message = argv[4];
	if (message.empty())
	{
		std::cerr << "Message is empty\n";
		return 0;
	}
	if (message.size() > 255)
	{
		std::cerr << "Message is too long\n";
		return 0;
	}
	return 1;
}

int CommandLine::CommandCheck(int argc, char** argv)
{
	if (MinimumArguments(argc, argv) == 0)
	{
		return 0;
	}
	if (CommandChoice(argc, argv) == 0)
	{
		return 0;
	}
	if (ImageFileCheck(argc, argv) == 0)
	{
		return 0;
	}
	if (CommandKey(argc, argv) == 0)
	{
		return 0;
	}
	if (CommandChoice(argc, argv) == 1)
	{
		if (CommandMessage(argc, argv) == 0)
		{
			return 0;
		}
	}
	return 1;
 }


void CommandLine::CommandEncode(int argc, char** argv)
{
	std::string key = argv[3];
	std::string message = argv[4];
	std::vector<std::uint8_t> MesssageBinaire(message.size());
	std::vector<std::uint8_t> MessageEncoded(message.size());
	for (int i = 0; i < message.size(); ++i)
	{
		MesssageBinaire[i] = { static_cast<std::uint8_t>(message[i]) };  // Convertir le caractère en binaire
		MessageEncoded[i] = XOR::EncodeDecode(MesssageBinaire[i], key); // Encode le message en utilisant la clé
		std::cout << "Encoded message: " << MessageEncoded[i] << std::endl;
	}
	// fonction pour recevoir les octets de couleur (dans un tableau) // Hugo
	// fonction qui modifie les octets en parametre le tableau, le MesssageEncoded // Louis
	// fonction qui envoye le tableau modifier pour creer un fichier image avec l'image modifiée // Hugo
}

void CommandLine::CommandDecode(int argc, char** argv)
{
	std::string key = argv[3];
	std::uint8_t MessageEncoded[] = { 0 };

	// fonction pour recevoir les octets de couleur (dans un tableau) // Hugo
	// MessageEncoded = {fonction pour lire le bit de pont faible et les assembler} // Louis

	std::vector<uint8_t> MessageDecoded;

	for (int i = 0; i < sizeof(MessageEncoded); ++i)
	{
		MessageDecoded.push_back(XOR::EncodeDecode(MessageEncoded[i], key));
	}

	std::string Message(MessageDecoded.begin(), MessageDecoded.end());

	std::cout << "Decoded message: " << Message;
}


void CommandLine::CommandGo(int argc, char** argv)
{
	std::vector<std::uint8_t> bmp_data = ReadBinaryFile(argv[2]);
	//inspect_pixels(bmp_data, info); // a rementre une fois que l'on a merge
	if (CommandCheck(argc, argv) == 0)
	{
		return;
	}
	if (CommandChoice(argc, argv) == 1)
	{
		CommandEncode(argc, argv);
	}
	else if (CommandChoice(argc, argv) == 2)
	{
		CommandDecode(argc, argv);
	}
	else
	{
		return;
	}
}

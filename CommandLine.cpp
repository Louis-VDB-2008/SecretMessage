#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CommandLine.h"
#include "XOR.h"
#include "Image.h"
#include <bitset>

std::vector<std::uint8_t> bmp_data;
BmpInfo info;


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
		if (argc != 6)
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
	validate_bmp_header(bmp_data);

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
	std::vector<std::uint8_t> color = extract_pixel_color(bmp_data, info);
	if (message.size() > color.size() / 8)
	{
		std::cerr << "Message is too long\n";
		return 0;
	}
	return 1;
}

bool CommandLine::CommandCheck(int argc, char** argv)
{
	if (MinimumArguments(argc, argv) == 0)
	{
		return false;
	}
	if (CommandChoice(argc, argv) == 0)
	{
		return false;
	}
	if (ImageFileCheck(argc, argv) == 0)
	{
		return false;
	}
	if (CommandKey(argc, argv) == 0)
	{
		return false;
	}
	if (CommandChoice(argc, argv) == 1)
	{
		if (CommandMessage(argc, argv) == 0)
		{
			return false;
		}
	}
	return true;
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
		MessageEncoded[i] = XOR::EncodeDecode(MesssageBinaire[i], key);
	}
	std::vector<std::uint8_t> color = extract_pixel_color(bmp_data, info);
	std::string output;
	if (argc < 6)
	{
		output = "output.bmp";
	}
	else
	{
		output = argv[5] + std::string(".bmp");
	}
	apply_pixel_changes(bmp_data, info, ModifPixels(color, MessageEncoded, argv), output);
}

std::vector<std::uint8_t> CommandLine::ModifPixels(std::vector<std::uint8_t> color, std::vector<std::uint8_t> MessageEncoded, char** argv)
{
	int y = 0;
	int j = 0;
	std::string key = argv[3];
	std::uint8_t octet = MessageEncoded[j];
	std::uint8_t MessageSize = MessageEncoded.size();
	std::cout << "Taille " << static_cast<int>(MessageSize) << " lettres\n";
	for (int i = 0; i < 8; i++)
	{
		std::uint8_t bitSize = (MessageSize >> (7 - i)) & 0x01u;
		color[i] = (color[i] & 0xFEu) | bitSize;
	}
	for (int i = 8; i < color.size(); ++i)
	{
		std::uint8_t bit = (octet >> (7 - y)) & 0x01u;
		color[i] = (color[i] & 0xFEu) | bit;
		if (y == 7)
		{
			y = 0;
			j++;
			if (j >= MessageEncoded.size())
			{
				octet = 0;
			}
			else
			{
				octet = MessageEncoded[j];
			}
		}
		else
		{
			y++;
		}
	}
	return color;
}

void CommandLine::CommandDecode(int argc, char** argv)
{
	std::string key = argv[3];


	std::vector<std::uint8_t> color = extract_pixel_color(bmp_data, info);
	std::vector<std::uint8_t> MessageEncoded = { ReadMessage(color) };

	std::vector<uint8_t> MessageDecoded;

	for (int i = 0; i < MessageEncoded.size(); ++i)
	{
		MessageDecoded.push_back(XOR::EncodeDecode(MessageEncoded[i], key));
	}

	std::string Message(MessageDecoded.begin(), MessageDecoded.end());

	std::cout << "Decoded message: " << Message;
}
std::vector<std::uint8_t>CommandLine::ReadMessage(const std::vector<std::uint8_t>& color)
{
	std::vector<std::uint8_t> MessageEncoded;
	std::vector<std::uint8_t> MessageEncod;
	int j = 0;
	std::uint8_t BIT = 0;
	std::uint8_t BitSize = 0b00000000;
	for (int i = 0; i < 8; i++)
	{
		BitSize = static_cast<std::uint8_t>((BitSize << 1) | color[i] & 1u);
	}
	std::cout << "Taille " << static_cast<int>(BitSize) << " lettres\n";
	for (int i = 8; i < 8 + static_cast<int>(BitSize) * 8; ++i)
	{
		j++;
		BIT = static_cast<std::uint8_t>((BIT << 1) | color[i] & 1u);
		if (j == 8)
		{
			MessageEncoded.push_back(BIT);
			j = 0;
			BIT = 0;
		}
	}
	
	return MessageEncoded;
}
void CommandLine::CommandGo(int argc, char** argv)
{
	if (argc > 2)
	{
		bmp_data = ReadBinaryFile(argv[2]);
		info = validate_bmp_header(bmp_data);
	}
	if (CommandCheck(argc, argv) == false)
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


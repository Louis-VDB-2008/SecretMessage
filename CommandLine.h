#pragma once
#include "Main.cpp"


class CommandLine
{
public:
	int CommandCheck(int argc, char** argv);
	int	CommandGo(int argc, char** argv);

private:
	int MinimumArguments(int argc, char** argv);
	int CommandChoice(int argc, char** argv);
	int ImageFileCheck(int argc, char** argv);
	int CommandEncode(int argc, char** argv);
	int CommandDecode(int argc, char** argv);
};


#pragma once
#include <cstdint>
#include <vector>

class CommandLine
{
public:
	void CommandGo(int argc, char** argv);

private:
	int MinimumArguments(int argc, char** argv); // Vérifie si le nombre d'arguments est suffisant
	int CommandChoice(int argc, char** argv); // Vérifie si la commande est "encode" ou "decode" ou "help"
	int ImageFileCheck(int argc, char** argv); // Vérifie si le fichier image existe et peut être ouvert
	int CommandKey(int argc, char** argv); // Vérifie si la clé est valide (un entier entre 0 et 9)
	int CommandMessage(int argc, char** argv); // Vérifie si le message est valide (non vide)

	void CommandEncode(int argc, char** argv); // fonction pour encoder le message dans l'image
	std::vector<std::uint8_t> ModifPixels(std::vector<std::uint8_t> color, std::vector<std::uint8_t> MessageEncoded);
	void CommandDecode(int argc, char** argv); // fonction pour décoder le message de l'image
	std::vector<std::uint8_t>ReadMessage(const std::vector<std::uint8_t>& color);


	bool CommandCheck(int argc, char** argv); // Vérifie si les arguments sont valides
};


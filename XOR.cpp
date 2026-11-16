#include "XOR.h"

std::uint8_t XOR::EncodeDecode(const std::uint8_t& message, const std::string& key)
{
	return message ^ static_cast<std::uint8_t>(std::stoi(key)); // XOR de message avec la clé convertie en int par (std::stoi) et transformée en binaire par (static_cast<std::uint8_t>)
}

#pragma once
#include <string>
#include <cstdint>

class XOR
{
public :
	static std::uint8_t EncodeDecode(const std::uint8_t& message, const std::string& key);
};


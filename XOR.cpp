#include "XOR.h"

std::uint8_t XOR::EncodeDecode(const std::uint8_t& message, const std::string& key)
{
    std::uint8_t result = message;

    for (int i = 0; i < key.size(); ++i)
    {
        result ^= static_cast<std::uint8_t>(key[i]);
    }

    return result;
}
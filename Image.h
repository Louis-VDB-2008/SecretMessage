#pragma once
#include <cstdint>
#include <string>
#include <vector>

std::vector<std::uint8_t> ReadBinaryFile(const std::string& path);

void WriteBinaryFile(const std::string& path, const std::vector<std::uint8_t>& data);

void ValidateBMPHeader(const std::vector<std::uint8_t>& data);
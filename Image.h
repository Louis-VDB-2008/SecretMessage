#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <cstddef>

struct BmpInfo
{
    std::size_t width = 0;
    std::size_t height = 0;
    std::size_t pixel_offset = 0;
    std::size_t stride = 0;
};

void inspect_pixels(const std::vector<std::uint8_t>& data, const BmpInfo& info);

std::vector<std::uint8_t> ReadBinaryFile(const std::string& path);

void WriteBinaryFile(const std::string& path, const std::vector<std::uint8_t>& data);

void ValidateBMPHeader(const std::vector<std::uint8_t>& data);
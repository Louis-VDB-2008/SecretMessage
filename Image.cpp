#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>

void lecture()
{
    std::ifstream file("ImageTest.bmp", std::ios::binary);

    if (!file)
    {
        std::cerr << "Failed to open file\n";
    }
    constexpr std::size_t buffer_size = 500;
    char buffer[buffer_size];

    file.read(buffer, buffer_size);

    std::streamsize bytes_read = file.gcount();

    std::string result(
        buffer,
        static_cast<std::size_t>(bytes_read)
    );
}
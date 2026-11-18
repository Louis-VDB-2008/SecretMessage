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


std::vector<std::uint8_t> ReadBinaryFile(const std::string& path);

void WriteBinaryFile(const std::string& path, const std::vector<std::uint8_t>& data);

BmpInfo validate_bmp_header(const std::vector<std::uint8_t>& data);

// Extrait uniquement les composantes B, G, R utiles (sans en-tête ni padding)
std::vector<std::uint8_t> extract_pixel_components(
	const std::vector<std::uint8_t>& bmp_data,       // Le buffer BMP complet (data)
	const BmpInfo& info                              // Les informations sur l'image BMP (largeur, hauteur, offset des pixels, stride)
);

// Réinjecte les composantes modifiées dans le buffer BMP
void apply_pixel_components(
    std::vector<std::uint8_t>& bmp_data,
    const BmpInfo& info,
    const std::vector<std::uint8_t>& modified_components,
	const std::string& output_path
);

std::vector<std::uint8_t> extract_pixel_color(
    const std::vector<std::uint8_t>& bmp_data,
    const BmpInfo& info);

void apply_pixel_changes(
    std::vector<std::uint8_t>& bmp_data,
    const BmpInfo& info,
    const std::vector<std::uint8_t>& modified_components,
    const std::string& output_path);
#include "Image.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::vector<std::uint8_t> ReadBinaryFile(const std::string& path)  //lire le fichier
{
	std::ifstream file(path, std::ios::binary);  // Ouvrir le fichier en mode binaire
    if (!file.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

	file.seekg(0, std::ios::end);                                       // Déplacer le curseur à la fin du fichier pour obtenir la taille
    std::streampos end_pos = file.tellg();                              // récupère l'info
	if (end_pos <= 0)                                                   // Check si le fichier est vide ou illisible
    {
        throw std::runtime_error("Fichier vide ou illisible");
    }

	std::size_t file_size = static_cast<std::size_t>(end_pos);          // Convertir la taille en std::size_t
    file.seekg(0, std::ios::beg);                                       //debut

    std::vector<std::uint8_t> buffer(file_size);
	file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(file_size)); //static_cast pour convertir la taille du vecteur en std::streamsize, reinterpret_cast pour convertir le pointeur de uint8_t en pointeur de char

	if (file.gcount() != static_cast<std::streamsize>(file_size))                               //gcount() retourne le nombre d'octets effectivement lus. Si ce nombre est différent de la taille du fichier, cela signifie que la lecture n'a pas été complète.
    {
        throw std::runtime_error("Lecture incomplete du fichier.");
    }

	return buffer;                                                                              // Retourner le buffer contenant les données du fichier
}


void WriteBinaryFile(const std::string& path, const std::vector<std::uint8_t>& data)         //écrire le fichier
{
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Impossible de creer le fichier de sortie : " + path);
    }

	file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));  
    if (!file)
    {
        throw std::runtime_error("Erreur lors de l'ecriture du fichier.");
    }

    file.close();
}


namespace
{
	std::uint16_t ReadUInt16LE(const std::vector<std::uint8_t>& data, std::size_t offset)  //fonction pour lire un entier non signé de 16 bits en little-endian à partir d'un vecteur d'octets
    {
        return static_cast<std::uint16_t>(                                                //cast pour convertir le résultat en uint16_t
			static_cast<std::uint16_t>(data[offset]) |                                    //data[offset] est le premier octet (poids faible), data[offset + 1] est le deuxième octet (poids fort)
            (static_cast<std::uint16_t>(data[offset + 1]) << 8)
            );
    }

	std::uint32_t ReadUInt32LE(const std::vector<std::uint8_t>& data, std::size_t offset)  //fonction pour lire un entier non signé de 32 bits en little-endian à partir d'un vecteur d'octets
    {
		return static_cast<std::uint32_t>(data[offset]) |                                 //data[offset] est le premier octet (poids faible), data[offset + 1] est le deuxième octet, data[offset + 2] est le troisième octet, data[offset + 3] est le quatrième octet (poids fort)
            (static_cast<std::uint32_t>(data[offset + 1]) << 8) |
            (static_cast<std::uint32_t>(data[offset + 2]) << 16) |
            (static_cast<std::uint32_t>(data[offset + 3]) << 24);
    }

    std::int32_t ReadInt32LE(const std::vector<std::uint8_t>& data, std::size_t offset)  
    {
		return static_cast<std::int32_t>(ReadUInt32LE(data, offset));  //cast pour convertir le résultat en int32_t (entier signé)
    }
}


BmpInfo validate_bmp_header(const std::vector<std::uint8_t>& data)
{
    if (data.size() < 54)
    {
        throw std::runtime_error("Fichier trop petit pour contenir un en-tete BMP valide.");
    }

    if (data[0] != 0x42 || data[1] != 0x4D)
    {
        throw std::runtime_error("Signature invalide : ce fichier n'est pas un BMP ('BM').");
    }

	std::uint32_t declared_size = ReadUInt32LE(data, 2); // Lire la taille déclarée du fichier à partir de l'en-tête BMP (offset 2)
	std::uint32_t pixel_offset = ReadUInt32LE(data, 10); // Lis l'index de début des données de pixels à partir de l'en-tête BMP (offset 10)
    std::uint32_t dib_header_size = ReadUInt32LE(data, 14); // verifie BitMapFileHeader 
	std::int32_t  width = ReadInt32LE(data, 18);            //18 à 21 : largeur de l'image en pixels (entier signé 32 bits)
	std::int32_t  height = ReadInt32LE(data, 22);           //22 à 25 : hauteur de l'image en pixels (entier signé 32 bits)
	std::uint16_t planes = ReadUInt16LE(data, 26);          //26 à 27 : nombre de plans de couleur (doit être 1)
	std::uint16_t bits_par_pixel = ReadUInt16LE(data, 28);  //28 à 29 : nombre de bits par pixel (doit être 24 pour un BMP 24 bits)
	std::uint32_t compression = ReadUInt32LE(data, 30);     //30 à 33 : type de compression (doit être 0 pour un BMP non compressé)

	if (declared_size != data.size())   //on verifie tout les champs de l'en-tête BMP
    {
        throw std::runtime_error("Taille declaree incoherente avec la taille reelle du fichier.");
    }
    if (dib_header_size != 40)
    {
        throw std::runtime_error("En-tete DIB non supporte (taille attendue : 40 octets).");
    }
    if (width <= 0 || height <= 0)
    {
        throw std::runtime_error("Dimensions invalides : largeur et hauteur doivent etre positives.");
    }
    if (planes != 1)
    {
        throw std::runtime_error("Nombre de plans invalide (attendu : 1).");
    }
    if (bits_par_pixel != 24)
    {
        throw std::runtime_error("Format non supporte : seul le BMP 24 bits est accepte.");
    }
    if (compression != 0)
    {
        throw std::runtime_error("Compression non supportee (attendu : 0 / BI_RGB).");
    }
	if (pixel_offset < 54 || pixel_offset >= data.size())                   // Vérifie que l'offset des pixels est valide (doit être >= 54 et < taille du fichier)
    {
        throw std::runtime_error("Offset des pixels invalide.");
    }

    BmpInfo info;
    info.width = static_cast<std::size_t>(width);
    info.height = static_cast<std::size_t>(height);
    info.pixel_offset = static_cast<std::size_t>(pixel_offset);
    info.stride = (info.width * 3 + 3) / 4 * 4;

	// Vérifier que le buffer est suffisant pour contenir toutes les données de pixels, en tenant compte du padding
    std::size_t required_size = info.pixel_offset + info.height * info.stride;
    if (data.size() < required_size)
    {
        throw std::runtime_error("Fichier incomplet");

    }
    std::size_t padding_bytes = info.stride - (info.width * 3);  //calcul du padding
    
    //pas obligatoire
    std::cout << "BMP valide !\n"
        << "  Dimensions: " << info.width << " x " << info.height << " pixels\n"
        << "  Offset pixels: " << info.pixel_offset << "\n"
        << "  Stride: " << info.stride << " octets/ligne "
        << "(dont " << padding_bytes << " octet(s) de padding)\n";

	return info;  //retourne les infos du BMP en size_t
}


void inspect_pixels(const std::vector<std::uint8_t>& data, const BmpInfo& info)  //data est le vecteur contenant les données du fichier BMP, info contient les informations sur l'image BMP (largeur, hauteur, offset des pixels, stride)
{
    std::size_t component_count = 0;

    for (std::size_t row = 0; row < info.height; ++row)
    {
        for (std::size_t column = 0; column < info.width; ++column)
        {
            for (std::size_t channel = 0; channel < 3; ++channel)
            {
                std::size_t index =
                    info.pixel_offset +
                    row * info.stride +
                    column * 3 +
                    channel;

                // Lecture de la composante (0 = B, 1 = G, 2 = R)
                std::uint8_t component = data[index];
                //(void)component;

                ++component_count;
            }
        }
    }

    // Affichage des composantes BGR du tout premier pixel stocké
    std::size_t first_pixel = info.pixel_offset;
    std::cout << "Premier pixel stocke (BGR) : "
        << "B=" << +data[first_pixel + 0] << ", "
        << "G=" << +data[first_pixel + 1] << ", "
        << "R=" << +data[first_pixel + 2] << '\n';

    std::cout << "Composantes utiles parcourues : " << component_count
        << " (attendu : " << info.width * info.height * 3 << ")\n";
}
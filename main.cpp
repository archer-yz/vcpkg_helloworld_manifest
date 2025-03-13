#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>
#include <Eigen/Dense>
#include <zlib.h>

std::vector<uint8_t> compressString(const std::string &input)
{
    std::vector<uint8_t> compressed(input.size() * 2); // Allocate buffer
    uLong compressedSize = static_cast<uLong>(compressed.size());

    if (compress(compressed.data(), &compressedSize,
                 reinterpret_cast<const Bytef *>(input.data()), static_cast<uLong>(input.size())) != Z_OK)
    {
        throw std::runtime_error("Compression failed");
    }

    compressed.resize(compressedSize); // Resize to actual compressed size
    return compressed;
}

std::string decompressString(const std::vector<uint8_t> &compressed, size_t originalSize)
{
    std::vector<char> decompressed(originalSize);
    uLong decompressedSize = static_cast<uLong>(decompressed.size());

    if (uncompress(reinterpret_cast<Bytef *>(decompressed.data()), &decompressedSize,
                   compressed.data(), static_cast<uLong>(compressed.size())) != Z_OK)
    {
        throw std::runtime_error("Decompression failed");
    }

    return std::string(decompressed.data(), decompressedSize);
}

int main()
{
    std::string str = "Hello, CMake + vcpkg!";
    fmt::print("Hello World!\n");

    Eigen::MatrixXd m(2, 2); // cSpell: disable-line
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);

    std::cout << m << std::endl;

    // Compress the string
    std::vector<uint8_t> compressed = compressString(str);
    std::cout << fmt::format("Original: {}\n", str);
    std::cout << fmt::format("Compressed Size: {}\n", compressed.size());

    // Decompress it
    std::string decompressed = decompressString(compressed, str.size());
    std::cout << fmt::format("Decompressed: {}\n", decompressed);

    return 0;
}

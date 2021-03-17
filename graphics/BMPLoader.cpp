#include "BMPLoader.hpp"

#include <cstring>
#include <iostream>
#include <bitset>

#include "Debug.hpp"

BMPLoader::BMPLoader(FileInterface* file)
{
    if(!(file->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
            "The BMP file must be open for reading.");
        return;
    }

    file->seek(10, FileInterface::Origin::Begin);
    file->read(reinterpret_cast<uint8_t*>(&(BMPLoader::bmpHeader)), sizeof(BMPLoader::BMPHeader));

    if (BMPLoader::bmpHeader.bitsPerPixel != 24 &&
        BMPLoader::bmpHeader.bitsPerPixel != 32)
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
            "The engine only supports 24bpp(BGR) or 32bpp(ABGR)");
        return;
    }

    BMPLoader::imageData = new char[BMPLoader::bmpHeader.imageSize];
    file->seek(BMPLoader::bmpHeader.imageOffset, FileInterface::Origin::Begin);
    file->read(reinterpret_cast<uint8_t*>(BMPLoader::imageData), BMPLoader::bmpHeader.imageSize);
}

BMPLoader::~BMPLoader()
{
    delete BMPLoader::imageData;
}

glm::vec2 BMPLoader::getImageResolution()
{
    return glm::vec2(BMPLoader::bmpHeader.width, BMPLoader::bmpHeader.height);
}

GLenum BMPLoader::getImageFormat()
{
    switch(BMPLoader::bmpHeader.bitsPerPixel)
    {
        case 24:
           return GL_BGR;
        case 32:
            return GL_BGRA;
        default:
            return 0;
    }
}

char* BMPLoader::getImageData()
{
    return BMPLoader::imageData;
}

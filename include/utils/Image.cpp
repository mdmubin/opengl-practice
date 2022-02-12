#include "Image.hpp"

#include <fmt/core.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

myutils::Image::Image(std::string &imagePath, bool flipImage)
{
    stbi_set_flip_vertically_on_load(!flipImage);
    
    m_imageData = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_channelCount, 0);
}

myutils::Image::~Image() { stbi_image_free(m_imageData); }

int myutils::Image::width() { return m_width; }

int myutils::Image::height() { return m_height; }

int myutils::Image::channelCount() { return m_channelCount; }

myutils::uchar_t *myutils::Image::imageData() { return m_imageData; }

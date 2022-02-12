#pragma once

#include <string>

namespace myutils
{

typedef unsigned char uchar_t;

/**
 * @brief A class for reading and loading data from image files (e.g. .png, .jpg, etc)
 */
class Image
{
public:
    Image() = delete;

    ~Image();

    /**
     * @brief Construct a new Image object from given path to existing image file.
     *
     * @param imagePath path to image file
     * @param flipImage flip image vertically or not
     */
    Image(std::string &imagePath, bool flipImage);

    /**
     * @brief Get a pointer to the image data.
     * NOTE: the image data is automatically deallocated within the class destructor.
     *
     * @return uchar_t* image data
     */
    uchar_t *imageData();

    /**
     * @return int width of image
     */
    int width();

    /**
     * @return int height of image
     */
    int height();
    
    /**
     * @brief Get the number of channels within an image. (e.g. 1 for GrayScale, 3 for RGB, etc.)
     *
     * @return int number of channels in the image
     */
    int channelCount();

    operator bool() const{
        return m_imageData != nullptr;
    }

private:
    uchar_t *m_imageData;

    int m_width;
    int m_height;
    int m_channelCount;
};

} // namespace myutils

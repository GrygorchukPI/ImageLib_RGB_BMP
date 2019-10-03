#ifndef READWRITEFILE_H
#define READWRITEFILE_H

#include <string.h>
#include <string>
#include <cstdint>
#include <Canvas.h>

class ImageReader
{
public:
    virtual ~ImageReader();

    virtual void ReadFile (Canvas &canvas, const std::string &source) = 0;
    virtual void WriteFile(Canvas &canvas, const std::string &source) = 0;

protected:
    virtual void FileToBuffer(const std::string &source) = 0;
    virtual void BufferToFile(const std::string &source) = 0;

    virtual void BufferToBitmap() = 0;
    virtual void BitmapToBuffer() = 0;

    void GetBitmap(Canvas &canvas);
    void SetBitmap(Canvas &canvas);

    uint32_t  bitmapSize;
    uint8_t*  bitmap;

    uint32_t bufferSize;
    uint8_t* buffer;

    uint32_t width;
    uint32_t height;
};

#endif // READWRITEFILE_H

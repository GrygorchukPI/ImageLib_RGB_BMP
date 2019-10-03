#ifndef BMP_READER_H
#define BMP_READER_H

#include"ImageReader.h"

class BMP_Reader: public ImageReader
{
public:
    BMP_Reader();
   ~BMP_Reader();

    virtual void ReadFile (Canvas &canvas, const std::string &source);
    virtual void WriteFile(Canvas &canvas, const std::string &source);

protected:

    struct BMP_FILE_HEADER
    {
        uint16_t FileType; //2
        uint32_t FileSize; //4
        uint16_t Reserved1;//2
        uint16_t Reserved2;//2
        uint32_t Off_Bits; //4
    };

    struct BMP_INFO_HEADER
    {
        uint32_t InfoHeaderSize; //4
        uint32_t Width;          //4
        uint32_t Height;         //4
        uint16_t Planes;         //2
        uint16_t BitCount;       //2
        uint32_t Compression;    //4
        uint32_t SizeImage;      //4
        uint32_t XPixelPerMeter; //4
        uint32_t YPixelPerMeter; //4
        uint32_t ColorUsed;      //4
        uint32_t ColorImportan;  //4
    };

    virtual void FileToBuffer(const std::string &source);
    virtual void BufferToFile(const std::string &source);

    virtual void BufferToBitmap();
    virtual void BitmapToBuffer();

    void FileHeadersToBuffer();
    void FileHeadersFromBuffer();

    BMP_FILE_HEADER file_header;
    BMP_INFO_HEADER info_header;

    uint8_t off_Bits;// = 54;
    uint8_t extra_Bits;
};

#endif // BMP_READER_H

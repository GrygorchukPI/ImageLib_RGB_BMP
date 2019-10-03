#include "BMP_Reader.h"

/*
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
*/

BMP_Reader::BMP_Reader()
{
    //this->off_Bits = 54;
}

BMP_Reader::~BMP_Reader()
{
    //delete[] this->buffer;
}

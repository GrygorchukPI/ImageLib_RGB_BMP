#include "BMP_Reader.h"

void BMP_Reader::WriteFile(Canvas &canvas, const std::string &source)
{
    this->GetBitmap(canvas);
    this->BitmapToBuffer();
    this->BufferToFile(source);
}

void BMP_Reader::BitmapToBuffer()
{
    /////!!!!!!!!!!!!!! EXTRA BITS!!!!!!!!!!!!
    this->extra_Bits = 0;
    if((3*this->width)%4){ this->extra_Bits = 4 - (3*this->width)%4;}

    this->off_Bits = 54;
    this->bufferSize = 3 * this->height * this->width +
            this->height * this->extra_Bits + this->off_Bits;

    this->buffer = new uint8_t[this->bufferSize];

    this->FileHeadersToBuffer();

    uint32_t i = 0;
    uint32_t j = 0;

    for (uint32_t h = 0; h < this->info_header.Height; ++h)
    {
        for (uint32_t w = 0; w < 3*this->info_header.Width; ++w)
        {
            i = w + h * 3 * this->info_header.Width;
            this->buffer[j + this->off_Bits] = this->bitmap[i];
            ++j;
        }
        if(this->extra_Bits)
        {
            for (uint8_t ext = 0; ext < this->extra_Bits; ++ext)
            {
                this->buffer[j + this->off_Bits] = 9;
                ++j;
            }
        }
    }
}

void BMP_Reader::BufferToFile(const std::string &source)
{
    //Write file
    FILE * newBMPfile;
    newBMPfile = fopen (source.c_str(), "wb");
    if(newBMPfile == NULL){printf("Cannot create file.\n"); exit(1);}

    size_t successfully_bytes_written;
    successfully_bytes_written = fwrite (this->buffer , sizeof(uint8_t),
                                         this->bufferSize, newBMPfile);

    if(successfully_bytes_written != this->bufferSize)
    {
        printf("Cannot write file.\n"); exit(1);
    }

    fclose (newBMPfile);

    //delete[] this->buffer;
}

void BMP_Reader::FileHeadersToBuffer()
{
    this->off_Bits = 54;
    //FILE HEADER SET
    this->file_header.FileType  = 19778;
    this->file_header.FileSize  = this->bufferSize;
    this->file_header.Reserved1 = 0;
    this->file_header.Reserved2 = 0;
    this->file_header.Off_Bits  = this->off_Bits;

    //INFO HEADER SET
    this->info_header.InfoHeaderSize = 40;
    this->info_header.Width          = this->width;
    this->info_header.Height         = this->height;
    this->info_header.Planes         = 1;
    this->info_header.BitCount       = 24;
    this->info_header.Compression    = 0;
    this->info_header.SizeImage      = this->bitmapSize;
    this->info_header.XPixelPerMeter = 2832;
    this->info_header.YPixelPerMeter = 2832;
    this->info_header.ColorUsed      = 0;
    this->info_header.ColorImportan  = 0;

    //File Head
    uint32_t step = 0;
    memcpy ( buffer, &this->file_header.FileType, 2);
    step = 2;
    memcpy ( buffer + step, &this->file_header.FileSize, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->file_header.Reserved1, 2);
    step = step + 2;
    memcpy ( buffer + step, &this->file_header.Reserved2, 2);
    step = step + 2;
    memcpy ( buffer + step, &this->file_header.Off_Bits, 4);
    step = step + 4;

    //Info Head
    memcpy ( buffer + step, &this->info_header.InfoHeaderSize, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.Width, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.Height, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.Planes, 2);
    step = step + 2;
    memcpy ( buffer + step, &this->info_header.BitCount, 2);
    step = step + 2;
    memcpy ( buffer + step, &this->info_header.Compression, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.SizeImage, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.XPixelPerMeter, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.YPixelPerMeter, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.ColorUsed, 4);
    step = step + 4;
    memcpy ( buffer + step, &this->info_header.ColorImportan, 4);
}

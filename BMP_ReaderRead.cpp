#include "BMP_Reader.h"

void BMP_Reader::ReadFile(Canvas &canvas, const std::string &source)
{
    this->FileToBuffer(source);
    this->BufferToBitmap();
    SetBitmap(canvas);
}

void BMP_Reader::FileToBuffer(const std::string &source)
{
    FILE* fileBMP;

    fileBMP = fopen(source.c_str() , "rb" );
    if(fileBMP == NULL){printf("Cannot open file.\n"); exit(1);}

    //Get file size.
    fseek (fileBMP , 0 , SEEK_END);
    this->bufferSize = ftell (fileBMP);
    fseek(fileBMP, 0, SEEK_SET);

    this->buffer = new uint8_t[this->bufferSize];
    int64_t successfully_bytes_read;
    successfully_bytes_read = fread (this->buffer, sizeof(char), this->bufferSize, fileBMP);
    if(successfully_bytes_read != this->bufferSize){printf("Cannot read file.\n"); exit(1);}

    fclose (fileBMP);
}

void BMP_Reader::BufferToBitmap()
{
    ///EXTRA BITS !!!!!
    //File Head
    uint32_t step = 0;
    this->file_header.FileType = *(uint16_t*)(buffer);
    step = step + sizeof(uint16_t);
    this->file_header.FileSize = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->file_header.Reserved1 = *(uint16_t*)(buffer + step);
    step = step + sizeof(uint16_t);
    this->file_header.Reserved2 = *(uint16_t*)(buffer + step);
    step = step + sizeof(uint16_t);
    this->file_header.Off_Bits = *(uint32_t*)(buffer + step);

    //Info Head
    step = step + sizeof(uint32_t);
    this->info_header.InfoHeaderSize = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.Width = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.Height = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.Planes = *(uint16_t*)(buffer + step);
    step = step + sizeof(uint16_t);
    this->info_header.BitCount = *(uint16_t*)(buffer + step);
    step = step + sizeof(uint16_t);
    this->info_header.Compression = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.SizeImage = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.XPixelPerMeter = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.YPixelPerMeter = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.ColorUsed = *(uint32_t*)(buffer + step);
    step = step + sizeof(uint32_t);
    this->info_header.ColorImportan = *(uint32_t*)(buffer + step);

    this->width  = this->info_header.Width;
    this->height = this->info_header.Height;
    this->off_Bits = this->file_header.Off_Bits;
    this->bitmapSize = this->info_header.SizeImage;
    this->bitmap = new uint8_t[this->bitmapSize];

    this->extra_Bits = 0;
    uint32_t shift = 0;
    if((3*this->width)%4){ this->extra_Bits = 4 - (3*this->width)%4;}

    uint32_t k = 0;
    for(uint32_t h = 0; h < this->height; ++h)
    {
        for(uint32_t w = 0; w < 3*this->width; ++w)
        {
            this->bitmap[k] = this->buffer[k + shift + this->file_header.Off_Bits];
            ++k;
        }
        if(this->extra_Bits)
        {
            shift = shift + this->extra_Bits;
        }
    }
}

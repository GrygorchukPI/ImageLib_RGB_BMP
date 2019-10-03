#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "ImageReader.h"
#include "Canvas.h"

void ImageReader::GetBitmap(Canvas &canvas)
{
    canvas.RGB_BGR_Switch();
    //canvas.FlipVertical();
    this->bitmapSize = canvas.GetBitmapSize();
    this->width      = canvas.GetWidth();
    this->height     = canvas.GetHeight();

    this->bitmap = new uint8_t[this->bitmapSize];
    uint8_t* innerBitmap = canvas.GetBitmap();

    for (uint32_t i = 0; i < this->bitmapSize; ++i)
    {
        this->bitmap[i] = innerBitmap[i];
    }
}

void ImageReader::SetBitmap(Canvas &canvas)
{
    canvas.SetBitmapSize(this->bitmapSize);
    canvas.SetWidth(this->width);
    canvas.SetHeight(this->height);
    canvas.SetBitmap(this->bitmap);
    canvas.RGB_BGR_Switch();
    //canvas.FlipVertical();
}

ImageReader::~ImageReader()
{
    //delete[] this->bitmap;
}

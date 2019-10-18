#include "Canvas.h"

Canvas::Canvas(){}
Canvas::Canvas(uint32_t w, uint32_t h, RGB color)
{
    this->width  = w;
    this->height = h;

    this->bitmapSize = 3*w*h;
    this->bitmap = new uint8_t[this->bitmapSize];

    this->FillCanvasByColor(color);
}
Canvas::~Canvas()
{
    //delete [] this->bitmap;
}

/////////Bitmap

void Canvas::SetBitmapSize(uint32_t in_bitmapSize)
{
    this->bitmapSize = in_bitmapSize;
}

void Canvas::SetBitmap(uint8_t* in_bitmap)
{
    this->bitmap = new uint8_t[this->bitmapSize];

    for (uint32_t i = 0; i < this->bitmapSize; ++i)
    {
        this->bitmap[i] = in_bitmap[i];
    }
}

uint32_t Canvas::GetBitmapSize()
{
    return  this->bitmapSize;
}

uint8_t* Canvas::GetBitmap()
{
    return this->bitmap;
}

////////////////////////////////////////////////////////////////

void Canvas::SetPixel(uint32_t x, uint32_t y, RGB color)
{
    if(x < this->width && y < this->height)
    {
        uint32_t i = 3*(this->width * y + x);
        this->bitmap[i]   = color.R;
        this->bitmap[i+1] = color.G;
        this->bitmap[i+2] = color.B;
    }
}

RGB  Canvas::GetPixel(uint32_t x, uint32_t y)
{
    RGB res;

    if(x < this->width && y < this->height)
    {
        uint32_t i = 3*(this->width * y + x);
        res.R = this->bitmap[i];
        res.G = this->bitmap[i+1];
        res.B = this->bitmap[i+2];
    }

    return res;
}

void Canvas::RGB_BGR_Switch()
{
    uint8_t swap = 0;
    for(uint32_t i = 0; i < this->bitmapSize; i = i +3)
    {
        swap = this->bitmap[i];
        this->bitmap[i] = this->bitmap[i+2];
        this->bitmap[i+2] = swap;
    }
}

void Canvas::FillCanvasByColor(RGB color)
{
    for (uint32_t h = 0; h < this->height; ++h)
    {
        for (uint32_t w = 0; w < this->width; ++w)
        {
            this->SetPixel(w, h,color);
        }
    }
}

///// Width Height
void Canvas::SetWidth(uint32_t in_w)
{
    this->width = in_w;
}

void Canvas::SetHeight(uint32_t in_h)
{
    this->height = in_h;
}

uint32_t Canvas::GetWidth()
{
    return this->width;
}

uint32_t Canvas::GetHeight()
{
    return this->height;
}

void Canvas::SwapPixel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    uint8_t swapR = 0;
    uint8_t swapG = 0;
    uint8_t swapB = 0;

    if(x1 < this->width && y1 < this->height && x2 < this->width && y2 < this->height)
    {
        uint32_t i = 3*(this->width * y1 + x1);
        uint32_t j = 3*(this->width * y2 + x2);

        swapR = this->bitmap[i];
        swapG = this->bitmap[i+1];
        swapB = this->bitmap[i+2];

        this->bitmap[i]   = this->bitmap[j];
        this->bitmap[i+1] = this->bitmap[j+1];
        this->bitmap[i+2] = this->bitmap[j+2];

        this->bitmap[j]   = swapR;
        this->bitmap[j+1] = swapG;
        this->bitmap[j+2] = swapB;
    }
}

void Canvas::FlipHorizontal()
{
    for(uint32_t h = 0; h < this->height; ++h)
    {
        for(uint32_t w = 0; w < this->width/2; ++w)
        {
            this->SwapPixel(w, h, this->width - w - 1, h);
        }
    }
}

void Canvas::FlipVertical()
{
    for(uint32_t i = 0; i < this->height/2; ++i)
    {
        this->SwapRows(i, this->height - i - 1);
    }
}

void Canvas::SwapRows(uint32_t i, uint32_t j)
{
    //void * memmove ( void * destination, const void * source, size_t num );
    if(i != j)
    {
        uint8_t* tmp = new uint8_t[3*this->width];
        memmove ( tmp, this->bitmap+(3*i*this->width), 3*this->width );
        memmove ( this->bitmap+(3*i*this->width), this->bitmap+(3*j*this->width), 3*this->width );
        memmove ( this->bitmap+(3*j*this->width), tmp, 3*this->width );
    }
}

void Canvas::PrintBitmap()
{
    printf("\n");
    uint32_t i = 0;
    for(uint32_t h = 0; h < this->height; ++h)
    {
        for(uint32_t w = 0; w < 3*this->width; ++w)
        {
            printf("%i ",this->bitmap[i]);
            ++i;
        }
        printf("\n");
    }
    printf("\n");
}

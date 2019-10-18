#ifndef CANVAS_H
#define CANVAS_H

#include<stdio.h>
#include <string.h>
#include <cstdint>

struct RGB
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

class Canvas
{
public:
    Canvas();// done
    Canvas(uint32_t w, uint32_t h, RGB color);
   ~Canvas();// done

    void SetBitmapSize(uint32_t in_bitmapSize);// done
    void SetBitmap(uint8_t* in_bitmap); // done

    uint32_t GetBitmapSize();// done
    uint8_t* GetBitmap();// done

    void FillCanvasByColor(RGB color);// done
    void SetPixel(uint32_t x, uint32_t y, RGB color);// done
    RGB  GetPixel(uint32_t x, uint32_t y); // almost done

    void RGB_BGR_Switch();//done

    void FlipHorizontal();//done
    void FlipVertical();//done

    void SetWidth(uint32_t in_w);// done
    void SetHeight(uint32_t in_h);// done
    uint32_t GetWidth();// done
    uint32_t GetHeight();// done

    void PrintBitmap();

private:

    uint32_t width;
    uint32_t height;

    uint8_t* bitmap;
    uint32_t bitmapSize;

    void SwapRows(uint32_t i, uint32_t j);
    void SwapPixel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
};

#endif // CANVAS_H

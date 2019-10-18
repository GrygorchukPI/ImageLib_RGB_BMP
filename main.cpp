#include<stdio.h>
#include<Canvas.h>
#include<BMP_Reader.h>

RGB Mandebrot(float i, float j)
{
    int numIterations {255};
    float x_old {0.0};
    float y_old {0.0};
    float x_new {0.0};
    float y_new {0.0};

    float abs = 0;

    RGB color{0,0,0};

    for (int k = 0; k < numIterations; ++k)
    {
        x_new = x_old * x_old-y_old * y_old + i;
        y_new = 2.0 * x_old * y_old + j;
        x_old = x_new;
        y_old = y_new;
        abs = x_old*x_old+y_old*y_old;

        if(abs > 1.0)
        {
            color.B = color.B + k;
            color.G = color.G + k;
            color.R = color.R + k;
            break;
        }
    }

    //return (x_old*x_old+y_old*y_old) < 1.0;
    return color;
}

int main()
{
    printf("BEGIN - ImageReader.\n");
/*
    uint32_t w = 400;
    uint32_t h = 400;
    Canvas canvas(w,h,{0,0,255});

    float cx = 0;
    float cy = 0;
    float zx_old = 0;
    float zy_old = 0;
    float zx_new = 0;
    float zy_new = 0;
    float sqrtabs = 0;
    RGB color {0,255,0};

    for (uint32_t i = 0; i < w; ++i)
    {
        for (uint32_t j = 0; j < h; ++j)
        {
            cx = 5.0*(float(i)-w/2)/float(w);
            cy = 5.0*(float(j)-h/2)/float(h);
            zx_old = cx;
            zy_old = cy;
            for (uint8_t k = 0; k < 255; ++k)
            {
                zx_new = zx_old*zx_old - zy_old*zy_old + cx;
                zy_new = 2*zx_old*zy_old + cy;
                zx_old = zx_new;
                zy_old = zy_new;
                sqrtabs = zx_old*zx_old + zx_old*zx_old;
                color.B = k;
                color.G = k;
                color.R = k;
                if(sqrtabs > 100.0f) break;
            }
            canvas.SetPixel(i,j,color);
            color.B = 0;
            color.G = 0;
            color.R = 0;
        }
    }

    BMP_Reader writer;
    writer.WriteFile(canvas, "..//YO.bmp");
    */

    //Canvas canvas2(7,9,{255,0,0});
    Canvas canvas2;
    BMP_Reader reader;
    BMP_Reader writer;

    reader.ReadFile(canvas2,"..//nude.bmp");

    /*
    for(uint32_t h = 0; h < 9; ++h)
    {
        for(uint32_t w = 0 ; w < 3; ++w)
        {
            canvas2.SetPixel(w, h, RGB{0,0,255});
        }
    }
    */

    //canvas2.SetPixel(0, 0, RGB{0,0,255});
    //canvas2.SetPixel(0, 1, RGB{0,0,255});
    //canvas2.SetPixel(0, 2, RGB{0,0,255});
    //canvas2.PrintBitmap();
    //canvas2.FlipVertical();
    canvas2.FlipHorizontal();
    //canvas2.SwapPixel(0,0,6,0);
    //canvas2.PrintBitmap();
    writer.WriteFile(canvas2,"..//Yo.bmp");


    printf("END - ImageReader.\n");
    return 0;
}

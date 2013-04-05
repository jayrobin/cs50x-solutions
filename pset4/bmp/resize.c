#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int resize = atoi(argv[1]);
    if(resize < 1 || resize > 100)
    {
        printf("Resize must be between 1 and 100\n");
        return 2;
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // store original dimensions
    int originalWidth = abs(bi.biWidth);
    int originalHeight = abs(bi.biHeight);
    //int originalSizeImage = bi.biSizeImage;
    //int originalSize = bf.bfSize;
      
    // change dimensions in BITMAPINFOHEADER
    bi.biWidth *= resize;
    bi.biHeight *= resize;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int originalPadding =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = (abs(bi.biWidth) * 3 + padding) * abs(bi.biHeight);
    
    // change dimensions in BITMAPFILEHEADER
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;
    
    //printf("Width: %d, %d\n", originalWidth, bi.biWidth);
    //printf("Height: %d, %d\n", originalHeight, bi.biHeight);
    //printf("Size Image: %d, %d\n", originalSizeImage, bi.biSizeImage);
    //printf("Size: %d, %d\n", originalSize, bf.bfSize);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < originalHeight; i++)
    {
        for (int l = 0; l < resize; l++)
        {
            fseek(inptr, bf.bfOffBits + i * (originalPadding + (originalWidth * 3)), SEEK_SET);
            //printf("%d, %d, %d . %d\n", i, padding, originalWidth, i * (originalPadding + (originalWidth * 3)));
            // iterate over pixels in scanline
            for (int j = 0; j < originalWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < resize; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
            
            // reset to start of scanline
            //fseek(inptr, -(padding + bi.biWidth * 3), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

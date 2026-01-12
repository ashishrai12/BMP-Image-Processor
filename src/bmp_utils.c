#include "bmp_utils.h"
#include <stdlib.h>
#include <math.h>

int bmp_copy(const char* infile, const char* outfile) {
    FILE* inptr = fopen(infile, "rb");
    if (inptr == NULL) return 2;

    FILE* outptr = fopen(outfile, "wb");
    if (outptr == NULL) {
        fclose(inptr);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        for (int j = 0; j < bi.biWidth; j++) {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        fseek(inptr, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++) {
            fputc(0x00, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}

int bmp_resize(const char* infile, const char* outfile, int n) {
    if (n < 1) return 1;

    FILE* inptr = fopen(infile, "rb");
    if (inptr == NULL) return 2;

    FILE* outptr = fopen(outfile, "wb");
    if (outptr == NULL) {
        fclose(inptr);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        return 4;
    }

    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int absOldHeight = abs(oldHeight);
    int padding1 = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth *= n;
    bi.biHeight *= n;
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding2) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 0; i < absOldHeight; i++) {
        for (int r = 0; r < n; r++) {
            for (int j = 0; j < oldWidth; j++) {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int r1 = 0; r1 < n; r1++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for (int k = 0; k < padding2; k++) {
                fputc(0x00, outptr);
            }
            if (r < n - 1) {
                fseek(inptr, -(oldWidth * (int)sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        fseek(inptr, padding1, SEEK_CUR);
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}

int bmp_filter_red(const char* infile, const char* outfile) {
    FILE* inptr = fopen(infile, "rb");
    if (inptr == NULL) return 2;

    FILE* outptr = fopen(outfile, "wb");
    if (outptr == NULL) {
        fclose(inptr);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        for (int j = 0; j < bi.biWidth; j++) {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // Filter: Replace pure red (00, 00, FF) with white (FF, FF, FF)
            // Note: BGR order in RGBTRIPLE
            if (triple.rgbtGreen == 0x00 && triple.rgbtBlue == 0x00 && triple.rgbtRed == 0xff) {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }
            
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        fseek(inptr, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++) {
            fputc(0x00, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}

int recover_jpegs(const char* infile) {
    uint8_t buffer[512];
    char title[20];
    int count = 0;
    FILE* filer = fopen(infile, "rb");
    if (filer == NULL) return 2;

    FILE* filew = NULL;

    while (fread(buffer, 512, 1, filer) == 1) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            if (filew != NULL) {
                fclose(filew);
            }
            sprintf(title, "%03d.jpg", count++);
            filew = fopen(title, "wb");
        }
        if (filew != NULL) {
            fwrite(buffer, 512, 1, filew);
        }
    }

    if (filew != NULL) {
        fclose(filew);
    }
    fclose(filer);
    return 0;
}

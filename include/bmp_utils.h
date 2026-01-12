#ifndef BMP_UTILS_H
#define BMP_UTILS_H

#include "bmp.h"
#include <stdio.h>

int bmp_copy(const char* infile, const char* outfile);
int bmp_resize(const char* infile, const char* outfile, int factor);
int bmp_filter_red(const char* infile, const char* outfile);
int recover_jpegs(const char* infile);

#endif // BMP_UTILS_H

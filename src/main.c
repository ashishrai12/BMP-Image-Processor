#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_utils.h"

void print_usage(const char* progname) {
    printf("Usage: %s <command> [args]\n", progname);
    printf("Commands:\n");
    printf("  copy <infile> <outfile>       - Copy a BMP file\n");
    printf("  resize <n> <infile> <outfile> - Resize a BMP file by factor n\n");
    printf("  filter-red <infile> <outfile> - replace pure red with white\n");
    printf("  recover <rawfile>             - Recover JPEGs from a raw file\n");
    printf("  info <infile>                 - Display BMP file information\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char* command = argv[1];

    if (strcmp(command, "copy") == 0) {
        if (argc != 4) {
            printf("Usage: %s copy <infile> <outfile>\n", argv[0]);
            return 1;
        }
        return bmp_copy(argv[2], argv[3]);
    } else if (strcmp(command, "resize") == 0) {
        if (argc != 5) {
            printf("Usage: %s resize <n> <infile> <outfile>\n", argv[0]);
            return 1;
        }
        int n = atoi(argv[2]);
        return bmp_resize(argv[3], argv[4], n);
    } else if (strcmp(command, "filter-red") == 0) {
        if (argc != 4) {
            printf("Usage: %s filter-red <infile> <outfile>\n", argv[0]);
            return 1;
        }
        return bmp_filter_red(argv[2], argv[3]);
    } else if (strcmp(command, "recover") == 0) {
        if (argc != 3) {
            printf("Usage: %s recover <rawfile>\n", argv[0]);
            return 1;
        }
        return recover_jpegs(argv[2]);
    } else if (strcmp(command, "info") == 0) {
        if (argc != 3) {
            printf("Usage: %s info <infile>\n", argv[0]);
            return 1;
        }
        return bmp_info(argv[2]);
    } else {
        printf("Unknown command: %s\n", command);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}

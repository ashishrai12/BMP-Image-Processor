#include <stdio.h>
#include <assert.h>
#include "bmp_utils.h"

int main() {
    printf("Running basic tests...\n");
    
    // Test that the functions exist and can be called (even if they fail due to missing files)
    // In a real scenario, we'd create a small BMP file and test operations on it.
    
    int result = bmp_copy("nonexistent.bmp", "out.bmp");
    assert(result == 2); // File not found
    
    printf("Basic tests passed!\n");
    return 0;
}

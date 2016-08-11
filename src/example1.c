#include <stdlib.h>
#include <stdio.h>
#include "colors.h"

int main() {
    puts("System colors:");
    for (int i = 0; i < 16; i++) {
        term_set_fg(i);
        printf("%4d", i);
        term_reset();
        if (i % 8 == 7) puts("");
    }
    puts("Cube 6x6x6:");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                int col = 16 + j * 36 + i * 6 + k;
                term_set_fg(col);
                printf("%4d", col);
                term_reset();
            }
            printf(" ");
        }
        puts("");
    }
    puts("Grayscale:");
    for (int i = 16 + 36 * 6; i < UINT8_MAX; i++) {
        term_set_fg(i);
        printf("%4d", i);
        term_reset();
    }
    
    puts("");

    return 0;
}

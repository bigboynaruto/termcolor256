#include <stdlib.h>
#include <stdio.h>
#include "colors.h"

int main() {
    term_set_bg(RED);
    printf("WHITE TEXT ON RED");
    term_reset();
    puts("");
    
    term_set_format(UNDERLINED);
    printf("WHITE UNDERLINED TEXT ON BLACK");
    term_reset();
    puts("");
    
    term_set_fg(BLUE);
    term_set_format(INVERTED);
    printf("BLUE INVERTED TEXT ON BLACK");
    term_reset();
    puts("");

    return 0;
}

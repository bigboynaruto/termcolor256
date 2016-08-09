#ifndef TERMCOLS_H
#define TERMCOLS_H

#include <stdio.h>
#include <stdint.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>

#else

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTRED 9
#define LIGHTGREEN 10
#define LIGHTYELLOW 11
#define LIGHTBLUE 12
#define LIGHTMAGENTA 13
#define LIGHTCYAN 14
#define WHITE 15

#define BOLD 1
#define DIM 2
#define UNDERLINED 4
#define BLINK 5
#define INVERTED 7
#define HIDDEN 8

#define RESET_ALL 0

#endif

#define RGB(r, g, b) (r * 6 / 256) * 36 + (g * 6 / 256) * 6 + (b * 6 / 256)

static struct {
    uint8_t fg_col;
    uint8_t bg_col;
    uint8_t format;
} text;

void init(uint8_t fg, uint8_t bg, uint8_t f) {
    f %= 9;
    text.fg_col = fg;
    text.bg_col = bg;
    text.format = f;
}

void set_fg(uint8_t col) {
    char c[] = "\e[38;5;000m";
    c[7] += col / 100;
    c[8] += col % 100 / 10;
    c[9] += col % 100 % 10;
    printf("%s", c);
    text.fg_col = col;
}

void set_bg(uint8_t col) {
    char c[] = "\e[48;5;000m";
    c[7] += col / 100;
    c[8] += col % 100 / 10;
    c[9] += col % 100 % 10;
    printf("%s", c);
    text.bg_col = col;
}

void reset() {
    printf("\e[0m");
    text.fg_col = 0;
    text.bg_col = 0;
    text.format = 0;
}

void set_format(uint8_t f) {
    f %= 9;
    printf("\e[%dm", f);
}

void reset_format(uint8_t f) {
    f %= 9;
    printf("\e[%dm", f + 20);
}
#endif //TERMCOLS_H

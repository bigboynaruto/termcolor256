#ifndef TERMCOLOR256_H
#define TERMCOLOR256_H

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/*
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>

#else
*/

/*
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
*/

typedef enum {
    BOLD = 1,
    DIM = 2,
    UNDERLINED = 4,
    BLINK = 5,
    INVERTED = 7,
    HIDDEN = 8
} Formats;

typedef enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_YELLOW,
    LIGHT_BLUE,
    LIGHT_MAGENTA,
    LIGHT_CYAN,
    WHITE
} StandartColors;

/*
#define BOLD 1
#define DIM 2
#define UNDERLINED 4
#define BLINK 5
#define INVERTED 7
#define HIDDEN 8
*/

/*
#endif
*/

#define RGB(r, g, b) (r * 6 / 256) * 36 + (g * 6 / 256) * 6 + (b * 6 / 256)
#define term_set_format(...) _term_set_format(__VA_ARGS__, NULL)
#define term_reset_format(...) _term_reset_format(__VA_ARGS__, NULL)

void term_set_fg(uint8_t col) {
    char c[] = "\e[38;5;000m";
    c[7] += col / 100;
    c[8] += col % 100 / 10;
    c[9] += col % 100 % 10;
    printf("%s", c);
}

void term_set_bg(uint8_t col) {
    char c[] = "\e[48;5;000m";
    c[7] += col / 100;
    c[8] += col % 100 / 10;
    c[9] += col % 100 % 10;
    printf("%s", c);
}

void term_reset() {
    printf("\e[0m");
}

void _term_set_format(Formats arg1, ...) {
    va_list ap;
    va_start(ap, arg1);

    void* curr_arg = (void*)arg1;

    do {
        printf("\e[%dm", (uint8_t)(Formats)curr_arg);
    }
    while ((curr_arg = va_arg(ap, void*)) != NULL);

    va_end(ap);
}

void _term_reset_format(Formats arg1, ...) {
    va_list ap;
    va_start(ap, arg1);

    void* curr_arg = (void*)arg1;

    do {
        printf("\e[%dm", (uint8_t)(Formats)curr_arg + 20);
    }
    while ((curr_arg = va_arg(ap, void*)) != NULL);

    va_end(ap);
}

#endif //TERMCOLS_H

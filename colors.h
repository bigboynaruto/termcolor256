#ifndef TERMCOLOR256_H
#define TERMCOLOR256_H

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#error "Windows is not supported yet"

#include <windows.h>
#include <io.h>

#define __WINDOWS__

#define _ISATTY_ _isatty(_fileno(stdout))

typedef enum {
    BLACK           = 0,
    BLUE            = FOREGROUND_BLUE,
    GREEN           = FOREGROUND_GREEN,
    CYAN            = FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED             = FOREGROUND_RED,
    MAGENTA         = FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW          = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY        = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    LIGHTGRAY            = FOREGROUND_INTENSITY,
    LIGHTBLUE       = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    LIGHTGREEN      = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    LIGHTCYAN       = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    LIGHTRED        = FOREGROUND_INTENSITY | FOREGROUND_RED,
    LIGHTMAGENTA    = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    LIGHTYELLOW     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

#elif defined(__unix__) || defined(__unix) || defined(__APPLE__)

#include <unistd.h>

#define __UNIX__

#define _ISATTY_ isatty(fileno(stdout))

typedef enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTRED,
    LIGHTGREEN,
    LIGHTYELLOW,
    LIGHTBLUE,
    LIGHTMAGENTA,
    LIGHTCYAN,
    WHITE
} StandartColors;

#else

#error "unsupported platform"

#endif

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

/*
#define BOLD 1
#define DIM 2
#define UNDERLINED 4
#define BLINK 5
#define INVERTED 7
#define HIDDEN 8
*/

//#define RGB(r,g,b) (r * 6 / 256) * 36 + (g * 6 / 256) * 6 + (b * 6 / 256)
#define term_set_format(...) _term_set_format(__VA_ARGS__, NULL)
#define term_reset_format(...) _term_reset_format(__VA_ARGS__, NULL)

//#define TO_STRING(x) #x
//#define BG(col) TO_STRING(col)

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define term_set_fg(...) GET_MACRO(__VA_ARGS__, _term_set_fg3, NULL, _term_set_fg1)(__VA_ARGS__)
#define term_set_bg(...) GET_MACRO(__VA_ARGS__, _term_set_bg3, NULL, _term_set_bg1)(__VA_ARGS__)

void _term_set_fg1(uint8_t col) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            char c[] = "\e[38;5;000m";
            c[7] += col / 100;
            c[8] += col % 100 / 10;
            c[9] += col % 100 % 10;
            printf("%s", c);
        #elif defined(__WINDOWS__)
            if (col >= 0 && col < 16) {
                CONSOLE_SCREEN_BUFFER_INFO info;
                GetConsoleScreenBufferInfo(h, &info);
                uint8_t fg_col = col;
                uint8_t bg_col = info.wAttributes >> 4;
                SetConsoleTextAttribute(h, fg_col | bg_col);
            }
        #endif
    }
}

void _term_set_fg3(uint8_t r, uint8_t g, uint8_t b) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            printf("\e[38;5;%d;%d;%dm", r, g, b);
        #endif
    }
}

void _term_set_bg1(uint8_t col) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            char c[] = "\e[48;5;000m";
            c[7] += col / 100;
            c[8] += col % 100 / 10;
            c[9] += col % 100 % 10;
            printf("%s", c);
        #elif defined(__WINDOWS__)
            if (col >= 0 && col < 16) {
                CONSOLE_SCREEN_BUFFER_INFO info;
                GetConsoleScreenBufferInfo(h, &info);
                uint8_t bg_col = col << 4;
                uint8_t fg_col = info.wAttributes & 15;
                SetConsoleTextAttribute(h, fg_col | bg_col);
            }
        #endif
    }
}

void _term_set_bg3(uint8_t r, uint8_t g, uint8_t b) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            printf("\e[48;5;%d;%d;%dm", r, g, b);
        #endif
    }
}

void term_reset_fg() {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            printf("\e[38;5;016m");
        #endif
    }
}

void term_reset_bg() {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            printf("\e[48;5;016m");
        #endif
    }
}

void term_reset() {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            printf("\e[0m");
        #elif defined
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, -1);
        #endif
    }
}

void _term_set_format(Formats arg1, ...) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            va_list ap;
            va_start(ap, arg1);

            void* curr_arg = (void*)arg1;

            do {
                printf("\e[%dm", (uint8_t)(Formats)curr_arg);
            }
            while ((curr_arg = va_arg(ap, void*)) != NULL);

            va_end(ap);
        #endif
    }
}

void _term_reset_format(Formats arg1, ...) {
    if (_ISATTY_) {
        #if defined(__UNIX__)
            va_list ap;
            va_start(ap, arg1);

            void* curr_arg = (void*)arg1;

            do {
                printf("\e[%dm", (uint8_t)(Formats)curr_arg + 20);
            }
            while ((curr_arg = va_arg(ap, void*)) != NULL);

            va_end(ap);
        #endif
    }
}

#endif //TERMCOLOR256_H
